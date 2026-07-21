#ifndef __X86_16_H__
#define __X86_16_H__

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
 * Consume an 8bit register
 * @file x86_16/bitwise.c
 * @param reg The register value
 * @returns True if it was consumed
 */
extern int parse_x86_16_reg8 (int *reg);

#endif
