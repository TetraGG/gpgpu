CC=gcc
CFLAGS = -std=c99 -Wall -pedantic -Wextra -g
LDFLAGS = -lm

BIN = main
OBJS = main.o \
       emitter.o \
       helpers.o \
       view.o \
       wind.o

all: $(BIN)

$(BIN): $(OBJS)

.PHONY: test clean

clean:
	$(RM) $(BIN) $(OBJS)
