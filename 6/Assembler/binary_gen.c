#include <string.h>
#include "binary_gen.h"

static Table DEST_TABLE[] = {
    { "",  "000" },
    { "M",   "001" },
    { "D",   "010" },
    { "MD",  "011" },
    { "A",   "100" },
    { "AM",  "101" },
    { "AD",  "110" },
    { "AMD", "111" },
    { NULL, NULL } // end
};

static Table COMP_TABLE[] = {
    { "0", "0101010" },
    { "1", "0111111" },
    { "-1", "0111010" },
    { "D", "0001100" },
    { "A", "0110000" },
    { "M", "1110000" },
    { "!D", "0001101" },
    { "!A", "0110001" },
    { "!M", "1110001" },
    { "-D", "0001111" },
    { "-A", "0110011" },
    { "-M", "1110011" },
    { "D+1", "0011111" },
    { "A+1", "0110111" },
    { "M+1", "1110111" },
    { "D-1", "0001110" },
    { "A-1", "0110010" },
    { "M-1", "1110010" },
    { "D+A", "0000010" },
    { "D+M", "1000010" },
    { "D-A", "0010011" },
    { "D-M", "1010011" },
    { "A-D", "0000111" },
    { "M-D", "1000111" },
    { "D&A", "0000000" },
    { "D&M", "1000000" },
    { "D|A", "0010101" }, 
    { "D|M", "1010101" }
};

static Table JUMP_TABLE[] = {
    { "",  "000" },
    { "JGT", "001" },
    { "JEQ", "010" },
    { "JGE", "011" },
    { "JLT", "100" },
    { "JNE", "101" },
    { "JLE", "110" },
    { "JMP", "111" },
    { NULL, NULL } // end
};

const char* gen_dest(const char *dest) {
    return search_table(DEST_TABLE, dest);
}

const char* gen_comp(const char *comp) {
    return search_table(COMP_TABLE, comp);
}

const char* gen_jump(const char *jump) {
    return search_table(COMP_TABLE, jump);
}

static const char* search_table(Table table[], const char *str) {
    for (int i = 0; table[i].key != NULL; i++) {
        if (strcmp(str, table[i].key) == 0) { // if equal
            return table[i].val;
        }
    }

    // no result
    return NULL;
}
