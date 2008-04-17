OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_bootstart)
SECTIONS
{
	. = 0x33A00000;
	. = ALIGN(4);
	.text      :
	{
	  board/init.o	(.text)
	  *(.text)
	}
	. = ALIGN(4);
	.rodata : { *(.rodata) }

	. = ALIGN(4);
	.data : {
		__data_start = .;
		*(.data)
		. = ALIGN(4);
		_edata = .;
	}

	. = ALIGN(4);
	.bss : {
		__bss_start = .;	/* BSS				*/
		*(.bss)
		. = ALIGN(4);
		_end = .;
	}
}