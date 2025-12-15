/**
 * main.c - Demo completo SSD1306
 * 
 * Muestra TODAS las capacidades del driver modular:
 *   - Texto pequeño (5x7)
 *   - Texto invertido
 *   - Números decimales y hexadecimales
 *   - BigFont (15x15 px)
 *   - Gráficos (líneas, rectángulos, barra progreso)
 *   - Scroll
 *   - Control (contraste, inversión)
 *   - Framebuffer (píxeles, líneas diagonales, círculos)
 */

#include <stdint.h>
#include "../libs/uart/uart.h"
#include "../libs/i2c/i2c.h"
#include "../libs/ssd1306/ssd1306.h"

/* Icono ejemplo 8x8: corazón */
static const uint8_t icon_heart[8] = {
    0x0C, 0x1E, 0x3E, 0x7C, 0x7C, 0x3E, 0x1E, 0x0C
};

/* Icono ejemplo 8x8: estrella */
static const uint8_t icon_star[8] = {
    0x08, 0x08, 0x3E, 0x1C, 0x1C, 0x36, 0x22, 0x00
};

/* Delay */
void delay(uint16_t count) {
    volatile uint16_t i;
    for (i = 0; i < count; i++);
}

void delay_sec(uint8_t sec) {
    uint8_t s;
    for (s = 0; s < sec; s++) {
        delay(60000);
    }
}

/* ============================================
 * DEMO 1: Texto pequeño (5x7)
 * ============================================ */
void demo_text(void) {
    uart_puts("Demo 1: Texto pequeno 5x7\r\n");
    
    ssd1306_clear();
    ssd1306_text(0, 0, "Texto normal 5x7");
    ssd1306_text(0, 1, "Segunda linea");
    ssd1306_text(0, 2, "!@#$%^&*()");
    ssd1306_text(0, 3, "abcdefghijklmnop");
    delay_sec(1);
    
    /* Texto invertido */
    uart_puts("   Texto invertido\r\n");
    ssd1306_clear();
    ssd1306_text(0, 0, "Normal:");
    ssd1306_text(48, 0, "Hola");
    ssd1306_text(0, 2, "Invertido:");
    ssd1306_text_inv(66, 2, "Hola");
    delay_sec(1);
}

/* ============================================
 * DEMO 2: Números
 * ============================================ */
void demo_numbers(void) {
    uart_puts("Demo 2: Numeros\r\n");
    
    ssd1306_clear();
    ssd1306_text(0, 0, "Decimal:");
    ssd1306_number(60, 0, 12345);
    ssd1306_text(0, 1, "Negativo:");
    ssd1306_number_signed(60, 1, -9876);
    ssd1306_text(0, 2, "Hex 8b:");
    ssd1306_hex8(60, 2, 0xAB);
    ssd1306_text(0, 3, "Hex 16b:");
    ssd1306_hex16(60, 3, 0xCAFE);
    delay_sec(1);
}

/* ============================================
 * DEMO 3: BigFont
 * ============================================ */
void demo_bigfont(void) {
    uint8_t i;
    
    uart_puts("Demo 3: BigFont 15x15px\r\n");
    
    /* Texto centrado */
    ssd1306_clear();
    ssd1306_bigtext_center("HOLA");
    delay_sec(1);
    
    /* Número */
    ssd1306_clear();
    ssd1306_bigtext_center("6502");
    delay_sec(1);
    
    /* Dos líneas */
    ssd1306_clear();
    ssd1306_bigtext(20, BIGFONT_ROW1, "CPU");
    ssd1306_bigtext(4, BIGFONT_ROW2, "6502");
    delay_sec(1);
    
    /* Contador */
    ssd1306_clear();
    for (i = 0; i < 10; i++) {
        ssd1306_bigchar(56, BIGFONT_CENTER, '0' + i);
        delay(15000);
    }
    
    /* Reloj */
    ssd1306_clear();
    ssd1306_bignum_time_centered(12, 34);
    delay_sec(1);
}

/* ============================================
 * DEMO 4: Gráficos
 * ============================================ */
void demo_graphics(void) {
    uint8_t i;
    
    uart_puts("Demo 4: Graficos\r\n");
    
    /* Líneas horizontales */
    ssd1306_clear();
    ssd1306_text(0, 0, "Lineas:");
    ssd1306_hline(0, 1, 128, 0xFF);
    ssd1306_hline(0, 2, 128, 0xAA);
    ssd1306_hline(0, 3, 128, 0x55);
    delay_sec(1);
    
    /* Rectángulos */
    ssd1306_clear();
    ssd1306_text(0, 0, "Rectangulos:");
    ssd1306_rect(0, 2, 30, 2);
    ssd1306_rect(35, 2, 30, 2);
    ssd1306_rect(70, 2, 30, 2);
    delay_sec(1);
    
    /* Barra de progreso */
    ssd1306_clear();
    ssd1306_text(0, 0, "Progreso:");
    for (i = 0; i <= 100; i += 5) {
        ssd1306_progress_bar(0, 2, 128, i);
        delay(5000);
    }
    delay_sec(1);
    
    /* Iconos */
    ssd1306_clear();
    ssd1306_text(0, 0, "Iconos 8x8:");
    ssd1306_icon8(20, 2, icon_heart);
    ssd1306_icon8(50, 2, icon_star);
    ssd1306_icon8(80, 2, icon_heart);
    ssd1306_icon8(110, 2, icon_star);
    delay_sec(1);
}

/* ============================================
 * DEMO 5: Scroll
 * ============================================ */
