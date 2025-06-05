CC := clang
CC_FLAGS := -D_POSIX_C_SOURCE=200809L -Wall -Werror -Wno-switch -O3 -g -std=gnu89 -MMD -MP -fsanitize=address -DDEBUG

LD := clang
LD_FLAGS := -fsanitize=address

BIN_DIR := bin
OBJ_DIR := obj
SRC_DIR := src

BIN_FILE := $(BIN_DIR)/tariffwar
SRC_FILE := $(shell find $(SRC_DIR) -name '*.c')
OBJ_FILE := $(patsubst %.c, $(OBJ_DIR)/%.o, $(patsubst ../%,%,$(SRC_FILE)))
CC_FLAGS := $(CC_FLAGS) -I$(SRC_DIR) -I$(COM_DIR)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	CC_FLAGS := $(CC_FLAGS) -DLINUX
endif
ifeq ($(UNAME_S), Darwin)
	CC_FLAGS := $(CC_FLAGS) -DAPPLE
endif
UNAME_P := $(shell uname -p)
ifeq ($(UNAME_P),x86_64)
	CC_FLAGS := $(CC_FLAGS) -DAMD64
endif
ifneq ($(filter %86,$(UNAME_P)),)
	CC_FLAGS := $(CC_FLAGS) -DIA32
endif
ifneq ($(filter arm%,$(UNAME_P)),)
	CC_FLAGS := $(CC_FLAGS) -DARM
endif

.PHONY: all mkdirs clean preprocessed ir

all: mkdirs $(BIN_FILE)

mkdirs:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

$(BIN_FILE): $(OBJ_FILE)
	$(LD) -o $(BIN_FILE) $(OBJ_FILE) $(LD_FLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c $< -o $@

-include $(OBJ_FILE:.o=.d)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)

wasm: CC := emcc
wasm: LD := emcc
wasm: CC_FLAGS := -Wall -O2 -std=gnu89 \
	-sALLOW_MEMORY_GROWTH=1 \
	-sEXPORTED_RUNTIME_METHODS='["cwrap","ccall","callMain","FS"]' \
	-sFORCE_FILESYSTEM \
	-s ASYNCIFY \
	-sUSE_ES6_IMPORT_META=0 \
	-sENVIRONMENT=web \
	-sASSERTIONS=1 \
	-sMODULARIZE=1 \
	-sEXPORT_ES6=1 \
	-sEXPORTED_FUNCTIONS='["_main"]' \
	--js-library=node_modules/xterm-pty/emscripten-pty.js \
	-sASYNCIFY
wasm: LD_FLAGS :=
wasm: WASM_OUT := $(BIN_DIR)/tariffwar.js
wasm: mkdirs
	$(LD) $(SRC_FILE) $(CC_FLAGS) -o $(WASM_OUT)
