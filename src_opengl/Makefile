CC=g++
CXXFLAGS = -std=c++2a -Wall -pedantic -Wextra
LDFLAGS = -lm -lXext -lX11 -lm -lglut -lXi -lXmu -lGL -lGLU -lglut

BIN = opengl
OBJS = main.o rng.o opengl.o

BIN2 = vulkan
OBJS2 = main.o rng.o vulkan.o

all: $(BIN)

$(BIN): $(OBJS)

$(BIN2): $(OBJS2)

.PHONY: test clean

clean:
	$(RM) $(BIN) $(BIN2) $(OBJS) $(OBJS2)

