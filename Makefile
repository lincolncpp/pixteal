OBJS = $(wildcard src/engine/*.cpp) $(wildcard src/*.cpp)
INCLUDES = $(wildcard include/engine/*.h) $(wildcard include/*.h)
CC = g++
CFLAGS=-Wall -std=c++14
OBJ_NAME = game
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread

all : $(OBJS) $(INCLUDES)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(CFLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
