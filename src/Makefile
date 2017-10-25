CC=g++
FLAGS=-O3
SOURCE = translator.cc
PROGRAM_NAME = translator
OBJ = translator.o
ARGS=index.txt

translator: $(OBJ)
	$(CC) $(FLAGS) -o $(PROGRAM_NAME) $(OBJ)

translator.o: $(SOURCE)
	$(CC) -O3 -c $(SOURCE)

clean:
	$(RM) $(OBJ)
	$(RM) $(PROGRAM_NAME)

run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME) $(ARGS)