void demo_scroll(void) {
    uart_puts("Demo 5: Scroll\r\n");
    
    ssd1306_clear();
    ssd1306_text(0, 0, "  SCROLL DEMO  ");
    ssd1306_text(0, 1, "<<< IZQUIERDA");
    ssd1306_text(0, 2, ">>> DERECHA");
    ssd1306_text(0, 3, "  6502 FPGA  ");
    
    /* Scroll izquierda */
    ssd1306_scroll_left(0, 3, 7);
    delay_sec(2);
    ssd1306_scroll_stop();
    
    /* Scroll derecha */
    ssd1306_scroll_right(0, 3, 7);
    delay_sec(2);
    ssd1306_scroll_stop();
}

/* ============================================
 * DEMO 6: Control display
 * ============================================ */
void demo_control(void) {
    uint8_t i;
    
    uart_puts("Demo 6: Control\r\n");
    
    ssd1306_clear();
    ssd1306_text(0, 0, "Control display");
    ssd1306_text(0, 2, "Contraste...");
    
    /* Bajar contraste */
    for (i = 255; i > 0; i -= 25) {
        ssd1306_set_contrast(i);
        delay(10000);
    }
    /* Subir contraste */
    for (i = 0; i < 255; i += 25) {
        ssd1306_set_contrast(i);
        delay(10000);
    }
    ssd1306_set_contrast(0x8F); /* Normal */
    
    /* Inversión */
    ssd1306_clear();
    ssd1306_text(0, 1, "  Inversion...  ");
    delay_sec(1);
    ssd1306_invert(1);
    delay_sec(1);
    ssd1306_invert(0);
    delay_sec(1);
}

/* ============================================
 * DEMO 7: Framebuffer (píxeles individuales)
 * ============================================ */
#if SSD1306_USE_FRAMEBUFFER
void demo_framebuffer(void) {
    uint8_t i;
    int8_t x, y;
    
    uart_puts("Demo 7: Framebuffer\r\n");
    
    /* Líneas diagonales */
    uart_puts("   Lineas diagonales\r\n");
    fb_clear();
    fb_line(0, 0, 127, 31);     /* Diagonal \\ */
    fb_line(0, 31, 127, 0);     /* Diagonal / */
    fb_flush();
    delay_sec(1);
    
    /* Rectángulo con diagonales */
    fb_clear();
    fb_rect(10, 2, 108, 28);    /* Marco */
    fb_line(10, 2, 117, 29);    /* Diagonal */
    fb_line(10, 29, 117, 2);    /* Diagonal */
    fb_flush();
    delay_sec(1);
    
    /* Círculos */
    uart_puts("   Circulos\r\n");
    fb_clear();
    fb_circle(32, 16, 14);      /* Círculo izquierdo */
    fb_circle(96, 16, 14);      /* Círculo derecho */
    fb_circle(64, 16, 10);      /* Círculo central */
    fb_flush();
    delay_sec(1);
    
#if SSD1306_USE_FB_FILL
    /* Círculos rellenos */
    uart_puts("   Circulos rellenos\r\n");
    fb_clear();
    fb_circle_filled(32, 16, 12);
    fb_circle_filled(64, 16, 8);
    fb_circle_filled(96, 16, 12);
    fb_flush();
    delay_sec(1);
    
    /* Rectángulos rellenos */
    uart_puts("   Rectangulos rellenos\r\n");
    fb_clear();
    fb_rect_filled(5, 4, 30, 24);
    fb_rect_filled(45, 8, 38, 16);
    fb_rect_filled(93, 4, 30, 24);
    fb_flush();
    delay_sec(1);
#endif
    
    /* Animación: círculo moviéndose */
    uart_puts("   Animacion\r\n");
    for (x = 10; x < 118; x += 4) {
        fb_clear();
        fb_circle(x, 16, 8);
        fb_flush();
        delay(3000);
    }
    
#if SSD1306_USE_FB_PLOT
    /* Gráfica de datos */
    uart_puts("   Grafica de datos\r\n");
    fb_clear();
    /* Simular datos tipo senoide */
    for (i = 0; i < 128; i++) {
        /* Onda simple: sube y baja */
        if (i < 32) y = i;
        else if (i < 64) y = 63 - i;
        else if (i < 96) y = i - 64;
        else y = 127 - i;
        fb_set_pixel(i, 31 - (y >> 1));  /* Escalar a 0-31 */
    }
    fb_flush();
    delay_sec(2);
#endif
    
    /* Patrón de píxeles */
    uart_puts("   Patron pixeles\r\n");
    fb_clear();
    for (y = 0; y < 32; y += 2) {
        for (x = 0; x < 128; x += 2) {
            fb_set_pixel(x, y);
        }
    }
    fb_flush();
    delay_sec(1);
}
#endif /* SSD1306_USE_FRAMEBUFFER */

/* ============================================
 * PROGRAMA PRINCIPAL
 * ============================================ */
int main(void) {
    uart_init();
    i2c_init();
    
    uart_puts("\r\n");
    uart_puts("================================\r\n");
    uart_puts("  SSD1306 Driver - Demo Full\r\n");
    uart_puts("  6502 @ Tang Nano 9K\r\n");
    uart_puts("================================\r\n\r\n");
    
    if (!ssd1306_init()) {
        uart_puts("ERROR: SSD1306 no encontrado!\r\n");
        while(1);
    }
    
    uart_puts("SSD1306 inicializado OK\r\n\r\n");
    
    while (1) {
        demo_text();
        demo_numbers();
        demo_bigfont();
        demo_graphics();
        demo_scroll();
        demo_control();
#if SSD1306_USE_FRAMEBUFFER
        demo_framebuffer();
#endif
        
        uart_puts("\r\n--- Reiniciando demo ---\r\n\r\n");
    }
    
    return 0;
}
