CC := gcc
# Sanitizers generally need to be enabled during both compilation and linking
CFLAGS := -Wall -Wshadow -Wpedantic -g3 -O0 -fsanitize=address,undefined,bounds
LDFLAGS := -fsanitize=address,undefined,bounds
OBJ := snowflakes_1.o
TARGET := snow

# "Explicit Recipe"
$(TARGET) : $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@
# NOTE: Make's implicit rules will still include $(CFLAGS) and even $(CXXFLAGS) in the rules that compile each .c file
# During compilation, GCC inserts sanitizer instrumentation into the object file.
# During linking, GCC links the sanitizer runtime libraries
clean :
	rm -f $(TARGET) $(OBJ)
