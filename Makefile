SOURCE_FILES = $(shell find src -type f -name '*.c')
HEADER_FILES = $(shell find include -type f -name '*.h')
OUTPUT_DIR = lib
OUTPUT_FILE = $(OUTPUT_DIR)/liblife.so

.PHONY: clean all

all: $(OUTPUT_FILE)

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

$(OUTPUT_FILE): $(OUTPUT_DIR) $(SOURCE_FILES) $(INCLUDE_FILES)
	cc -shared -o $(OUTPUT_FILE) -Iinclude $(SOURCE_FILES)

clean:
	rm -vfR $(OUTPUT_DIR)
