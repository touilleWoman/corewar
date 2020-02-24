
# Corewar

Assembleur:
- C'est un programme qui analyse un code source en langage Assembleur et le transforme en code binaire

Machine Virtuel:
- Prend un champion, precedemment traduit de l'assembleur au binaire.
- charge ce code binaire et en fonction des instructions qui y sont écrits effectue des opérations.


**Usage**
```
make
```
```
./asm champs/*.s
```
```
./corewar file1.cor file2.cor ..
	(flags optional)
    -dump <nb> : dump memory in hexadecimal after <nb> cycles then quit
    -n : set id of next player. Player_id must > 0 and <= player_nb
    -v : show operations and cycle
    -p : show movement of cursor
```

visualiseur :

install pygame in virtual env
```
python3 -m venv venv && source venv/bin/activate && pip install pygame
```

```
python3 visu_python/run_visu.py file1.cor file2.cor .. (flags the same as corewar)
```

