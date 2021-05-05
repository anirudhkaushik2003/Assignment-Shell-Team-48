CC=gcc
LIBS=-lm
TARGET=Subjects/AssignmentShell
all : main.c globals.c processor/*.c utils/*.c commands/*.c
	$(CC) -o $(TARGET) main.c globals.c processor/*.c utils/*.c commands/*.c $(LIBS)

