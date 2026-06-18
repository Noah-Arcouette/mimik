#ifndef __X86_16_H__
#define __X86_16_H__

/**
 * jump family of instructions (sjmp, jmp, ljmp)
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

#endif
