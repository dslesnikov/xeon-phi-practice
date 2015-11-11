CC = icc
CC_FLAGS = -L/opt/intel/mkl/lib/mic -lmkl_intel_ilp64 -lmkl_core -lmkl_intel_thread -lpthread -qopenmp -DMKL_ILP64 -I/opt/intel/mkl/include/ -lm -mmic -O2 -std=c99
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
