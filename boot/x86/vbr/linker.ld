ENTRY(_init)

SECTIONS
{
	. = 0x500;
	BSS_START = .;
	.bss NOLOAD :
	{
		*(*.bss)
	}
	BSS_END = 0x7c00;

	. = 0x7c00;
	.init :
	{
		*(*.init)
	}
	.stage1.text :
	{
		stage1/*(*.text)
	}
	.stage1.rodata :
	{
		stage1/*(*.rodata)
	}
	.stage1.data :
	{
		stage1/*(*.data)
	}

	. = 0x7e00;
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
}
