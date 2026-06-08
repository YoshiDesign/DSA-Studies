CXX := clang++
CXXFLAGS := -std=c++20 -g -pedantic -Wall -Wextra
CPPFLAGS := -Isrc

BUILD_DIR := build

SRCS := $(shell find src -name '*.cpp')
OBJS := $(SRCS:src/%.cpp=$(BUILD_DIR)/%.o)
TARGET := deque_test

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ 

$(BUILD_DIR)/%.o : src/%.cpp
	mkdir -p $(dir $@) # This extracts the directory portion of (e.g.) build/Memory/Arena.o so literally "build/Memory/"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean :
	rm -rf $(BUILD_DIR) $(TARGET)

