#Variables
GCC = gcc
TARGET = advcalc
OBJECTS = main.o parser.o interpreter.o SymbolTable.o

#Rules
all: $(TARGET)

#Link object files
$(TARGET): $(OBJECTS)
	$(GCC) -o $(TARGET) $(OBJECTS)


#Compile C files to object files
%.o: %.c
	$(GCC) -c $< -o $@


#Clean up
clean:
	rm -f $(TARGET) $(OBJECTS)