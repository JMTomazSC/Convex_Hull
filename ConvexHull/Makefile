CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin

GEO_OBJ = $(OBJ)/Geometric_structures.o $(OBJ)/main.o
GEO_INC = $(INC)/Geometric_structures.hpp
STACK_INC = $(INC)/Stack.hpp
ERRORS_INC = $(INC)/errors.hpp
FUNC_INC = $(INC)/functions.hpp
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/fecho

run: $(EXE)
	
$(BIN)/fecho: $(GEO_OBJ)
	$(CC) -pg -o $(BIN)/fecho $(GEO_OBJ) $(LIBS)

$(OBJ)/Geometric_structures.o: $(GEO_INC) $(STACK_INC) $(FUNC_INC) $(SRC)/Geometric_structures.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Geometric_structures.o $(SRC)/Geometric_structures.cpp

$(OBJ)/main.o: $(GEO_INC) $(STACK_INC) $(FUNC_INC) $(ERRORS_INC) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

clean:
		rm -f $(EXE) $(GEO_OBJ) gmon.out
		clear
