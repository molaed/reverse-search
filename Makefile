MAKEFILE_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
REVERSE_SEARCH := $(shell find $(MAKEFILE_DIR) \( -name '*.c' -o -name '*.h' \))
BINARY := $(MAKEFILE_DIR)/build/your_binary_name

all: generate build

rebuild: update generate build

debug: update debug_mode generate build

$(MAKEFILE_DIR)/build/CMakeCache.txt: $(REVERSE_SEARCH)

	cmake -S $(MAKEFILE_DIR) -B $(MAKEFILE_DIR)/build/ $(DEBUG_FLAG)

$(BINARY): $(REVERSE_SEARCH)
	echo "building binary"
	cmake --build $(MAKEFILE_DIR)/build/

update:
	touch $(MAKEFILE_DIR)/CMakeLists.txt

generate: $(MAKEFILE_DIR)/build/CMakeCache.txt

debug_mode: 
	$(MAKE) generate DEBUG_FLAG:='-DDEBUG:int=1'

build: $(BINARY)

clean:
	rm -rf $(MAKEFILE_DIR)/build