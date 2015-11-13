CC = icc
#CC_FLAGS = -DMLK_ILP64 -L/opt/intel/mkl/lib/intel64 -lmkl_intel_ilp64 -lmkl_core -lmkl_intel_thread -lm -lpthread -qopenmp -I/opt/intel/mkl/include/ -offload-attribute-target=mic -offload-option,mic,compiler," -L/opt/intel/mkl/lib/mic -lmkl_intel_ilp64 -lmkl_core -lmkl_intel_thread" -std=c99
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
