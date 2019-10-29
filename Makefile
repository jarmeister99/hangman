TARGET   = a.out
CC       = gcc
CCFLAGS  = -ggdb -g
LDFLAGS  = 
SOURCES  = $(wildcard *.c)
INCLUDES = $(wildcard *.h) 
OBJECTS  = $(SOURCES:.c=.o)

all:$(TARGET)

$(TARGET):$(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) 
#(OBJECTS):$(SOURCES) $(INCLUDES)
	$(CC) -c $(CCFLAGS) $(SOURCES)

clean:
	rm -f $(TARGET) $(OBJECTS)
