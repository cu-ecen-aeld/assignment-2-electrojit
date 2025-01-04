#make file to compile the application using cross compiler tool chain

# Compiler settings
CROSS_COMPILE ?=
CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Wextra

# Sources
SRCS = writer.c

# Objects
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = writer

# Add phony to avoid any makefile issues
.PHONY: all clean

# build all - default build target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(TARGET) $(OBJS)