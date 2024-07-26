
TARGET=main.exe

CC=wcl
CFLAGS=-omaxnet -bw -l=windows -bt=windows -zw

SOURCES=main.c

$(TARGET): .SYMBOLIC
	$(CC) $(CFLAGS) $(SOURCES)
