# Demo SSD1306 OLED - 6502 Tang Nano 9K

Demo completo del driver SSD1306 para display OLED 128x32 en CPU 6502.

## Características del Demo

- ✅ **Texto 5x7** - 4 líneas, texto normal e invertido
- ✅ **Números** - Decimal, con signo, hexadecimal 8/16 bits
- ✅ **BigFont 15x15px** - Dígitos, letras A-Z, reloj HH:MM
- ✅ **Gráficos** - Líneas, rectángulos, barra de progreso, iconos 8x8
- ✅ **Scroll** - Horizontal izquierda/derecha
- ✅ **Control** - Contraste, inversión de pantalla

## Hardware

| Componente | Especificación |
|------------|----------------|
| CPU | 6502 @ 6.75 MHz |
| FPGA | Tang Nano 9K |
| Display | SSD1306 OLED 128x32 I2C |
| Dirección I2C | 0x3C |

## Dependencias

Este proyecto requiere las siguientes librerías en `libs/`:

| Librería | Repositorio |
|----------|-------------|
| **ssd1306** | https://github.com/nelsama/lcd_ssd1306-i2c-6502-cc65 |
| **i2c** | (incluir manualmente) |
| **uart** | (incluir manualmente) |

### Clonar librerías

```bash
cd libs
git clone https://github.com/nelsama/lcd_ssd1306-i2c-6502-cc65.git ssd1306
```

## Estructura

```
test_lcd-ssd1306_6502_TN-9k/
├── src/
│   ├── main.c              # Demo completo de todas las funciones
│   └── main_clock.c        # Ejemplo de reloj
├── libs/                   # Librerías (no incluidas, ver Dependencias)
│   ├── ssd1306/            # Driver display OLED
│   ├── i2c/                # Driver I2C
│   └── uart/               # Driver UART (debug)
├── config/
│   └── fpga.cfg            # Configuración linker cc65
├── scripts/
│   └── bin2rom3.py         # Conversor BIN → VHDL
└── makefile                # Compilación
```

## Compilación

### Requisitos
- [cc65](https://cc65.github.io/) instalado
- Python 3
- Librerías clonadas en `libs/`

### Compilar
```bash
make
```

### Limpiar
```bash
make clean
```

## Capturas del Demo

El demo ejecuta 6 secciones en bucle:

1. **Texto** - Caracteres ASCII, texto invertido
2. **Números** - Decimal 12345, negativo -9876, hex 0xCAFE
3. **BigFont** - "HOLA", "6502", reloj 12:34
4. **Gráficos** - Líneas, rectángulos, barra de progreso, iconos
5. **Scroll** - Texto desplazándose izquierda/derecha
6. **Control** - Fade de contraste, inversión de pantalla

## Licencia

MIT License
