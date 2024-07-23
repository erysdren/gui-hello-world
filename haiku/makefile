
EXEC ?= main
RM ?= rm -f
CXX ?= g++

override LDFLAGS += -lbe

OBJECTS = main.o

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CXX) -c -o $@ $< $(CXXFLAGS)
