#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"
#include "binary_gen.h"
#include "symbol_table.h"

static const char* INPUT_FILE_NAME = "Prog.asm";
static const char* OUTPUT_FILE_NAME = "Prog.hack";

int main(int argc, char *argv[]) {
    freopen(INPUT_FILE_NAME, "r", stdin);

    char instruction[BUFSIZE];

    ADDRESS instruction_address = 0, variable_address = 16;

    // "2-pass"

    // 1. read label symbol and build hash table

    init_symbols();

    while (advance(instruction)) {
        INSTRUCTION_TYPE type = get_instruction_type(instruction);
        
        switch (type) {
            case A_INSTRUCTION:
                instruction_address++;
                break;
            case C_INSTRUCTION:
                instruction_address++;
                break;
            case L_INSTRUCTION: {
                char *symbol = get_symbol(instruction);

                if (!is_valid_symbol(symbol)) {
                    printf("Invalid symbol on line %d.\n", instruction_address);
                    return 1;
                }

                bool succeed = insert_symbol(symbol, instruction_address);

                if (!succeed) { // lable symbols cant repeat
                    printf("Repeated lable symbol on line %d.\n", instruction_address);
                    return 1;
                }

                // the hashtable uses symbol as key, so dont free symbol.
                break;
            }
            default:
                puts("Invalid instruction.");
                return 1;
        }
    }

    fclose(stdin);

    freopen(INPUT_FILE_NAME, "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);

    // 2. generate binary code
    while (advance(instruction)) {
        INSTRUCTION_TYPE type = get_instruction_type(instruction);

        switch (type) {
            case A_INSTRUCTION: {
                char *symbol = get_symbol(instruction);
                ADDRESS result_address;

                if (is_valid_symbol(symbol)) {
                    bool succeed = insert_symbol(symbol, variable_address);

                    if (succeed) { // add new variable, which is also the result address
                        result_address = variable_address++;

                        // the hashtable uses symbol as key, so dont free symbol.
                    } else { // otherwise, find it in hashtable
                        result_address = find_symbol(symbol);

                        free(symbol);
                    }
                } else {
                    if (is_num(symbol)) {
                        result_address = get_num(symbol);
                    } else {
                        printf("Invalid symbol on line %d.\n", instruction_address);
                        return 1;
                    }
                }

                print_binary_address(result_address);

                break;
            }
            case C_INSTRUCTION: {
                char *dest = get_dest(instruction);
                char *comp = get_comp(instruction);
                char *jump = get_jump(instruction);

                const char *binary_dest = gen_dest(dest);
                const char *binary_comp = gen_comp(comp);
                const char *binary_jump = gen_jump(jump);

                if (binary_dest == NULL) {
                    printf("Invalid dest on line %d.\n", instruction_address);
                    return 1;
                }

                if (binary_comp == NULL) {
                    printf("Invalid comp on line %d.\n", instruction_address);
                    return 1;
                }

                if (binary_jump == NULL) {
                    printf("Invalid dest on line %d.\n", instruction_address);
                    return 1;
                }

                printf("111%s%s%s\n", binary_comp, binary_dest, binary_jump);

                free(dest), free(comp), free(jump);
                break;
            }
            case L_INSTRUCTION: {
                // everything done in step1, so do nothing
                break;
            }
            default:
                puts("Invalid instruction.");
                return 1;
        }
    }

    fclose(stdin);
    fclose(stdout);

    return 0;
}
