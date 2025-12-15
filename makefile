# Makefile para 6502 OLED SSD1306 - Versión Modular
# Compila main.c con UART, I2C y SSD1306 modular

# ============================================
# DIRECTORIOS
# ============================================
SRC_DIR = src
LIB_DIR = libs
BUILD_DIR = build
OUTPUT_DIR = output
CONFIG_DIR = config
SCRIPTS_DIR = scripts

# ============================================
# HERRAMIENTAS
# ============================================
CC65 = cc65
CA65 = ca65
LD65 = ld65
CL65 = cl65
PYTHON = py

# ============================================
# CONFIGURACIÓN
# ============================================
CONFIG = $(CONFIG_DIR)/fpga.cfg
PLATAFORMA = D:\cc65\lib\none.lib
CFLAGS = -t none -O --cpu 6502

# ============================================
# LIBRERÍAS BASE
# ============================================
UART_DIR = $(LIB_DIR)/uart
I2C_DIR = $(LIB_DIR)/i2c
SSD1306_DIR = $(LIB_DIR)/ssd1306

INCLUDES = -I$(UART_DIR) -I$(I2C_DIR) -I$(SSD1306_DIR)

# ============================================
# ARCHIVOS OBJETO - BASE
# ============================================
MAIN_OBJ = $(BUILD_DIR)/main.o
UART_OBJ = $(BUILD_DIR)/uart.o
I2C_OBJ = $(BUILD_DIR)/i2c.o
STARTUP_OBJ = $(BUILD_DIR)/startup.o
VECTORS_OBJ = $(BUILD_DIR)/simple_vectors.o

# ============================================
# ARCHIVOS OBJETO - SSD1306 MODULAR
# ============================================
SSD1306_CORE_OBJ = $(BUILD_DIR)/ssd1306_core.o
SSD1306_CONTROL_OBJ = $(BUILD_DIR)/ssd1306_control.o
SSD1306_FONT_OBJ = $(BUILD_DIR)/font_5x7_full.o
SSD1306_TEXT_OBJ = $(BUILD_DIR)/ssd1306_text.o
SSD1306_NUMBERS_OBJ = $(BUILD_DIR)/ssd1306_numbers.o
SSD1306_BIGNUM_OBJ = $(BUILD_DIR)/ssd1306_bignum.o
SSD1306_GRAPHICS_OBJ = $(BUILD_DIR)/ssd1306_graphics.o
SSD1306_SCROLL_OBJ = $(BUILD_DIR)/ssd1306_scroll.o
SSD1306_FRAMEBUFFER_OBJ = $(BUILD_DIR)/ssd1306_framebuffer.o

# ============================================
# SELECCIÓN DE MÓDULOS
# Comenta los que no necesites para reducir tamaño
# ============================================
SSD1306_OBJS = $(SSD1306_CORE_OBJ)
SSD1306_OBJS += $(SSD1306_CONTROL_OBJ)
SSD1306_OBJS += $(SSD1306_FONT_OBJ)
SSD1306_OBJS += $(SSD1306_TEXT_OBJ)
SSD1306_OBJS += $(SSD1306_NUMBERS_OBJ)
SSD1306_OBJS += $(SSD1306_BIGNUM_OBJ)
SSD1306_OBJS += $(SSD1306_GRAPHICS_OBJ)
SSD1306_OBJS += $(SSD1306_SCROLL_OBJ)
SSD1306_OBJS += $(SSD1306_FRAMEBUFFER_OBJ)

# Todos los objetos
OBJS = $(MAIN_OBJ) $(UART_OBJ) $(I2C_OBJ) $(STARTUP_OBJ) $(SSD1306_OBJS) $(VECTORS_OBJ)

# ============================================
# TARGET PRINCIPAL
# ============================================
TARGET = $(BUILD_DIR)/main.bin

# Regla por defecto
all: dirs $(TARGET) rom
	@echo ========================================
	@echo COMPILADO EXITOSAMENTE
	@echo ========================================
	@echo VHDL: $(OUTPUT_DIR)/rom.vhd
	@echo ========================================

# Crear directorios
dirs:
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	@if not exist "$(OUTPUT_DIR)" mkdir "$(OUTPUT_DIR)"

# ============================================
# COMPILACIÓN DE OBJETOS
# ============================================

# Main
$(MAIN_OBJ): $(SRC_DIR)/main.c
	$(CL65) -t none $(INCLUDES) -c -o $@ $<

# UART
$(UART_OBJ): $(UART_DIR)/uart.c
	$(CC65) $(CFLAGS) -o $(BUILD_DIR)/uart.s $<
	$(CA65) -t none -o $@ $(BUILD_DIR)/uart.s

# I2C
$(I2C_OBJ): $(I2C_DIR)/i2c.c
	$(CC65) $(CFLAGS) -I$(I2C_DIR) -o $(BUILD_DIR)/i2c.s $<
	$(CA65) -t none -o $@ $(BUILD_DIR)/i2c.s

# Vectores
$(VECTORS_OBJ): $(SRC_DIR)/simple_vectors.s
	$(CA65) -t none -o $@ $<

# Startup
$(STARTUP_OBJ): $(SRC_DIR)/startup.s
	$(CA65) -t none -o $@ $<

# ============================================
# SSD1306 MODULAR
# ============================================

# Core
$(SSD1306_CORE_OBJ): $(SSD1306_DIR)/core/ssd1306_core.c
	$(CC65) $(CFLAGS) -I$(I2C_DIR) -I$(SSD1306_DIR) -o $(BUILD_DIR)/ssd1306_core.s $<
	$(CA65) -t none -o $@ $(BUILD_DIR)/ssd1306_core.s

