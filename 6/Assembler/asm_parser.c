#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "asm_parser.h"

void init(const char* input_file_name, const char* output_file_name) {
    freopen(input_file_name, "r", stdin);
    freopen(output_file_name, "w", stdout);
}

bool advance(char *instruction) {
    char *buf;

    buf = (char*) malloc(BUFSIZE * sizeof(char));

    while (fgets(buf, BUFSIZE, stdin)) {
        // remove space and newline
        char *buf_ptr = buf, *instruction_ptr = instruction;

        while (*buf_ptr != '\0') {
            if (*(buf_ptr + 1) != '\0' && // not the end
                *buf_ptr == '/' && *(buf_ptr + 1) == '/') { // is comment
                break;
            }

            if (*buf_ptr != ' ' && *buf_ptr != '\n') {
                *instruction_ptr = *buf_ptr;
                instruction_ptr++;
            }

            buf_ptr++;
        }

        *instruction_ptr = '\0';

        // read until the line isnt empty
        if (strlen(instruction)) break;
    }

    free(buf);

    if (feof(stdin)) return false;
    return true;
}

INSTRUCTION_TYPE get_instruction_type(const char *instruction) {
    switch (instruction[0]) {
        case '@':
            return A_INSTRUCTION;
        case '(':
            return L_INSTRUCTION;
        default:
            return C_INSTRUCTION;
    }
}

char* get_symbol(const char *instruction) {
    INSTRUCTION_TYPE type = get_instruction_type(instruction);

    if (type != A_INSTRUCTION && type != L_INSTRUCTION) {
        return NULL;
    }

    size_t len = strlen(instruction);
    char *res = (char*) malloc(len * sizeof(char));

    if (get_instruction_type(instruction) == A_INSTRUCTION) {
        for (int i = 0; i < len - 1; i++) {
            res[i] = instruction[1 + i];
        }
        res[len - 1] = '\0';
    }

    if (get_instruction_type(instruction) == L_INSTRUCTION) {
        for (int i = 0; i + 1 < len - 1; i++) {
            res[i] = instruction[1 + i];
        }
        res[len - 2] = '\0';
    }

    return res;
}

char* get_dest(const char *instruction) {
    const char *end_ptr = instruction;

    while (*end_ptr != '\0' && *end_ptr != '=') {
        end_ptr++;
    }

    if (*end_ptr == '\0') { // return empty string
        char *res = (char*) malloc(sizeof(char));
        *res = '\0';
        return res;
    }

    char *res = (char*) malloc((end_ptr - instruction + 3) * sizeof(char));
    const char *instruction_ptr = instruction;
    char *res_ptr = res;

    for (; instruction_ptr != end_ptr; ) {
        *(res_ptr++) = *(instruction_ptr++);
    }

    *res_ptr = '\0';

    return res;
}

char* get_comp(const char *instruction) {
    const char *sec1_ptr = instruction, *sec2_ptr = instruction;

    while (*sec1_ptr != '\0' && *sec1_ptr != '=') {
        sec1_ptr++;
    }

    while (*sec2_ptr != '\0' && *sec2_ptr != ';') {
        sec2_ptr++;
    }

    const char *begin_ptr;
    const char *end_ptr = sec2_ptr;

    if (*sec1_ptr == '\0') { // comp;jump
        begin_ptr = instruction;
    } else { // dest=comp;jump
        begin_ptr = sec1_ptr + 1;
    }

    char *res = (char*) malloc((end_ptr - begin_ptr + 3) * sizeof(char));
    const char *instruction_ptr = begin_ptr;
    char *res_ptr = res;

    while (instruction_ptr != end_ptr) {
        *(res_ptr++) = *(instruction_ptr++);
    }

    *res_ptr = '\0';

    return res;
}

char* get_jump(const char *instruction) {
    const char *begin_ptr = instruction;

    while (*begin_ptr != '\0' && *begin_ptr != ';') {
        begin_ptr++;
    }

    if (*begin_ptr == '\0') { // return empty string
        char *res = (char*) malloc(sizeof(char));
        *res = '\0';
        return res;
    }

    begin_ptr++;
    char *res = (char*) malloc((strlen(begin_ptr) + 3) * sizeof(char));
    const char *instruction_ptr = begin_ptr;
    char *res_ptr = res;

    while (*instruction_ptr != '\0') {
        *(res_ptr++) = *(instruction_ptr++);
    }

    *res_ptr = '\0';

    return res;
}
