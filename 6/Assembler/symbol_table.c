#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "symbol_table.h"

bool is_valid_symbol(const char *symbol) {
    // empty symbol is invalid
    if (*symbol == '\0') return false;

    // symbol cant begin with number
    if (*symbol >= '0' && *symbol <= '9') return false;

    while (*symbol != '\0') {
        if ((*symbol < '0' || *symbol > '9')
         && (*symbol < 'a' || *symbol > 'z')
         && (*symbol < 'A' || *symbol > 'Z')
         && *symbol != '_'
         && *symbol != '.'
         && *symbol != '$'
         && *symbol != ':') {
            return false;
        }
        symbol++;
    }
    
    return true;
}

bool is_num(const char *symbol) {
    while (*symbol != '\0') {
        if (*symbol < '0' || *symbol > '9') {
            return false;
        }
        symbol++;
    }
    return true;
}

ADDRESS get_num(const char *symbol) {
    ADDRESS res = 0;

    while (*symbol != '\0') {
        res = res * 10 + *symbol - '0';
        symbol++;
    }
    return res;
}

void print_binary_address(ADDRESS address) {
    for (int i = ADDRESS_BIT - 1; i >= 0; i--) {
        putchar('0' + (address >> i & 1));
    }
    puts("");
}

static HASH get_hash_value(const char *key) {
    HASH hash = 0;
    while (*key != '\0') {
        hash = (hash * BASE + *key) % MOD;
        key++;
    }
    return hash;
}

// head of linked lists
static Node *link_head[257];

bool insert_symbol(const char *symbol, ADDRESS address) {
    HASH hash_value = get_hash_value(symbol);

    Node *ptr = link_head[hash_value], *tail = NULL;

    while (ptr != NULL) {
        if (strcmp(ptr->key, symbol) == 0) { // already inserted
            return false;
        }
        tail = ptr;
        ptr = ptr->nxt;
    }
    
    Node *new_node = (Node*) malloc(sizeof(Node));

    if (link_head[hash_value] == NULL) {
        link_head[hash_value] = new_node;
    }
    if (tail != NULL) {
        tail->nxt = new_node;
    }
    new_node->key = symbol;
    new_node->val = address;
    new_node->nxt = NULL;

    return true;
}

ADDRESS find_symbol(const char *symbol) {
    HASH hash_value = get_hash_value(symbol);

    Node *ptr = link_head[hash_value];

    while (ptr != NULL) {
        if (strcmp(ptr->key, symbol) == 0) { // find the symbol
            return ptr->val;
        }
        ptr = ptr->nxt;
    }

    return ADDRESS_NULL;
}

struct {
    const char *symbol;
    ADDRESS address;
} SYMBOLS[] = {
    { "SP", 0x0000 },
    { "LCL", 0x0001 },
    { "ARG", 0x0002 },
    { "THIS", 0x0003 },
    { "THAT", 0x0004 },

    { "R0", 0x0000 },
    { "R1", 0x0001 },
    { "R2", 0x0002 },
    { "R3", 0x0003 },
    { "R4", 0x0004 },
    
    { "R5", 0x0005 },
    { "R6", 0x0006 },
    { "R7", 0x0007 },
    { "R8", 0x0008 },
    { "R9", 0x0009 },
    
    { "R10", 0x000a },
    { "R11", 0x000b },
    { "R12", 0x000c },
    { "R13", 0x000d },
    { "R14", 0x000e },
    { "R15", 0x000f },

    { "SCREEN", 0x4000 },
    { "KBD", 0x6000 },
    { NULL, ADDRESS_NULL }
};

void init_symbols() {
    for (int i = 0; SYMBOLS[i].symbol != NULL; i++) {
        insert_symbol(SYMBOLS[i].symbol, SYMBOLS[i].address);
    }
}
