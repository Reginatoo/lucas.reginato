# Variáveis de compilação
CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
LIBS = -lm

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

# Nome do executável principal
TARGET = $(BIN_DIR)/ted

# Arquivos fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.c.o, $(SRCS))

# --- Alvos Principais ---

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

$(OBJ_DIR)/%.c.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Target para Testes Unitários ---
# Aqui supomos que você baixou o framework Unity e o colocou em uma pasta 'unity'
test: $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TEST_DIR)/test_hash.c unity/unity.c $(filter-out $(OBJ_DIR)/main.c.o, $(OBJS)) -o $(BIN_DIR)/test_suite $(LIBS)
	./$(BIN_DIR)/test_suite

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) *.hf *.hfc *.hfd

.PHONY: all clean test