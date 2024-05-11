CC=gcc
CODEDIRS=src
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))
CFLAGS = -Wno-implicit-function-declaration
OBJECTS=$(patsubst %.c,%.o,$(CFILES))
BINARY=bin

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJECTS) $(BINARY)
