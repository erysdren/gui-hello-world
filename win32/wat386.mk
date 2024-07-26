
TARGET=main.exe

CC=wcl386
BIND=wbind
CFLAGS=-omaxnet -bw -l=win386 -bt=windows -zw

SOURCES=main.c

$(TARGET): .SYMBOLIC
	$(CC) $(CFLAGS) $(SOURCES)
	$(BIND) $(TARGET) -n
