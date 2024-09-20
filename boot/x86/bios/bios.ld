OUTPUT_ARCH(i386)
ENTRY(boot_init)

/*
 * The payload is placed in the MBR break
 * By convension the MBR break leaves 2024 sectors
 * Make sure the payload fits in those regions
 */

MEMORY
{
	BSS    (rw) : ORIGIN = 0x0500, LENGTH = 0x1000
	BOOT   (rx) : ORIGIN = 0x7c00, LENGTH = 0x0200
	TEXT   (x)  : ORIGIN = 0x7e00, LENGTH = 0x2000
	DATA   (rw) : ORIGIN = 0x9e00, LENGTH = 0x1000
	RODATA (r)  : ORIGIN = 0xae00, LENGTH = 0x1000
	PAD    (r)  : ORIGIN = 0xbe00, LENGTH = 0x0001
}

PHDRS
{
	bss    PT_LOAD;
	boot   PT_LOAD;
	text   PT_LOAD;
	data   PT_LOAD;
	rodata PT_LOAD;
	pad    PT_LOAD;
}

SECTIONS
{
	BSS_START = ORIGIN(BSS);
	BSS_END   = ORIGIN(BSS)+LENGTH(BSS);
	.bss (NOLOAD) : {
		*(.bss*)
	} >BSS :bss

	.boot : { /* Boot sector */
		*(.boot.init)
		*(.boot)
	} >BOOT :boot

	/* Where the stage two will be loaded to */
	STAGE_TWO_START = 0x7e00;

	.text : {
		*(.text*)
	} >TEXT :text =0

	.data : {
		*(.data*)
	} >DATA :data =0

	.rodata : {
		*(.rodata*)
	} >RODATA :rodata =0

	/* Pad to the nearest sector */
	.padding : {
		BYTE(225)
	} >PAD :pad

	STAGE_TWO_END = .;
	STAGE_TWO_SECTORS = (STAGE_TWO_END-STAGE_TWO_START)/512; /* Amount of sector in the stage two */

	.shstrtab : { /* Please don't corrupt the ELF and discard these */
		*(.shstrtab)
	}
	.comment : {
		*(.comment)
	}

	/DISCARD/ : {
		*(.note.gnu.property)
		/* *(*) */
	}
}
