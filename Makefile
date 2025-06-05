CC = gcc
CFLAGS = -Wall -std=c99 -O2
LDFLAGS = -lSDL2 -lSDL2_image -lopengl32 -lglu32 -lm -lobj

SRC_DIR = src
INC_DIR = include
OBJ_DIR = build_A
LIB_DIR = lib
BIN = main

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

INCLUDES = -I$(INC_DIR) -I$(INC_DIR)/obj
LIBS = -L$(LIB_DIR)

all: $(OBJ_DIR) $(LIB_DIR) $(BIN)

# Könyvtárak létrehozása, ha nem léteznek
$(OBJ_DIR):
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

$(LIB_DIR):
	if not exist $(LIB_DIR) mkdir $(LIB_DIR)

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LIBS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	if exist $(BIN).exe del $(BIN).exe
	if exist $(BIN) del $(BIN)

.PHONY: all clean