# Control
$(SSD1306_CONTROL_OBJ): $(SSD1306_DIR)/core/ssd1306_control.c
	$(CC65) $(CFLAGS) -I$(I2C_DIR) -I$(SSD1306_DIR) -o $(BUILD_DIR)/ssd1306_control.s $<
	$(CA65) -t none -o $@ $(BUILD_DIR)/ssd1306_control.s

# Font 5x7 Full
$(SSD1306_FONT_OBJ): $(SSD1306_DIR)/fonts/font_5x7_full.c
	$(CC65) $(CFLAGS) -I$(SSD1306_DIR) -o $(BUILD_DIR)/font_5x7_full.s $<
	$(CA65) -t none -o $@ $(BUILD_DIR)/font_5x7_full.s

# Text
$(SSD1306_TEXT_OBJ): $(SSD1306_DIR)/text/ssd1306_text.c
	$(CC65) $(CFLAGS) -I$(I2C_DIR) -I$(SSD1306_DIR) -o $(BUILD_DIR)/ssd1306_text.s $<
	$(CA65) -t none -o $@ $(BUILD_DIR)/ssd1306_text.s

# Numbers
$(SSD1306_NUMBERS_OBJ): $(SSD1306_DIR)/numbers/ssd1306_numbers.c
	$(CC65) $(CFLAGS) -I$(I2C_DIR) -I$(SSD1306_DIR) -o $(BUILD_DIR)/ssd1306_numbers.s $<
	$(CA65) -t none -o $@ $(BUILD_DIR)/ssd1306_numbers.s

# BigFont (fuente grande pixel art)
$(SSD1306_BIGNUM_OBJ): $(SSD1306_DIR)/bignum/ssd1306_bigfont.c
	$(CC65) $(CFLAGS) -I$(I2C_DIR) -I$(SSD1306_DIR) -o $(BUILD_DIR)/ssd1306_bignum.s $<
	$(CA65) -t none -o $@ $(BUILD_DIR)/ssd1306_bignum.s

# Graphics
$(SSD1306_GRAPHICS_OBJ): $(SSD1306_DIR)/graphics/ssd1306_graphics.c
	$(CC65) $(CFLAGS) -I$(I2C_DIR) -I$(SSD1306_DIR) -o $(BUILD_DIR)/ssd1306_graphics.s $<
	$(CA65) -t none -o $@ $(BUILD_DIR)/ssd1306_graphics.s

# Scroll
$(SSD1306_SCROLL_OBJ): $(SSD1306_DIR)/scroll/ssd1306_scroll.c
	$(CC65) $(CFLAGS) -I$(I2C_DIR) -I$(SSD1306_DIR) -o $(BUILD_DIR)/ssd1306_scroll.s $<
	$(CA65) -t none -o $@ $(BUILD_DIR)/ssd1306_scroll.s

# Framebuffer
$(SSD1306_FRAMEBUFFER_OBJ): $(SSD1306_DIR)/framebuffer/ssd1306_framebuffer.c
	$(CC65) $(CFLAGS) -I$(I2C_DIR) -I$(SSD1306_DIR) -o $(BUILD_DIR)/ssd1306_framebuffer.s $<
	$(CA65) -t none -o $@ $(BUILD_DIR)/ssd1306_framebuffer.s

# ============================================
# ENLAZADO
# ============================================
$(TARGET): $(OBJS)
	$(LD65) -C $(CONFIG) --start-addr 0x8000 -o $@ $(OBJS) $(PLATAFORMA)

# ============================================
# GENERACIÓN DE ROM
# ============================================
rom: $(TARGET)
	$(PYTHON) $(SCRIPTS_DIR)/bin2rom3.py $(TARGET) -s 8192 --name rom --data-width 8 -o $(OUTPUT_DIR)

# ============================================
# LIMPIEZA
# ============================================
clean:
	@if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"
	@if exist "$(OUTPUT_DIR)\*.vhd" del /q "$(OUTPUT_DIR)\*.vhd"
	@if exist "$(OUTPUT_DIR)\*.bin" del /q "$(OUTPUT_DIR)\*.bin"
	@if exist "$(OUTPUT_DIR)\*.hex" del /q "$(OUTPUT_DIR)\*.hex"

# ============================================
# CONFIGURACIONES PRESETS
# ============================================

# Solo reloj (mínimo)
clock: CFLAGS += -DSSD1306_PRESET_CLOCK
clock: all

# Terminal texto
text: CFLAGS += -DSSD1306_PRESET_TEXT
text: all

# ============================================
# AYUDA
# ============================================
help:
	@echo ========================================
	@echo 6502 SSD1306 Modular - Comandos
	@echo ========================================
	@echo   make        - Compilar todo
	@echo   make clean  - Limpiar archivos
	@echo   make help   - Mostrar esta ayuda
	@echo ========================================
	@echo.
	@echo Modulos SSD1306 (editar Makefile):
	@echo   SSD1306_CORE_OBJ     - Core (obligatorio)
	@echo   SSD1306_CONTROL_OBJ  - Contraste, inversion
	@echo   SSD1306_FONT_OBJ     - Fuente 5x7
	@echo   SSD1306_TEXT_OBJ     - Texto
	@echo   SSD1306_NUMBERS_OBJ  - Numeros
	@echo   SSD1306_BIGNUM_OBJ   - Numeros grandes
	@echo   SSD1306_GRAPHICS_OBJ - Graficos
	@echo   SSD1306_SCROLL_OBJ   - Scroll
	@echo ========================================

.PHONY: all dirs rom clean help clock text
