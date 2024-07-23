
EXEC ?= main
RM ?= rm -f
CC ?= x86_64-w64-mingw32-gcc

OBJECTS = main.o

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
