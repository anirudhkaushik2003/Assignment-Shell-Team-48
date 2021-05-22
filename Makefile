CC=gcc
LIBS=-lm
TARGET=AssignmentShell
all : source/main.c source/globals.c source/processor/*.c source/utils/*.c source/commands/*.c
	$(CC) -o $(TARGET) source/main.c source/globals.c source/processor/*.c source/utils/*.c source/commands/*.c $(LIBS)