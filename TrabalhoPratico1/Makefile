CXX = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++17

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

TARGET = $(BIN_DIR)/programa

$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CFLAGS) -I $(INC_DIR) -c -o $@ $<

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(BIN_DIR):
	mkdir $(BIN_DIR)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: valgrind
valgrind: $(TARGET)
	valgrind ./$(TARGET)

.PHONY: debug
debug: CFLAGS += -g
debug: clean $(TARGET)
