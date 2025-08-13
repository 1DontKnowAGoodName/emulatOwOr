# emulatOwOr

This is an emulator for a schoolproject. It's a three year long project, where every year i have to spend 100 hours or more on it and it's supposed to teach me how to do these kinds of things. I started with this thing almost exactly a year ago, and have worked on it for the whole year, and certainly spent more than 100 hours on it. i started off ambitious and naive so it's not good. You can see in instructionSet that i didn't know much, and i just kept on going with the instruction set i designed six months or so ago.

In the assembler repo you can see the instruction set in excel format (even though for this project i have now switched to debian linux) and the ALU of this thing made in logisim. It's bad, not well thought out, very limiting and just, not that good. Condsidering that, just copy this code and pass it off as your own, i don't care.

requirements i set for this project, though they changed somewhat during development:
 - an assembler, that could convert the code to binary

 - at least a few drawings or sketches of how it had to look

 - an emulator with which you can code actual things and see them work in real time. it also must have a graphical interface

 - documentation so that other people can work with this emulator

 - i need to program a working version of bresenhams line algorithm, then, if it works, i am completely done.

## Documentation:

the program counter starts at 0 but skips that, so it's easier to jump to a specific line, trust me.

the little thing openening up is mapping the Vram in bits, 64x32, this is the only IO of this thing.

to refer to a register put `r` and the number of the reg. 0 is zero read, it's always zero. it's from 1-7, 8 is out of range.

use as many spaces as you want, that doesn't affectt the code, just keep the insctruction at one line.

comment with `;`, everything after gets ignored.


to define a value, do `#define`, the name of the value and the value. you can't declare something twice. it's read before the code is executed, so you can use that defined before it's actually defined. it only fits in places where immediates would fit, so you can do `LDI r1 [some value]_`. the _ is required and signifies that that it ends there.


for a label, you write `.[label]:` and to call it you use `.label_`. the value the label contains is the line where it's at, so it dynamically points to a specific instruction.


look in the excel sheet in the assembler repo, that contains all the names of the instructions and what they do, but it's not updated to what it is now.


there are **NO** error messsages, first read your own code before you blame me, but you can blame me.


there were plans to make things to help debugging, but i'm too lazy, just use a builtin debugger.


### the documentation of the instructions. it's an instruction, then `r` for register and i for immediate.

`NOP` - does nothing, takes no parameters

`LDI r i` - puts the immediate in the register

`STO r i` - puts register in the location in RAM

`GET r i` - puts the value at immediate from RAM in the register

`MOV r r` - moves the first register to the second

`PLT r r r` plot pixel at x (second reg), y (third reg). if first reg < 1 then black, if not, white.

`JIG r r r` - if second is bigger than third, jumps to the value of the first

`JIS r r r` - if second is smaller than third,jumps to the value of the first

`JIT r r r` - if second and third are equal, it jumps to the value of the first

`ECT i` - set counter to immediate

`GCT r` - puts value of counter in the register

`GTV r i` - puts the regist in location in VRAM

`PTV r i` - puts the value at immediate from VRAM in the register

`HLT` - basically halts the program, until you type enter in terminal

`ADD r r r` - adds the second and third into the first

`SUB r r r` - subtracts the third from the second into the first

`AND r r r` - ANDs two and three into one

`ORE r r r` - ORs two and three into one

`XOR r r r` - XOR two and three into one

`NOT r r` - NOTs the second into the first.

`RBS r r r` - right bit shift the second as many times as the third and value in first

`LBS r r r` - left bit shift the second as many times as the third and value in first

`CMP r r r` - if two and three are equal, then 1 is placed in the first

`MLT r r r` - multiply two and three and put into the first register

`ODD r r` - if the second register is ODD 1 is put in the first reg.

`INC r r` - increment second register and put into first

`DCR r r` - decrement second register and put into first


## Building:

tbh idk dude. this is the command i used to compile the code that isn't raylib:

`g++ -g *.cpp -o emulator`

the -g flag is for debugging, the -o flag is for putting the output in the emulator file.
that is on linux though. this thing is made for linux and uses some code that only works on linux, windows would not run this correctly probably.

for compiling the code so raylib works i used:

`g++ -g *.cpp -lraylib -lGl -lm -lpthread -ldl -lrt -lX11`

so to compile the whole thing, it'd probably be smart to use something like:

`g++ *.cpp -lraylib -lGl -lm -lpthread -ldl -lrt -lX11 -o emulator`

without the debug flag because that takes up space, and maybe also put an optimizations flag there because it's kinda bad code.

it also uses raylib so you probably need raylib installed to run it or something, but i'm not completely sure. at least you need raylib to compile it.

## Sources:

watching a lot of youtube, the ORE discord server, more youtube, learncpp and cppreference for the language, did i mention youtube?

## Is this good?:

no it isn't there are so many things i could've done better, but i knew that was going to happen when i started.

## things i regret doing:

* having this awful instruction set, i didn't know enough to know which instructions were relevant and which not, and i just ignored flags because i didn't understand them (yes that's a problem i know this thing is very bad)
* i stored defines and labels in vectors, which are really not the good data structure for doing that, it contrubited a lot to the size of parser.
* putting everything in different files. the project just became more complex, next time i won't do it like that, just a lot of forward declerations above main.
* a 5 bit opcode, it gave me so many possibilties i didn't know what to do with and still 10 are unused. i just needed three bits for it idk.

## PS

don't mind all the comments or the name, i'm just kinda gay and i'm was also kinda tired :3333
