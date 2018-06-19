CC = gcc
CFLAGS = -ggdb3 -c -std=gnu11 $(shell pkg-config --cflags gtk+-3.0)

OBJS = smlog.o nubix.o nubix-taskbar.o nubix-background.o

TARGET = libnubix.a

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $(TARGET) $(OBJS)
	make clean

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -f $(OBJS)

clean-all:
	rm -f $(TARGET)
