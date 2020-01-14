CC=g++
CXXFLAGS = -std=c++2a -Wall -pedantic -Wextra
LDFLAGS = `pkg-config --static --libs glfw3` -lvulkan
VPATH = src/:src_particles/

SRC = src/main.cpp \
      vulkan_application.cpp \
      validation_layers.cpp \
      devices.cpp \
      queue_family_indices.cpp \
      swap_chain.cpp \
      graphics_pipeline.cpp \
      command_buffers.cpp \
      window.cpp \
      instance.cpp \

BIN = particle
OBJS = $(SRC:.cpp=.o)
SHADERS = shaders/vert.spv shaders/frag.spv

BIN_OPENGL = opengl
BIN_VULKAN = vulkan
OBJS_PARTICLES = src_particles/main.o rng.o


all: $(BIN) $(SHADERS) particles


$(BIN): $(OBJS)
	$(LINK.cc) -o $@ $^  $(LDFLAGS)


particles: LDFLAGS = -lm -lGL -lGLU -lglut
particles: $(BIN_OPENGL) $(BIN_VULKAN)

$(BIN_OPENGL): OBJS_PARTICLES += opengl.o
$(BIN_OPENGL): $(OBJS_PARTICLES)

$(BIN_VULKAN): OBJS_PARTICLES += vulkan.o
$(BIN_VULKAN): $(OBJS_PARTICLES)


%.spv: shader.%
	glslc -o $@ $<

test: $(BIN)
	./$(BIN)

.PHONY: test clean

clean:
	$(RM) $(BIN) $(OBJS) $(SHADERS) $(BIN_OPENGL) $(BIN_VULKAN) $(OBJS_OPENGL) $(OBJS_VULKAN)
