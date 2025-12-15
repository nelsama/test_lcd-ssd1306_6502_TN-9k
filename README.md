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

### Cargar en FPGA
Copiar `output/rom.vhd` al proyecto FPGA y sintetizar.

## Efectos de Luces

El programa ejecuta 4 efectos en bucle infinito:

| Efecto | Descripción |
|--------|-------------|
| Knight Rider | LED que recorre de izquierda a derecha y regresa |
| Llenado | LEDs se llenan desde los extremos hacia el centro |
| Alternado | Parpadeo alternado (010101 ↔ 101010) |
| Contador | Contador binario de 0 a 63 |

## Mapa de Memoria

| Región | Dirección | Tamaño | Descripción |
|--------|-----------|--------|-------------|
| Zero Page | $0002-$00FF | 254 bytes | Variables rápidas |
| RAM | $0100-$3DFF | ~15 KB | RAM principal |
| Stack | $3E00-$3FFF | 512 bytes | Pila del sistema |
| ROM | $8000-$9FF9 | 8 KB | Código del programa |
| Vectores | $9FFA-$9FFF | 6 bytes | NMI, RESET, IRQ |
| I/O | $C000-$C003 | 4 bytes | Puertos de E/S |

## Requisitos

- [cc65](https://cc65.github.io/) - Compilador C para 6502 (instalado en `D:\cc65`)
- Python 3 - Para el script bin2rom3.py
- FPGA Tang Nano 9K (o compatible)
- 6 LEDs conectados a los bits 0-5 del puerto $C001

## Licencia

MIT
