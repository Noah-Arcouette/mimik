ENTRY(_init)

SECTIONS
{
	. = 0x500;
	.bss (NOLOAD) :
	{
		*(*.bss)
	}

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
