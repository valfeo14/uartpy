  
#PROGS   = foo
#OBJECTS = foo.o bar.o

# Shouldn't need to change anything below here...

#OBJDIR = ../obj

#VPATH = $(OBJDIR)

#$(OBJDIR)/%.o : %.c
        #$(COMPILE.c) $< -o $@

#OBJPROG = $(addprefix $(OBJDIR)/, $(PROGS))

#all: $(OBJPROG)

#$(OBJPROG): $(addprefix $(OBJDIR)/, $(OBJECTS))  -nostartfiles -ffreestanding
        #$(LINK.o) $^ $(LDLIBS) -o $@


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

us.elf: $(OBJPROG2) $(OBJPROG1)
	$(COMPILE) -T$(LD) $(OBJPROG2) $(OBJPROG1) $(FLAGS) -L/usr/arm-none-eabi/lib -lc -lg -lm -o us.elf

us.bin: us.elf
	arm-none-eabi-objcopy us.elf us.bin -O binary

flash: us.bin
	st-flash write us.bin 0x08000000


clear:
	rm ./obj/*
	rm us.elf
	rm us.bin