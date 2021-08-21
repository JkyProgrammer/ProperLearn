CC_FILES := $(wildcard src/*.cc)

CC       = g++
CC_ARGS  = -std=c++17

ifeq ($(OS),Windows_NT)
	PL = ProperLearn
	raylib_flags = -L deps/WIN/ -lraylib -lopengl32 -lgdi32 -lwinmm -Wno-enum-compare
	OUTPUT = ProperLearn.exe
	RM = del
else
	PL = ./ProperLearn
	raylib_flags = -L deps/MAC/ -lraylib -framework IOKit -framework Cocoa -framework OpenGL -Wno-enum-compare
	OUTPUT = ProperLearn
	RM = rm
endif

build:
	@$(CC) $(CC_ARGS) $(CC_FILES) $(raylib_flags) -o $(OUTPUT)
	@echo Done.

run: $(build)
	@$(PL)

clean:
	@$(RM) ProperLearn.exe
	@$(RM) ProperLearn
	
	
