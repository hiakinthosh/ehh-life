# Directories
S_DIR=source
B_DIR=build

# Files
S_FILES=$(S_DIR)/main.cpp

# Output
EXEC=$(B_DIR)/sup

# Build settings
CC=g++
# SDL options
CC_SDL=-lSDL `sdl-config --cflags --libs`


all:Build

Build:
	$(CC) $(S_FILES) -o $(EXEC) $(CC_SDL)

build_run:Build
	$(EXEC)

clean:
	rm -rf $(B_DIR)/*
