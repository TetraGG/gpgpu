CC=gcc
CFLAGS = -std=c99 -Wall -pedantic -Wextra -g
LDFLAGS = -lm -lXext -lX11 -lm -lglut -lXi -lXmu -lGL -lGLU -lglut

BIN = main
OBJS = main.o \
       emitter.o \
       helpers.o \
       view.o \
       wind.o \
	   abstract_opengl.o

all: $(BIN)

$(BIN): $(OBJS)

.PHONY: test clean

clean:
	$(RM) $(BIN) $(OBJS)
