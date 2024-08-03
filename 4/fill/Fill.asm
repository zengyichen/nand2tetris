// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.


// set address 'color' to selected color

(SetBlack)
@1
D=-A // all black is 1111 1111 1111 1111
@color
M=D
@SetColorDone
0;JMP

(SetWhite)
@0
D=A
@color
M=D
@SetColorDone
0;JMP

(Loop)

@SCREEN
D=A
@addr
M=D // initial address
@KBD
D=M
@SetBlack
D;JNE // set color to black if any key is pressed
@SetWhite
D;JEQ // set to white when no key is pressed
(SetColorDone)

(PaintBlack)
@color
D=M // read color to D
@addr
A=M // jump to current screen address
M=D // draw color to screen
@addr
MD=M+1 // jump to next memory
@KBD
D=D-A
@Loop
D;JGE // if current address >= keyboard address, break
@PaintBlack
0;JMP // else, continue painting