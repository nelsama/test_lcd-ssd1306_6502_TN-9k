# Demo SSD1306 OLED - 6502 Tang Nano 9K

Demos del driver SSD1306 para display OLED 128x32 en CPU 6502.

---

## Demos Disponibles

Este repositorio contiene **2 demos** independientes:

| Demo | Archivo | ROM | RAM | Makefile |
|------|---------|-----|-----|----------|
| **Features** | `main_features_demo.c` | ~7 KB | ~0 B | `makefile_features_demo` |
| **Framebuffer** | `main_fb_demo.c` | ~3 KB | ~640 B | `makefile_fb_demo` |

---

## Compilación

### Requisitos

- [cc65](https://cc65.github.io/) - Compilador C para 6502
- Python 3 - Para script de conversión
- Make

### Demo Features (Texto, Números, BigFont, Scroll, Control)

```bash
make -f makefile_features_demo clean
make -f makefile_features_demo
```

**Características:**
- Texto 5x7 normal e invertido
- Números decimales, negativos, hexadecimales
- BigFont 15x15 (reloj HH:MM, texto grande)
- Líneas con patrones, barra de progreso
- Scroll horizontal izquierda/derecha
- Control de contraste e inversión

---

### Demo Framebuffer (Gráficos a nivel de píxel)

```bash
make -f makefile_fb_demo clean
make -f makefile_fb_demo
```

**Características:**
- Píxeles aleatorios
- Líneas diagonales (Bresenham)
- Rectángulos anidados
- Círculos concéntricos y rellenos
- Animación de pelota rebotando
- Patrón XOR dinámico
- Gráfica con scroll en tiempo real

---

## Configuración Automática

Cada demo tiene su propio archivo de configuración en `config/`:

| Demo | Archivo de configuración |
|------|--------------------------|
| Features | `config/ssd1306_config_features.h` |
| Framebuffer | `config/ssd1306_config_fb.h` |

**El makefile copia automáticamente** el archivo de configuración correcto antes de compilar. **No necesitas modificar la librería**.

### ¿Cómo funciona?

1. Los makefiles copian `config/ssd1306_config_*.h` → `config/ssd1306/ssd1306_config.h`
2. El compilador busca primero en `-Iconfig` antes que en `-Ilibs`
3. La librería usa `#include <ssd1306/ssd1306_config.h>` que encuentra el config local

### Configuración Features (`config/ssd1306_config_features.h`)

```c
#define SSD1306_USE_CORE            1
#define SSD1306_USE_FONT_5X7_FULL   1
#define SSD1306_USE_TEXT            1
#define SSD1306_USE_TEXT_INV        1
#define SSD1306_USE_NUMBERS         1
#define SSD1306_USE_NUMBERS_HEX     1
#define SSD1306_USE_BIGNUM          1
#define SSD1306_BIGNUM_LETTERS      1
#define SSD1306_USE_GRAPHICS        1
#define SSD1306_USE_PROGRESS        1
#define SSD1306_USE_SCROLL          1
#define SSD1306_USE_CONTROL         1
#define SSD1306_USE_FRAMEBUFFER     0   // Desactivado
```

### Configuración Framebuffer (`config/ssd1306_config_fb.h`)

```c
#define SSD1306_USE_CORE            1
#define SSD1306_USE_FRAMEBUFFER     1
#define SSD1306_USE_FB_LINE         1
#define SSD1306_USE_FB_CIRCLE       1
#define SSD1306_USE_FB_FILL         1
#define SSD1306_USE_FB_PLOT         1
// Todo lo demás usa valores por defecto (0)
```

---

## Salida de Compilación

Ambos makefiles generan:
- `output/rom.bin` - ROM binaria
- `output/rom.vhd` - ROM en VHDL para FPGA
- `output/rom.hex` - Formato hexadecimal

---

## Hardware Requerido

| Componente | Especificación |
|------------|----------------|
| CPU | 6502 @ 6.75 MHz |
| FPGA | Tang Nano 9K |
| Display | SSD1306 OLED 128x32 |
| Interfaz | I2C |
| Dirección | 0x3C |

---

## Instalación

### 1. Clonar este repositorio

```bash
git clone https://github.com/nelsama/test_lcd-ssd1306_6502_TN-9k.git
cd test_lcd-ssd1306_6502_TN-9k
```

### 2. Clonar librería SSD1306

```bash
cd libs
git clone https://github.com/nelsama/lcd_ssd1306-i2c-6502-cc65.git ssd1306
```

### 3. Agregar librerías I2C y UART

Copiar manualmente los drivers a:
- `libs/i2c/`
- `libs/uart/`

---

## Estructura del Proyecto

```
test_lcd-ssd1306_6502_TN-9k/
├── src/
│   ├── main_features_demo.c    # Demo Features (~7 KB)
│   ├── main_fb_demo.c          # Demo Framebuffer (~3 KB)
│   ├── startup.s               # Código de arranque
│   └── simple_vectors.s        # Vectores 6502
├── config/
│   ├── fpga.cfg                # Configuración linker cc65
│   ├── ssd1306_config_features.h  # Config para demo Features
│   └── ssd1306_config_fb.h        # Config para demo Framebuffer
├── libs/                       # Librerías (no incluidas)
│   ├── ssd1306/                # Driver OLED (clonar)
│   ├── i2c/                    # Driver I2C (agregar)
│   └── uart/                   # Driver UART (agregar)
├── scripts/
│   └── bin2rom3.py             # Conversor BIN → VHDL
├── build/                      # Archivos compilados
├── output/                     # ROM generada
├── makefile_features_demo      # Compilar demo features
└── makefile_fb_demo            # Compilar demo framebuffer
```

---

## Cargar en FPGA

1. Compilar el demo deseado
2. Copiar `output/rom.vhd` al proyecto FPGA
3. Sintetizar con Gowin IDE
4. Programar Tang Nano 9K

---

## Dependencias

| Librería | Repositorio | Descripción |
|----------|-------------|-------------|
| **ssd1306** | [lcd_ssd1306-i2c-6502-cc65](https://github.com/nelsama/lcd_ssd1306-i2c-6502-cc65) | Driver OLED modular |
| **i2c** | (manual) | Driver I2C para 6502 |
| **uart** | (manual) | Driver UART para debug |

---

## Notas Importantes

⚠️ **Configuración de Memoria**: La RAM debe comenzar en `$0200` o superior en `config/fpga.cfg` para evitar conflictos con el stack de hardware del 6502.

✅ **Cambiar entre demos**: Solo ejecuta el makefile correspondiente. La configuración se aplica automáticamente.

---

## Crear tu Propio Proyecto

Para crear un proyecto nuevo usando esta librería:

1. Crea un archivo `config/ssd1306/ssd1306_config.h` con los módulos que necesites
2. Compila con `-Iconfig -Ilibs` (config primero)
3. La librería usará tu configuración local

Ejemplo mínimo:
```c
#ifndef SSD1306_CONFIG_H
#define SSD1306_CONFIG_H
#define SSD1306_USE_CORE 1
#define SSD1306_USE_TEXT 1
#define SSD1306_USE_FONT_5X7_FULL 1
#endif
```

---

## Licencia

MIT License - Libre para uso personal y comercial.

---

## Enlaces

- **Driver SSD1306**: https://github.com/nelsama/lcd_ssd1306-i2c-6502-cc65
- **Este repositorio**: https://github.com/nelsama/test_lcd-ssd1306_6502_TN-9k
