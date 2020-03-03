
# Corewar

> Core War is a 1984 programming game created by D. G. Jones and A. K. Dewdney in which two or more battle programs (called "warriors")
> compete for control of a virtual computer. These battle programs are written in an abstract assembly language called Redcode.


The project is consist of 2 parts:

Assembler
- compile champions and translate them from the language written them in (assembly language) into “Bytecode”.
Bytecode is a machine code, which will be directly interpreted by the virtual machine.

Virtual machine:
- It’s the “arena” where the champions fight against each other. This VM accept maximum 4 champions.

This is a team project of school 42, I am in charge of the Virtual machine.


**Usage**
```
make
```
```
./asm champs/*.s
```
```
./corewar file1.cor file2.cor ..
	(flags are optional)
    -dump <nb> : dump memory in hexadecimal after <nb> cycles then quit
    -n : set id of next player. Player_id must > 0 and <= player_nb
    -v : show operations and cycle
    -p : show movement of cursor
```

debug vm :
```
python3 debug_vm/debug_vm.py file1.cor file2.cor .. (flags the same as corewar)
```

