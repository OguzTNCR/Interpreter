
all: advcalc
	gcc -o advcalc main.c interpreter.c parser.c SymbolTable.c