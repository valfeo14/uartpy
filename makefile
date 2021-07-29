


OBJECTS1 = startup_stm32f10x_md.o stm32f10x_rcc.o stm32f10x_gpio.o stm32f10x_usart.o system_stm32f10x.o misc.o
OBJECTS2 = main.o ur.o
SOUR = main.c ur.c stm32f10x_rcc.c stm32f10x_gpio.c stm32f10x_usart.c startup_stm32f10x_md.s misc.c
COMPILE = arm-none-eabi-gcc
FLAGS = -nostartfiles -ffreestanding -Wall -mthumb -mcpu=cortex-m3 -I/myc/stm/need/inc/
LINK = arm-none-eabi-ld
LINKFLAGS = -T

SRCDIR = ./src
OBJDIR = ./obj
OBJDIRNEED = /myc/stm/need/obj
INCDIR = ./inc
VPATH = $(INCDIR)
OBJPROG1 = $(addprefix $(OBJDIRNEED)/, $(OBJECTS1))
OBJPROG2 = $(addprefix $(OBJDIR)/, $(OBJECTS2))
LD = /myc/stm/need/mem1.ld

all: flash
./obj/main.o: main.c
	$(COMPILE) $(FLAGS) -c main.c -o $(OBJDIR)/main.o

./obj/ur.o: ./src/ur.c
	$(COMPILE) $(FLAGS) -c $(SRCDIR)/ur.c -o $(OBJDIR)/ur.o

usp.elf: $(OBJPROG2) $(OBJPROG1)
	$(COMPILE) -T$(LD) $(OBJPROG2) $(OBJPROG1) $(FLAGS) -L/usr/arm-none-eabi/lib -lc -lg -lm -o usp.elf

usp.bin: usp.elf
	arm-none-eabi-objcopy usp.elf usp.bin -O binary

flash: usp.bin
	st-flash write usp.bin 0x08000000


clear:
	rm ./obj/*
	rm usp.elf
	rm usp.bin
