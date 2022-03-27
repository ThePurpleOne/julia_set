CC       := gcc
CFLAGS := -Wall -Wextra -g -fsanitize=address -fsanitize=leak

BIN     	 := bin
SRC     	 := src
INCLUDE 	 := include
LIBRARIES    := -lm -lSDL2 -lGLEW -lGLU -lGL -lglut
EXECUTABLE   := main

SOURCES += $(SRC)/$(EXECUTABLE).c
SOURCES += $(SRC)/sdl_abstract.c
SOURCES += $(SRC)/j_shaders.c

.PHONY: all run test clean prebuild

all: prebuild $(BIN)/$(EXECUTABLE) 

run: clean all
	@echo "########## EXECUTE FIRST PROGRAM ##########"
	./$(BIN)/$(EXECUTABLE)

prebuild:
	@mkdir -p $(BIN)

clean:
	@echo "########## CLEANING ##########"
	-rm $(BIN)/*

# COMPILE FIRST EXECUTABLE
$(BIN)/$(EXECUTABLE): $(SOURCES)
	@echo "########## COMPILING FIRST EXECUTABLE ##########"
	$(CC) $(CFLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES)
