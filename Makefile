TARGET = bin/renderer
SRC = $(wildcard code/src/*.c)
OBJ = $(patsubst code/src/%.c, obj/%.o, $(SRC))


build: clean $(TARGET)

$(TARGET): $(OBJ)
	gcc -o $@ $? -Wall -std=c99

obj/%.o : code/src/%.c
	gcc -c $< -o $@ -Icode/include


clean:
	rm -f obj/*.o
	rm -f bin/*

run:
	./$(TARGET)