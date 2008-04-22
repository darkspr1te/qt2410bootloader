OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
	. = 0x33600000;
	. = ALIGN(4);
	.text      :
	{
	  board/init.o	(.text)
	  board/vector.o (.text)
	  *(.text)
	}
	. = ALIGN(4);
	.rodata : { 
	*(.rodata) 
	etext = .;
  _etext = .; 
	}
	
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
	.heap    :
  {
    PROVIDE( startHeap = . );
    *(.heap)
    . += 0x100000;
    PROVIDE (heap_limit = . );
    PROVIDE( endHeap = . );
    PROVIDE (end = .);
    PROVIDE (__end__ = .);
  }
}