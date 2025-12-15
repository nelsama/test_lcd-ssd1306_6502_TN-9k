/**
 * main_clock.c - Ejemplo RELOJ con números grandes
 * 
 * Configuración mínima - solo core + bignum + control
 * 
 * Hardware:
 *   - 6502 CPU @ 6.75MHz en FPGA Tang Nano
 *   - I2C en $C010-$C014
 *   - UART en $C020-$C023
 *   - OLED SSD1306 128x32 en I2C 0x3C
 * 
 * Compilar: make -f makefile_clock
 */

#include <stdint.h>
#include "../libs/uart/uart.h"
#include "../libs/i2c/i2c.h"
#include "../libs/ssd1306/ssd1306_new.h"

/* Variables del reloj */
static uint8_t hours = 12;
static uint8_t minutes = 0;
static uint8_t seconds = 0;

/* Delay aproximado de 1 segundo (ajustar según CPU) */
void delay_1sec(void) {
    volatile uint16_t i, j;
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 600; j++) {
            /* espera */
        }
    }
}

/* Incrementar tiempo */
void tick(void) {
    seconds++;
    if (seconds >= 60) {
        seconds = 0;
        minutes++;
        if (minutes >= 60) {
            minutes = 0;
            hours++;
            if (hours >= 24) {
                hours = 0;
            }
        }
    }
}

/* ============================================
 * PROGRAMA PRINCIPAL - RELOJ
 * ============================================ */

int main(void) {
    uint8_t last_min = 255;  /* Para detectar cambio */
    uint8_t colon_visible = 1;
    
    /* Inicializar UART */
    uart_init();
    
    /* Inicializar I2C */
    i2c_init();
    
    uart_puts("\r\n");
    uart_puts("========================\r\n");
    uart_puts("  6502 Big Clock Demo\r\n");
    uart_puts("========================\r\n\r\n");
    
    /* Inicializar display */
    if (!ssd1306_init()) {
        uart_puts("ERROR: SSD1306!\r\n");
        while(1);
    }
    
    uart_puts("Display OK\r\n");
    
    /* Limpiar pantalla */
    ssd1306_clear();
    
    /* Ajustar brillo (opcional) */
#if SSD1306_USE_CONTROL
    ssd1306_set_contrast(0xFF);  /* Máximo brillo */
#endif
    
    /* Loop principal del reloj */
    while (1) {
        /* Solo redibujar si cambiaron los minutos */
        if (minutes != last_min) {
            ssd1306_bignum_time(2, hours, minutes);
            last_min = minutes;
            
            /* Debug por UART */
            uart_puts("Time: ");
            uart_putc('0' + hours / 10);
            uart_putc('0' + hours % 10);
            uart_putc(':');
            uart_putc('0' + minutes / 10);
            uart_putc('0' + minutes % 10);
            uart_puts("\r\n");
        }
        
        /* Parpadeo del colon cada segundo (visual) */
        /* En un reloj real, usarías interrupción de timer */
        
        /* Esperar 1 segundo */
        delay_1sec();
        
        /* Incrementar tiempo */
        tick();
        
        /* Parpadeo colon (invertir cada segundo) */
        colon_visible = !colon_visible;
        /* Aquí podrías redibujar solo el colon para efecto parpadeo */
    }
    
    return 0;
}
