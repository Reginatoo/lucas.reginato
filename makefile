CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
LIBS = -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

TARGET = $(BIN_DIR)/ted

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.c.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

$(OBJ_DIR)/%.c.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(OBJS)
	@mkdir -p $(BIN_DIR)
	@echo "Compilando testes..."
	$(CC) $(CFLAGS) $(TEST_DIR)/test_hash.c unity/unity.c $(filter-out $(OBJ_DIR)/main.c.o, $(OBJS)) -o $(BIN_DIR)/test_hash $(LIBS)
	$(CC) $(CFLAGS) $(TEST_DIR)/test_quadra.c unity/unity.c $(filter-out $(OBJ_DIR)/main.c.o, $(OBJS)) -o $(BIN_DIR)/test_quadra $(LIBS)
	$(CC) $(CFLAGS) $(TEST_DIR)/test_pessoa.c unity/unity.c $(filter-out $(OBJ_DIR)/main.c.o, $(OBJS)) -o $(BIN_DIR)/test_pessoa $(LIBS)
	@echo "\n--- Executando testes Hash ---"
	./$(BIN_DIR)/test_hash
	@echo "\n--- Executando testes Quadra ---"
	./$(BIN_DIR)/test_quadra
	@echo "\n--- Executando testes Pessoa ---"
	./$(BIN_DIR)/test_pessoa

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) *.hf *.hfc *.hfd

.PHONY: all clean test