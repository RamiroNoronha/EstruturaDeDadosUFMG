# Variáveis
CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++11
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include
EXEC = $(BIN_DIR)/programa

# Objetos
OBJS = $(OBJ_DIR)/Fila.o $(OBJ_DIR)/Pilha.o $(OBJ_DIR)/main.o

# Regras de compilação
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Regras especiais
.PHONY: all clean run

all: $(EXEC)

clean:
	rm -rf $(BIN_DIR)/* $(OBJ_DIR)/*

run: $(EXEC)
	./$(EXEC)
