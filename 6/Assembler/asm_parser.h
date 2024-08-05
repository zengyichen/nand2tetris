#ifndef ASM_PARSER_H
#define ASM_PARSER_H

#include <stdbool.h>

typedef enum _INSTRUCTION_TYPE {
    INVALID_INSTRUCTION = 0,
    A_INSTRUCTION, // @abc123
    C_INSTRUCTION, // dest=comp;jump
    L_INSTRUCTION, // (xxx)
} INSTRUCTION_TYPE;

// open file
void init(const char *input_file_name, const char  *output_file_name);

static const size_t BUFSIZE = 128;

// read instruction from stdin, return whether succeed
bool advance(char *instruction);

INSTRUCTION_TYPE get_instruction_type(const char *instruction);

// return xxx for (xxx) or @xxx instruction
char* get_symbol(const char *instruction);

// for dest=comp;jump
char* get_dest(const char *instruction);
char* get_comp(const char *instruction);
char* get_jump(const char *instruction);

#endif
