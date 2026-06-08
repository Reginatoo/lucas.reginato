CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
LIBS = -lm

SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

TARGET = ted

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

ted: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

all: ted

test: $(OBJS)
	@mkdir -p $(BIN_DIR)
	@echo "Compilando testes..."
	$(CC) $(CFLAGS) $(TEST_DIR)/test_hash.c unity/unity.c $(filter-out $(OBJ_DIR)/main.c.o, $(OBJS)) -o $(BIN_DIR)/test_hash $(LIBS)
	$(CC) $(CFLAGS) $(TEST_DIR)/test_quadra.c unity/unity.c $(filter-out $(OBJ_DIR)/main.c.o, $(OBJS)) -o $(BIN_DIR)/test_quadra $(LIBS)
	$(CC) $(CFLAGS) $(TEST_DIR)/test_pessoa.c unity/unity.c $(filter-out $(OBJ_DIR)/main.c.o, $(OBJS)) -o $(BIN_DIR)/test_quadra $(LIBS)
	./$(BIN_DIR)/test_hash
	./$(BIN_DIR)/test_quadra
	./$(BIN_DIR)/test_pessoa

clean:
	rm -rf *.o $(TARGET) $(OBJ_DIR) $(BIN_DIR) *.hf *.hfc *.hfd

.PHONY: all clean test ted *.hf *.hfc *.hfd

.PHONY: all clean test
