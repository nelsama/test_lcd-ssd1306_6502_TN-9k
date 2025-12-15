/**
 * main_features_demo.c - Demo de características SSD1306 (sin framebuffer)
 * 
 * Demuestra: Texto, Números, BigFont, Gráficos, Scroll, Control
 * 
 * ROM estimada: ~6 KB
 * RAM: ~0 bytes (sin framebuffer)
 */

#include <stdint.h>
#include "ssd1306/ssd1306.h"
#include "i2c/i2c.h"

/* ============================================
 * DELAYS
 * ============================================ */
static void delay(uint16_t ms) {
    volatile uint16_t i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 150; j++) { }
    }
}

static void delay_long(uint16_t x100ms) {
    uint16_t i;
    for (i = 0; i < x100ms; i++) {
        delay(100);
    }
}

/* ============================================
 * DEMO 1: TEXTO 5x7
 * ============================================ */
static void demo_text(void) {
    ssd1306_clear();
    ssd1306_text(0, 0, "Driver SSD1306");
    ssd1306_text(0, 1, "Tang Nano 9K");
    ssd1306_text(0, 2, "CPU: 6502");
    ssd1306_text(0, 3, "!@#$%^&*()+-=");
    delay_long(25);
    
    /* Texto invertido */
    ssd1306_clear();
    ssd1306_text(0, 0, "Normal");
    ssd1306_text_inv(0, 1, "Invertido");
    ssd1306_text(0, 2, "Normal");
    ssd1306_text_inv(0, 3, "Invertido");
    delay_long(25);
}

/* ============================================
 * DEMO 2: NÚMEROS
 * ============================================ */
static void demo_numbers(void) {
    uint16_t i;
    
    ssd1306_clear();
    ssd1306_text(0, 0, "Decimal:");
    ssd1306_number(60, 0, 12345);
    
    ssd1306_text(0, 1, "Negativo:");
    ssd1306_number_signed(60, 1, -9876);
    
    ssd1306_text(0, 2, "Hex 8b:");
    ssd1306_hex8(60, 2, 0xAB);
    
    ssd1306_text(0, 3, "Hex 16b:");
    ssd1306_hex16(60, 3, 0xCAFE);
    
    delay_long(30);
    
    /* Contador animado */
    ssd1306_clear();
    ssd1306_text(0, 1, "Contador:");
    for (i = 0; i < 100; i += 5) {
        ssd1306_text(60, 1, "     ");
        ssd1306_number(60, 1, i * 100);
        delay(150);
    }
    delay_long(10);
}

/* ============================================
 * DEMO 3: BIGFONT 15x15
 * ============================================ */
static void demo_bigfont(void) {
    uint8_t h = 12, m = 34, s = 0;
    uint8_t i;
    
    /* Reloj HH:MM centrado */
    for (i = 0; i < 10; i++) {
        ssd1306_clear();
        ssd1306_bignum_time_centered(h, m);
        delay(1000);
        if (++m >= 60) { m = 0; h++; }
        if (h >= 24) h = 0;
    }
    
    /* Texto grande */
    ssd1306_clear();
    ssd1306_bigtext(20, 0, "6502");
    ssd1306_text(35, 3, "CPU RETRO");
    delay_long(25);
    
    ssd1306_clear();
    ssd1306_bigtext_center("HOLA");
    delay_long(20);
}

/* ============================================
 * DEMO 4: GRÁFICOS
 * ============================================ */
static void demo_graphics(void) {
    uint8_t pct;
    
    /* Líneas */
    ssd1306_clear();
    ssd1306_text(0, 0, "Lineas:");
    ssd1306_hline(0, 1, 128, 0xFF);  /* Sólida */
    ssd1306_hline(0, 2, 128, 0xAA);  /* Punteada */
    ssd1306_hline(0, 3, 128, 0x55);  /* Punteada inversa */
    delay_long(20);
    
    /* Barra de progreso */
    ssd1306_clear();
    ssd1306_text(0, 0, "Cargando...");
    for (pct = 0; pct <= 100; pct += 2) {
        ssd1306_progress_bar(0, 2, 128, pct);
        ssd1306_text(55, 0, "   ");
        ssd1306_number(55, 0, pct);
        ssd1306_text(73, 0, "%");
        delay(40);
    }
    ssd1306_text(0, 0, "Completo!   ");
    delay_long(15);
}

/* ============================================
 * DEMO 5: SCROLL
 * ============================================ */
static void demo_scroll(void) {
    ssd1306_clear();
    ssd1306_text(0, 0, "  SCROLL DEMO  ");
    ssd1306_text(0, 1, "<<< IZQUIERDA");
    ssd1306_text(0, 2, ">>> DERECHA");
    ssd1306_text(0, 3, "  6502 FPGA  ");
    
    /* Scroll izquierda */
    ssd1306_scroll_left(0, 3, 5);
    delay_long(40);
    ssd1306_scroll_stop();
    
    /* Scroll derecha */
    ssd1306_scroll_right(0, 3, 5);
    delay_long(40);
    ssd1306_scroll_stop();
    
    delay_long(10);
}

/* ============================================
 * DEMO 6: CONTROL
 * ============================================ */
static void demo_control(void) {
    uint8_t i;
    
    ssd1306_clear();
    ssd1306_text(0, 1, "Control Demo");
    ssd1306_text(0, 2, "Fade...");
    delay_long(10);
    
    /* Fade out */
    for (i = 255; i > 10; i -= 10) {
        ssd1306_set_contrast(i);
        delay(50);
    }
    
    /* Fade in */
    for (i = 10; i < 255; i += 10) {
        ssd1306_set_contrast(i);
        delay(50);
    }
    
    /* Inversión */
    ssd1306_clear();
    ssd1306_text(0, 1, "Inversion...");
    delay_long(10);
    
    for (i = 0; i < 6; i++) {
        ssd1306_invert(i & 1);
        delay(300);
    }
    ssd1306_invert(0);
    ssd1306_set_contrast(0x8F);  /* Restaurar */
}

/* ============================================
 * MAIN
 * ============================================ */
int main(void) {
    i2c_init();
    
    if (!ssd1306_init()) {
        while (1) { }
    }
    
    ssd1306_clear();
    
    while (1) {
        demo_text();      /* Texto 5x7 normal e invertido */
        demo_numbers();   /* Decimal, negativo, hex */
        demo_bigfont();   /* Reloj HH:MM, texto grande */
        demo_graphics();  /* Líneas, barra de progreso */
        demo_scroll();    /* Scroll izq/der */
        demo_control();   /* Fade, inversión */
    }
    
    return 0;
}
