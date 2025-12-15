/**
 * ssd1306_config.h - Configuración para Demo Framebuffer
 * 
 * Este archivo sobrescribe los valores por defecto de la librería.
 * Compilar con: -Iconfig ANTES de -Ilibs
 */

#ifndef SSD1306_CONFIG_H
#define SSD1306_CONFIG_H

/* Hardware */
#define SSD1306_ADDR        0x3C
#define SSD1306_WIDTH       128
#define SSD1306_HEIGHT      32
#define SSD1306_PAGES       4

/* Core - Obligatorio */
#define SSD1306_USE_CORE            1

/* Framebuffer - Completo */
#define SSD1306_USE_FRAMEBUFFER     1
#define SSD1306_USE_FB_LINE         1
#define SSD1306_USE_FB_CIRCLE       1
#define SSD1306_USE_FB_FILL         1
#define SSD1306_USE_FB_PLOT         1

/* Todo lo demás desactivado por defecto en la librería */

#endif /* SSD1306_CONFIG_H */
