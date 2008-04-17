# The C compiler and linker

CC=arm-linux-gcc 
LD=arm-linux-ld
AS=arm-linux-as


DRIVERS=drivers
BOARD=board
UTILITY=utility
TFTP=tftp
	
OBJ_FILES= \
	$(BOARD)/init.o \
	$(BOARD)/isr.o \
	$(BOARD)/main.o \
	$(BOARD)/mmu.o \
	$(BOARD)/retarget.o \
	$(BOARD)/vector.o \
	$(DRIVERS)/adc.o \
	$(DRIVERS)/CS89IOMode.o \
	$(DRIVERS)/dma.o \
	$(DRIVERS)/gpio.o \
	$(DRIVERS)/iic.o \
	$(DRIVERS)/led.o \
	$(DRIVERS)/nand.o \
	$(DRIVERS)/timer.o \
	$(DRIVERS)/uart.o \
	$(DRIVERS)/usb.o \
	$(DRIVERS)/usbEP0.o \
	$(DRIVERS)/usbEP1.o \
	$(DRIVERS)/usbEP3.o \
	$(DRIVERS)/wd.o \
	$(TFTP)/arp.o \
	$(TFTP)/eth.o \
	$(TFTP)/icmp.o \
	$(TFTP)/ip.o \
	$(TFTP)/skbuff.o \
	$(TFTP)/tftp.o \
	$(TFTP)/tftpmain.o \
	$(TFTP)/tftpput.o \
	$(TFTP)/udp.o \
	$(UTILITY)/utility.o \
	$(UTILITY)/printLib.o \
	$(UTILITY)/heap.o \


SRCHEADER= \
	 $(BOARD)/*.h \
	 $(DRIVERS)/*.h \
	 $(UTILITY)/*.h \
	 $(TFTP)/*.h \

LIBPATH=/usr/local/arm/2.95.3/lib/gcc-lib/arm-linux/2.95.3
ARMINC=/usr/local/arm/2.95.3/arm-linux/include
CLIBS = -L$(LIBPATH) -lc -lgcc
CINCFLAG=-I$(BOARD) -I$(DRIVERS) -I$(UTILITY) -I$(TFTP) -I$(ARMINC)
#CFLAGS=-marm -g  $(CINCFLAG)
CFLAGS=-fno-builtin -nostdlib -nostdinc -g -c  $(CINCFLAG)
AFLAGS=-mapcs-32 -EL 
LDFLAGS=-p -X -Tbootloader.lds
OBJCOPYFLAGS = -R .comment -R .stab -R .stabstr

all : biosjy2410
	arm-linux-objcopy -O binary -S biosjy2410 biosjy2410.bin $(OBJCOPYFLAGS)
	
%.o:%.c
	$(CC) $(CFLAGS) $< -o $@

%.o:%.s
	$(AS) $(AFLAGS) $< -o $@
		
biosjy2410 : $(OBJ_FILES)
		$(LD) $(LDFLAGS)  $(OBJ_FILES) -static -o $@ $(CLIBS)
		@touch $@

clean:
	rm -f board/*.o drivers/*.o tftp/*.o utility/*.o biosjy2410 biosjy2410.bin