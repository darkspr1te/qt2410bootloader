# Listening for commands on this PC's tcp port 2331
target remote localhost:2331

# Reset the chip to get to a known state.
monitor reset 1

#
# Disable the watchdog and setup the PLL
#

# WDT_MR, disable watchdog 
monitor long 0x53000000 = 0x00000000
#go to svc mode
monitor reg cpsr = 0x13

# Setup GDB for faster downloads
set remote memory-write-packet-size 1024
set remote memory-write-packet-size fixed
monitor speed auto






