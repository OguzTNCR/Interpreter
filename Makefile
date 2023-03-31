
all: advcalc
	gcc-12 -o advcalc main.c interpreter.c parser.c SymbolTable.c