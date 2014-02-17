# You need to set the five variables below correctly for your system and chipKIT board.

# Path to chipKIT C compiler
TOOLCHAIN_PREFIX=/Applications/mpide.app/Contents/Resources/Java/hardware/pic32/compiler/pic32-tools
# Path to chipKIT avrdude
AVRTOOLS_PREFIX=/Applications/Mpide.app/Contents/Resources/Java/hardware/tools/avr/
# Serial port used to upload image with avrdude
SERIAL_PORT=/dev/tty.usbserial-AD01PNED
# PIC32 CPU model
CPUTYPE=32MX150F128D
CPUCLK=80000000L

# optimization for C source disabled with -O0 for better dissassembly from gdb
CFLAGS=-O0  -c  -mno-smart-io  -w  -fno-exceptions  -ffunction-sections  -fdata-sections  -g  -mdebugger  -Wcast-align  -fno-short-double  -mprocessor=$(CPUTYPE)  -DF_CPU=$(CPUCLK)
ASFLAGS=-g1  -c  -mprocessor=$(CPUTYPE)  -DF_CPU=$(CPUCLK)
LDFLAGS=-Os  -Wl,--gc-sections  -mdebugger  -mprocessor=$(CPUTYPE) -Dmpide.version=1
# linker script
LDSCRIPT=chipKIT-application-32MX150F128.ld

CC=$(TOOLCHAIN_PREFIX)/bin/pic32-gcc
LD=$(CC)
AR=$(TOOLCHAIN_PREFIX)/bin/pic32-ar
BIN2HEX=$(TOOLCHAIN_PREFIX)/bin/pic32-bin2hex

AVRDUDE=$(AVRTOOLS_PREFIX)/bin/avrdude 
AVRDUDEFLAGS=-C$(AVRTOOLS_PREFIX)/etc/avrdude.conf -c stk500v2 -p pic32 -P $(SERIAL_PORT) -b 115200 -v -U 

OBJDIR=obj

all: build arstartup main.elf hex burn

build: $(OBJDIR)/crt0.o $(OBJDIR)/crti.o $(OBJDIR)/crtn.o $(OBJDIR)/main.o

$(OBJDIR)/crt0.o:
	$(CC) $(CFLAGS) -o $(OBJDIR)/crt0.o startup/crt0.S

$(OBJDIR)/crti.o:
	$(CC) $(CFLAGS) -o $(OBJDIR)/crti.o startup/crti.S

$(OBJDIR)/crtn.o:
	$(CC) $(CFLAGS) -o $(OBJDIR)/crtn.o startup/crtn.S

$(OBJDIR)/main.o:
	$(CC) $(CFLAGS) -o $(OBJDIR)/main.o main.c

clean:
	rm -rf $(OBJDIR)/*
	rm -f main.hex
	rm -f main.elf

arstartup: $(OBJDIR)/crti.o $(OBJDIR)/crt0.o $(OBJDIR)/crtn.o
	$(AR) rcs $(OBJDIR)/startup.a $(OBJDIR)/crt0.o
	$(AR) rcs $(OBJDIR)/startup.a $(OBJDIR)/crti.o
	$(AR) rcs $(OBJDIR)/startup.a $(OBJDIR)/crtn.o

main.elf: $(OBJDIR)/startup.a $(OBJDIR)/main.o
	$(LD) $(LDFLAGS) -o main.elf $(OBJDIR)/main.o $(OBJDIR)/startup.a -lm -T $(LDSCRIPT)

hex: main.elf 
	$(BIN2HEX) -a main.elf

burn:
	$(AVRDUDE) $(AVRDUDEFLAGS) flash:w:main.hex:i

