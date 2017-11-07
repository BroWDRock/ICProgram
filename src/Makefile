CC=g++
FLAGS=-fopenmp
SOURCE = translator.cc
PROGRAM_NAME = translator
OBJ = translator.o
ARGS=index.txt

translator: $(OBJ)
	$(CC) $(FLAGS) -o $(PROGRAM_NAME) $(OBJ)

translator.o: $(SOURCE)
	$(CC) -fopenmp -c $(SOURCE)

clean:
	$(RM) $(OBJ)
	$(RM) $(PROGRAM_NAME)
	$(RM) output.txt
	$(RM) rs.txt
	$(RM) resultado.txt

run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME) $(ARGS)