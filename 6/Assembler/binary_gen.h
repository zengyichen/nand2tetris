#ifndef BINARY_GEN_H
#define BINARY_GEN_H

typedef struct Table {
	const char *key;
	const char *val;
} Table;

const char* gen_dest(const char *dest);
const char* gen_comp(const char *comp);
const char* gen_jump(const char *jump);
static const char* search_table(Table table[], const char *str);

#endif