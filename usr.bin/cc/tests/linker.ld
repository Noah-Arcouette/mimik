ENTRY(_init)

SECTIONS
{
	. = 0x500;
	BSS_START = .;
	.bss NOLOAD :
	{
		*(*.bss)
	}
	BSS_END = 0x600;

	. = 0x600;
	.init :
	{
		*(*.init)
	}

	.text :
	{
		*(*.text)
	}
	.rodata :
	{
		*(*.rodata)
	}
	.data :
	{
		*(*.data)
	}

	MBR_PART1 = 0x1be+0x600;
}
