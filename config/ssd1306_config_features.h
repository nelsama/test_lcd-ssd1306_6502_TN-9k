/**
 * ssd1306_config.h - Configuración para Demo Features
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

/* Texto 5x7 */
#define SSD1306_USE_FONT_5X7_FULL   1
#define SSD1306_USE_TEXT            1
#define SSD1306_USE_TEXT_INV        1

/* Números */
#define SSD1306_USE_NUMBERS         1
#define SSD1306_USE_NUMBERS_HEX     1

/* BigFont */
#define SSD1306_USE_BIGNUM          1
#define SSD1306_BIGNUM_LETTERS      1

/* Gráficos directos */
#define SSD1306_USE_GRAPHICS        1
#define SSD1306_USE_PROGRESS        1

/* Extras */
#define SSD1306_USE_SCROLL          1
#define SSD1306_USE_CONTROL         1

/* Framebuffer - Desactivado para este demo */
#define SSD1306_USE_FRAMEBUFFER     0

#endif /* SSD1306_CONFIG_H */
