#ifndef __X86_16_H__
#define __X86_16_H__

/**
 * mov family of instructions
 * @file x86_16/mov.c
 * @returns True if an instruction was consumed
 */
extern int parse_x86_16_mov (void);

/**
 * jump family of instructions (sjmp, jmp, ljmp, call, lcall)
 * @file x86_16/jmp.c
 * @returns True if an instruction was consumed
 */
extern int parse_x86_16_jmp (void);

/**
 * Consume a singlet instruction (instruction -> one byte)
 * @file x86_16/singlet.c
 * @param instruction The name of the instruction to consume
 * @param opcode The opcode to emit
 * @returns True if an instruction was consumed
 */
extern int parse_x86_16_singlet (const char *instruction, int opcode);

/**
 * Consume a string type instruction (movs, cmps, scas, etc)
 * @file x86_16/string.c
 * @returns True if an instruction was consumed
 */
extern int parse_x86_16_string (void);

/**
 * Consume a reservation
 * @file x86_16/reserve.c
 * @returns True if consumed
 */
extern int parse_x86_16_reserve (void);

/**
 * Consume an 8bit register
 * @file x86_16/reg8.c
 * @param reg The register value
 * @returns True if it was consumed
 */
extern int parse_x86_16_reg8 (int *reg);

/**
 * Consume a 16bit register
 * @file x86_16/reg16.c
 * @param reg The register value
 * @returns True if it was consumed
 */
extern int parse_x86_16_reg16 (int *reg);

/**
 * Consume a segment register
 * @file x86_16/sreg.c
 * @param reg The register value
 * @returns True if it was consumed
 */
extern int parse_x86_16_sreg (int *reg);

struct mem16
{
	char modrm;
	char displacement[2];
	char *symbol;
	int   gapType;
};

// A register in the format of a mem16 structure
#define MEM16_REG(reg) (struct mem16){ .modrm=0b11000000|reg, .symbol=NULL }

// Set the command portion of a mem16
#define MEM16_SET_CMD(mem16, cmd) (mem16.modrm|(cmd<<3))

/**
 * Consume a memory address
 * @param mem16 A pointer to the mem16 structure or NULL
 * @param rwx The read/write/execute flags for the gap information (if any)
 * @returns True if a memory address was consumed
 * @file x86_16/mem16.c
 */
extern int parse_x86_16_mem16 (struct mem16 *mem16, int rwx);

/**
 * Free the information from a memory address
 * @param mem16 The memory address
 * @file x86_16/free_mem16.c
 */
extern void free_x86_16_mem16 (struct mem16 *mem16);

/**
 * Emit address information
 * @param mem16 The memory address
 * @file x86_16/emit_mem16.c
 */
extern void emit_x86_16_mem16 (const struct mem16 *mem16);

/**
 * A standard arithmetic instruction: add, xor, sub, etc
 * @param mnemonic the instruction mnemonic
 * @param opcode reg|mem, reg|mem
 * @param immOpcode reg|mem, imm
 * @param immCommand reg|mem, imm
 * @param accOpcode acc, imm
 * @param _signed Is the instruction signed
 * @returns true if the instruction was consumed
 * @file x86_16/arithmetic.c
 */
extern int parse_x86_16_arithmetic (const char *mnemonic, int opcode,
	int immOpcode, int immCommand, int accOpcode, int _signed);

#endif
