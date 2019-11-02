BUILD_DIR = build
OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = test
TEST_BUILD_DIR = $(TEST_DIR)/$(BUILD_DIR)
OUT_DIRS = $(BUILD_DIR) $(OBJ_DIR) $(TEST_BUILD_DIR)

MD = mkdir
CC = gcc
LD = ld
CFLAGS = -c -Wall -Werror -fpic -Iheaders
LDFLAGS = -shared
OBJS = $(OBJ_DIR)/lexer.o $(OBJ_DIR)/parser.o
TARGET = $(BUILD_DIR)/libparce.so
TESTS = $(TEST_BUILD_DIR)/lexer-spec $(TEST_BUILD_DIR)/parser-spec
TESTCFLAGS = -Wall -lparce -L$(BUILD_DIR) -Wl,-rpath=$(BUILD_DIR) -Iheaders

all: $(OUT_DIRS) $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $^

test: $(OUT_DIRS) $(TARGET) $(TESTS)
	for file in $(TEST_BUILD_DIR)/*; do $${file}; done

$(TEST_BUILD_DIR)/%-spec: $(TEST_DIR)/%-spec.c
	$(CC) -o $@ $^ $(TESTCFLAGS)

$(OUT_DIRS):
	$(MD) -p $@

clean:
	rm -rf $(BUILD_DIR)/*
	rm -rf $(OBJ_DIR)/*
	rm -rf $(TEST_BUILD_DIR)/*
