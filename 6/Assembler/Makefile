Assembler: main.o asm_parser.o binary_gen.o symbol_table.o
		gcc -o Assembler main.o asm_parser.o binary_gen.o symbol_table.o

main.o: main.c asm_parser.h binary_gen.h symbol_table.h
		gcc -c main.c

asm_parser.o: asm_parser.c asm_parser.h
		gcc -c asm_parser.c

binary_gen.o: binary_gen.c binary_gen.h
		gcc -c binary_gen.c

symbol_table.o: symbol_table.c symbol_table.h
		gcc -c symbol_table.c

clean:
		rm -rf Assembler main.o asm_parser.o binary_gen.o symbol_table.o Prog.hack