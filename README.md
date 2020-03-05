
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

compile the champions, convert *.s to *.cor
```
./asm champs/*.s
```

execute corewar with champions
```
./corewar file1.cor file2.cor ... (maximum 4 champions)
	(flags are optional)
    -dump <nb> : dump memory in hexadecimal after <nb> cycles then quit
    -n : set id of next player. Player_id must > 0 and <= player_nb 
    				(default player id will be 1 2 3 4, use -n if you want to change their id)
    -v : show operations and cycle
    -p : show movement of cursor
```

test VM in python, compare my VM and the VM of Zaz (given by school)
Using Python hypothesis to take ramdom numbers of champions and execute them in the two vm, dump memory at random cycle, then compare the results. My VM has the same behavior with VM of Zaz, except when ocp code is wrong.
```
python3 -m venv venv
pip install tests/requirements
pytest tests
```


Debugger VM: stop at wanted cycle, and show information of vm.
I compile the my c functions to dylib, then use ctypes to connect Python and C.
```
python3 debug_vm/debug_vm.py file1.cor file2.cor .. (the flags the same as corewar)
```

