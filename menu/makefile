# Directories
S_DIR=source
HEADERS = components/button.hpp
# Files
S_FILES=main.cpp components/Button.cpp components/Button.hpp

# Output
EXEC=$(B_DIR)/sdl_app

# Build settings
CC=g++
# SDL options
CC_SDL=-lSDL `sdl-config --cflags --libs`
LIBFLAGS= -lSDL -lSDL_ttf


all:Build

Build:
	$(CC) $(S_FILES) -o $(EXEC) $(LIBFLAGS)

build_run:Build
	$(EXEC)

clean:
	rm -rf $(B_DIR)/*