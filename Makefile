
all: main.c interpreter.c parser.c SymbolTable.c
	gcc -o advcalc main.c interpreter.c parser.c SymbolTable.c