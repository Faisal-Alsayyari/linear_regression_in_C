# name of final executable
TARGET = linear_regression

# compiler
CC = gcc

# source files
SRCS = linear_regression.c

# flags
CFLAGS = -Wall -g

# default rule
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# clean rule
clean:
	rm -f $(TARGET)

	
