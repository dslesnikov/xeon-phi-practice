CC = icc
CC_FLAGS = -openmp -mkl -O3 -std=c99
SRC = rand_walk.c
OBJ = rand_walk.o
EXEC = rand_walk.x

all: $(SRC) $(EXEC) clean

$(EXEC): $(OBJ)
	$(CC) $< $(CC_FLAGS) -o $@

$(OBJ): $(SRC)
	$(CC) $< $(CC_FLAGS) -c -o $@

clean:
	rm $(OBJ)
