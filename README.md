# Demo SSD1306 OLED - 6502 Tang Nano 9K

Demo completo del driver SSD1306 mostrando todas las capacidades del display OLED 128x32 en CPU 6502.

---

## Demos Incluidos

| # | Demo | Descripción |
|---|------|-------------|
| 1 | **Texto** | Fuente 5x7, 4 líneas, texto invertido |
| 2 | **Números** | Decimal, con signo, hexadecimal 8/16 bits |
| 3 | **BigFont** | Caracteres 15x15 px, reloj HH:MM |
| 4 | **Gráficos** | Líneas, rectángulos, barra de progreso, iconos |
| 5 | **Scroll** | Scroll horizontal izquierda/derecha |
| 6 | **Control** | Fade de contraste, inversión de pantalla |
| 7 | **Framebuffer** | Líneas diagonales, círculos, animación, gráficas |

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

### 2. Clonar librerías en `libs/`

```bash
cd libs
git clone https://github.com/nelsama/lcd_ssd1306-i2c-6502-cc65.git ssd1306
```

### 3. Agregar librerías I2C y UART

Copiar manualmente los drivers I2C y UART a:
- `libs/i2c/`
- `libs/uart/`

---

## Compilación

### Requisitos

- [cc65](https://cc65.github.io/) - Compilador C para 6502
- Python 3 - Para script de conversión
- Make

### Compilar

```bash
make
```

Genera:
- `output/rom.bin` - ROM binaria
- `output/rom.vhd` - ROM en VHDL para FPGA

### Limpiar

```bash
make clean
```

### Cargar en FPGA

1. Copiar `output/rom.vhd` al proyecto FPGA
2. Sintetizar con Gowin IDE
3. Programar Tang Nano 9K

---

## Estructura del Proyecto

```
test_lcd-ssd1306_6502_TN-9k/
├── src/
│   ├── main.c              # Demo completo (7 secciones)
│   └── main_clock.c        # Ejemplo reloj simple
├── libs/                   # Librerías (no incluidas)
│   ├── ssd1306/            # Driver OLED (clonar)
│   ├── i2c/                # Driver I2C (agregar)
│   └── uart/               # Driver UART debug (agregar)
├── config/
│   └── fpga.cfg            # Configuración linker cc65
├── scripts/
│   └── bin2rom3.py         # Conversor BIN → VHDL
├── build/                  # Archivos compilados
├── output/                 # ROM generada
├── makefile                # Compilación principal
├── makefile_clock          # Solo reloj
└── README.md
```

---

## Descripción de los Demos

### Demo 1: Texto 5x7

```
┌──────────────────────────┐
│Texto normal 5x7          │
│Segunda linea             │
│!@#$%^&*()                │
│abcdefghijklmnop          │
└──────────────────────────┘
```

- 4 líneas de texto
- Caracteres ASCII 32-126
- Texto invertido (resaltado)

### Demo 2: Números

```
┌──────────────────────────┐
│Decimal:    12345         │
│Negativo:   -9876         │
│Hex 8b:     AB            │
│Hex 16b:    CAFE          │
└──────────────────────────┘
```

- Números decimales sin signo
- Números con signo (-32768 a 32767)
- Hexadecimal 8 y 16 bits

### Demo 3: BigFont 15x15 px

```
┌──────────────────────────┐
│                          │
│       ██  █████          │
│       ██      █          │  "12:34"
│       ██   ████          │
│       ██      █          │
│       ██  █████          │
└──────────────────────────┘
```

- Dígitos 0-9 grandes
- Letras A-Z (BIGNUM_LETTERS)
- Símbolos: `:` `-` `.`
- Funciones de reloj HH:MM y HH:MM:SS

### Demo 4: Gráficos

```
┌──────────────────────────┐
│Lineas:                   │
│████████████████████████  │ ← Sólida
│█ █ █ █ █ █ █ █ █ █ █ █  │ ← Punteada
│ █ █ █ █ █ █ █ █ █ █ █ █ │ ← Alternada
└──────────────────────────┘
```

- Líneas horizontales con patrones
- Rectángulos
- Barra de progreso animada
- Iconos 8x8 (corazón, estrella)

### Demo 5: Scroll

```
┌──────────────────────────┐
│  SCROLL DEMO  ←←←        │
│<<< IZQUIERDA             │
│>>> DERECHA               │
│  6502 FPGA               │
└──────────────────────────┘
```

- Scroll horizontal por hardware
- Velocidad configurable (0-7)
- Izquierda y derecha

### Demo 6: Control

- **Contraste**: Fade out / fade in (0-255)
- **Inversión**: Parpadeo blanco/negro
- Restauración a valores normales

### Demo 7: Framebuffer

```
┌──────────────────────────┐
│╲                       ╱ │
│  ╲                   ╱   │  Líneas diagonales
│    ╲               ╱     │
│      ╲           ╱       │
└──────────────────────────┘

┌──────────────────────────┐
│      ●●●●                │
│    ●      ●     ●●●      │  Círculos
│   ●        ●   ●   ●     │
│    ●      ●     ●●●      │
│      ●●●●                │
└──────────────────────────┘
```

- Líneas diagonales (Bresenham)
- Círculos y círculos rellenos
- Rectángulos rellenos
- Animación (círculo moviéndose)
- Gráfica de datos (onda)
- Patrón de píxeles

---

## Archivos Principales

### main.c

Demo completo con las 7 secciones ejecutándose en bucle infinito.

```c
while (1) {
    demo_text();
    demo_numbers();
    demo_bigfont();
    demo_graphics();
    demo_scroll();
    demo_control();
    demo_framebuffer();  // Requiere FRAMEBUFFER=1
}
```

### main_clock.c

Ejemplo simple de reloj con BigFont:

```c
while (1) {
    ssd1306_bignum_time_centered(horas, minutos);
    delay(1000);
    // Incrementar tiempo...
}
```

---

## Configuración del Driver

El demo usa la configuración completa. Para proyectos propios, editar `libs/ssd1306/ssd1306_config.h`:

### Solo lo que usa el demo

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
#define SSD1306_USE_RECT            1
#define SSD1306_USE_PROGRESS        1
#define SSD1306_USE_ICONS           1
#define SSD1306_USE_SCROLL          1
#define SSD1306_USE_CONTROL         1
#define SSD1306_USE_FRAMEBUFFER     1
#define SSD1306_USE_FB_LINE         1
#define SSD1306_USE_FB_CIRCLE       1
#define SSD1306_USE_FB_FILL         1
#define SSD1306_USE_FB_PLOT         1
```

### Para reducir ROM (solo reloj)

```c
#define SSD1306_USE_CORE            1
#define SSD1306_USE_BIGNUM          1
// Todo lo demás en 0
```

---

## Dependencias

| Librería | Repositorio | Descripción |
|----------|-------------|-------------|
| **ssd1306** | [lcd_ssd1306-i2c-6502-cc65](https://github.com/nelsama/lcd_ssd1306-i2c-6502-cc65) | Driver OLED modular |
| **i2c** | (manual) | Driver I2C para 6502 |
| **uart** | (manual) | Driver UART para debug |

---

## Tamaño del Demo

| Configuración | ROM | RAM |
|---------------|-----|-----|
| Demo completo (todo activado) | ~8 KB | ~640 B |
| Solo reloj BigFont | ~2 KB | 0 |

---

## Licencia

MIT License - Libre para uso personal y comercial.

---

## Enlaces

- **Driver SSD1306**: https://github.com/nelsama/lcd_ssd1306-i2c-6502-cc65
- **Este demo**: https://github.com/nelsama/test_lcd-ssd1306_6502_TN-9k
