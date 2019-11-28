
# variable substitution operator 
TARGET=Main

# all .cpp files in this directory are my sources

SOURCES=$(wildcard *.c)

OBJS=$(SOURCES:.c=.o)

INC_FLAGS=-I../include
CC=gcc


#CFLAGS=-pedantic -Wall -Werror -Wconversion -ansi -g $(INC_FLAGS)
#CFLAGS=-pedantic -Wall -Wconversion -ansi -g $(INC_FLAGS)
CFLAGS=-std=gnu90 -Wall -pedantic -Wconversion -Wconversion -ansi -g $(INC_FLAGS)-D_DEBUG=m
#CFLAGS=-std=gnu90 -g $(INC_FLAGS)

CXXFLAGS=$(CFLAGS)
LDFLAGS=-g
.PHONY: clean run gdb

$(TARGET): $(OBJS)
include .depends

# create a hidden file named .depends using a redirection with all include


.depends:
	$(CC) -MM -I$(INC_DIR) $(SOURCES) > .depends

clean:
	rm -f $(OBJS) $(TARGET) .depends

run: $(TARGET)
	#./$(TARGET)
	valgrind --leak-check=full ./$(TARGET)




# Do not forget to add '-g' to CFLAGS
gdb: $(TARGET)
	gdb -q ./$(TARGET)




