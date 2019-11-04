BUILD_DIR = build
OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = test
TEST_BUILD_DIR = $(TEST_DIR)/$(BUILD_DIR)
TEST_SRC_DIR = $(TEST_DIR)/$(SRC_DIR)
OUT_DIRS = $(BUILD_DIR) $(OBJ_DIR) $(TEST_BUILD_DIR)

MD = mkdir
CC = gcc
LD = ld
CFLAGS = -c -Wall -Werror -fpic -Iheaders
LDFLAGS = -shared
OBJS = $(OBJ_DIR)/lexer.o $(OBJ_DIR)/parser.o
TARGET = $(BUILD_DIR)/libparce.so
TESTS = $(TEST_BUILD_DIR)/lexer-spec $(TEST_BUILD_DIR)/parser-spec
TEST_OBJS = $(TEST_OBJ_DIR)/lexer-spec.o $(TEST_OBJ_DIR)/expect.o
TESTCFLAGS = -Wall -Werror -lparce -L$(BUILD_DIR) -Wl,-rpath=$(BUILD_DIR) -Iheaders -I$(TEST_DIR)/headers

all: $(OUT_DIRS) $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $^

test: $(OUT_DIRS) $(TARGET) $(TESTS)
	for file in $(TEST_BUILD_DIR)/*; do $${file}; done

$(TEST_BUILD_DIR)/%-spec: $(TEST_SRC_DIR)/%-spec.c
	$(CC) -o $@ $^ $(TEST_SRC_DIR)/expect.c $(TESTCFLAGS)

$(OUT_DIRS):
	$(MD) -p $@

clean:
	rm -rf $(OUT_DIRS)
