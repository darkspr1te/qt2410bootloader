This bootloader support TFTP upgrade and USB upgrade. Very easy to use, even if you dont know what a embedded system is.

Quick install steps:


1. Download Image pack from download section

2. Install GIVE IO driver

3. connect wriggler , parallel port between your QT2410 board and computer

4. Use biosjy.bat to burn bootloader.bin, and then enjoy

5. If you want to use usb firmware upgrade, please use the USB host driver(WDM) at computer

side. DNW is the windows UI software which can do bulk transfer with our usb firmware

upgrade  program

New release for GNU toolchain support. You can check out from

http://qt2410bootloader.googlecode.com/svn/GNUTrunk/BIOSJY2410

Please compile the BIOSJY2410 GNU source with YAGATO toolchain

http://www.yagarto.de/index.html