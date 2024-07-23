
EXEC ?= main
RM ?= rm -f
CC ?= gcc
PKGCONFIG ?= pkg-config

override CFLAGS += $(shell $(PKGCONFIG) gtk4 --cflags)
override LDFLAGS += $(shell $(PKGCONFIG) gtk4 --libs)

OBJECTS = main.o

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
