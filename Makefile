# Source directory
S_DIR=source

# Files to compile
S_FILES=$(S_DIR)/main.cpp $(S_DIR)/s.cpp

# Output
EXEC=out

# Build settings
CC=g++

# SDL options
CC_SDL=-lSDL2 `sdl-config --cflags --libs`


all:Build

Build:
	$(CC) $(S_FILES) -o $(EXEC) $(CC_SDL)

build_run:Build
	$(EXEC)

clean:
	rm -rf $(B_DIR)/*
