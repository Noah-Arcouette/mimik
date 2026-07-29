ENTRY(_init)

SECTIONS
{
	. = 0x500;
	BSS_START = .;
	.bss NOLOAD :
	{
		*(*.bss)
	}
	BSS_END = .;

	. = 0x7c00;
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
		*(*.text)
	}
	.data :
	{
		*(*.text)
	}

	. = 0x7e00-2;
	.mbr :
	{
		BYTE(0x55)
		BYTE(0xaa)
	}
}
