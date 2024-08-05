#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdbool.h>

// ===== address =====

typedef unsigned short ADDRESS;
#define ADDRESS_BIT 16
#define ADDRESS_NULL ((ADDRESS)(-1))

typedef struct _Node {
    const char *key;
    ADDRESS val;
    struct _Node *nxt;
} Node;

// check if the symbol is valid symbol
bool is_valid_symbol(const char *symbol);

// check if the symbol is number
bool is_num(const char *symbol);

// get number from symbol
ADDRESS get_num(const char *symbol);

// print a line of 16-bit address
void print_binary_address(ADDRESS address);

// ===== hash =====

typedef unsigned int HASH;

// polynominal hash. BASE and MOD is prime number
#define BASE 10007u
#define MOD 257u

static HASH get_hash_value(const char *key);

// insert to hash table. return whether succeed
bool insert_symbol(const char *symbol, ADDRESS address);

// find from hash table. return -1 if failed
ADDRESS find_symbol(const char *symbol);

// insert initial symbols
void init_symbols();

#endif