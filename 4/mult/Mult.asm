// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

//// Replace this comment with your code.

@R2 // clear R2
M=0
(LOOP)
@R0
D=M
@END
D;JEQ // end if R0 = 0
@R0
M=M-1 // R0--
@R1
D=M
@R2
M=M+D // R2 += R1
@LOOP
0;JMP // loop

(END) // end loop
@END
0;JMP