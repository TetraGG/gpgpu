CXX=g++

CXXFLAGS = -std=c++17 -Wall -pedantic -Wextra
LDFLAGS = `pkg-config --static --libs glfw3` -lvulkan

BIN = particle

SRC = main.cpp \
      vulcan_application.cpp \
      validation_layers.cpp \
      devices.cpp \
      queue_family_indices.cpp \
      swap_chain.cpp \
      graphics_pipeline.cpp \

OBJS = $(SRC:.cpp=.o)

SHADERS = shaders/vert.spv shaders/frag.spv

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
