ENTRY(_init)

SECTIONS
{
	. = 0x500;
	BSS_START = .;
	.bss (NOLOAD) :
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
}
