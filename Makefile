CXX=g++

CXXFLAGS = -std=c++17 -Wall -pedantic -Wextra
LDFLAGS = `pkg-config --static --libs glfw3` -lvulkan

BIN = particle

SRC = main.cpp \
      vulcan_application.cpp \
      validation_layers.cpp \

OBJS = $(SRC:.cpp=.o)

SHADERS =

VPATH = src/

all: $(BIN) $(SHADERS)

$(BIN): $(OBJS)
	$(LINK.cc) -o $@ $^  $(LDFLAGS)

%.spv: shader.%
	glslc -o $@ $<

.PHONY: test clean

test: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN) $(OBJS) $(SHADERS)
