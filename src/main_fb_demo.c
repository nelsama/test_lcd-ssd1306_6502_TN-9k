/**
 * main_fb_demo.c - Demo del Framebuffer SSD1306
 */

#include <stdint.h>
#include "../libs/uart/uart.h"
#include "../libs/i2c/i2c.h"
#include "../libs/ssd1306/ssd1306.h"

/* ============================================
 * DELAY
 * ============================================ */
static void delay(uint16_t count) {
    volatile uint16_t i;
    for (i = 0; i < count; i++);
}

static void delay_sec(uint8_t sec) {
    while (sec--) {
        delay(20000);
    }
}

/* ============================================
 * DEMO 1: Píxeles
 * ============================================ */
static void demo_pixels(void) {
    uint8_t x, y;
    
    uart_puts("D1\r\n");
    fb_clear();
    
    for (x = 0; x < 128; x += 4) {
        y = (x / 4) % 32;
        fb_set_pixel(x, y);
    }
    for (x = 0; x < 128; x += 2) {
        fb_set_pixel(x, 0);
        fb_set_pixel(x, 31);
    }
    for (y = 0; y < 32; y += 2) {
        fb_set_pixel(0, y);
        fb_set_pixel(127, y);
    }
    
    fb_flush();
    delay_sec(2);
}

/* ============================================
 * DEMO 2: Líneas
 * ============================================ */
#if SSD1306_USE_FB_LINE
static void demo_lines(void) {
    uint8_t i;
    
    uart_puts("D2\r\n");
    fb_clear();
    for (i = 0; i < 128; i += 16) {
        fb_line(0, 0, i, 31);
    }
    for (i = 0; i < 32; i += 8) {
        fb_line(0, 0, 127, i);
    }
    fb_flush();
    delay_sec(2);
    
    uart_puts("D3\r\n");
    fb_clear();
    for (i = 0; i < 14; i += 3) {
        fb_rect(i, i/2, 128 - i*2, 32 - i);
    }
    fb_flush();
    delay_sec(2);
}
#endif

/* ============================================
 * DEMO 3: Círculos
 * ============================================ */
#if SSD1306_USE_FB_CIRCLE
static void demo_circles(void) {
    uint8_t r;
    
    uart_puts("D4\r\n");
    fb_clear();
    for (r = 3; r < 16; r += 3) {
        fb_circle(64, 16, r);
    }
    fb_flush();
    delay_sec(2);
    
#if SSD1306_USE_FB_FILL
    uart_puts("D5\r\n");
    fb_clear();
    fb_circle_filled(25, 16, 10);
    fb_circle_filled(64, 16, 12);
    fb_circle_filled(103, 16, 10);
    fb_flush();
    delay_sec(2);
#endif
}
#endif

/* ============================================
 * DEMO 4: Rebote
 * ============================================ */
static void demo_bounce(void) {
    int8_t x = 10, y = 10;
    int8_t dx = 2, dy = 1;
    uint8_t i;
    
    uart_puts("D6\r\n");
    
    for (i = 0; i < 60; i++) {
        fb_clear();
        fb_set_pixel(x, y);
        fb_set_pixel(x+1, y);
        fb_set_pixel(x, y+1);
        fb_set_pixel(x+1, y+1);
#if SSD1306_USE_FB_LINE
        fb_rect(0, 0, 128, 32);
#endif
        fb_flush();
        
        x += dx;
        y += dy;
        if (x <= 1 || x >= 125) dx = -dx;
        if (y <= 1 || y >= 29) dy = -dy;
        
        delay(300);
    }
}

/* ============================================
 * DEMO 5: Patrón
 * ============================================ */
static void demo_pattern(void) {
    uint8_t frame, x, y;
    
    uart_puts("D7\r\n");
    
    for (frame = 0; frame < 16; frame++) {
        fb_clear();
        for (y = 0; y < 32; y++) {
            for (x = 0; x < 128; x++) {
                if (((x + frame) ^ (y + frame)) & 0x04) {
                    fb_set_pixel(x, y);
                }
            }
        }
        fb_flush();
        delay(2000);
    }
}

/* ============================================
 * DEMO 6: Gráfica
 * ============================================ */
#if SSD1306_USE_FB_PLOT
static void demo_plot(void) {
    uint8_t i;
    static uint8_t val = 16;
    static int8_t dir = 1;
    
    uart_puts("D8\r\n");
    
    for (i = 0; i < 100; i++) {
        val += dir;
        if (val >= 28 || val <= 4) dir = -dir;
        val += (i & 1) ? 1 : -1;
        
        fb_plot_scroll(val, 0, 31);
        fb_flush();
        delay(500);
    }
}
#endif

/* ============================================
 * MAIN
 * ============================================ */
int main(void) {
    uart_init();
    i2c_init();
    
    uart_puts("\r\nFB\r\n");
    
    ssd1306_init();
    fb_init();
    
    while (1) {
        demo_pixels();
        
#if SSD1306_USE_FB_LINE
        demo_lines();
#endif

#if SSD1306_USE_FB_CIRCLE
        demo_circles();
#endif
        
        demo_bounce();
        demo_pattern();
        
#if SSD1306_USE_FB_PLOT
        demo_plot();
#endif
        
        uart_puts("--\r\n");
        delay_sec(1);
    }
    
    return 0;
}
