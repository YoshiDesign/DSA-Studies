CC := gcc
CFLAGS := -Wall -Wextra -Wshadow -Wpedantic -std=c11 \
	 -fsanitize=address,undefined,bounds \
	 -fno-omit-frame-pointer \
	 -fno-sanitize-recover=all \
	 -O0 -g3

LDFLAGS := -fsanitize=address,undefined,bounds

# Note: -g includes debug symbols in the compiled executable

OBJ=main.o
TARGET=chapter0

# You can omit the 2nd directive (main.o : main.c) but then make will rely on implicit rules for turning a .c file into a .o file. This is often fine, as long as you define your own CFLAGS

# 1
$(TARGET) : $(OBJ) 
	$(CC) $(LDFLAGS) $(OBJ) -o $(TARGET)
# 2
# main.o : main.c
# 	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f $(TARGET) *.o
