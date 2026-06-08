#pragma once
#include <iostream>
#include <cstdint>
#include <cassert>

#include "Memory/Arena.h"

/**
* Things to remember:
* - Pointers into the victim’s stack are forbidden.
* - Pointers into arena/request memory are fine if lifetime is provably longer than the last task()
*/

template <class T>
class WSDeque {
public:
	WSDeque(size_t capacity, Arena* arena) : _capacity(capacity), mask(_capacity - 1) {
		assert((_capacity & mask) == 0 && "DeQueue capacity must be a pwr of 2");
		buffer = ArenaAlloc(arena, capacity);
	}
	~WSDeque() {
		DestroyArena(arena);
	}

	bool push_bottom(T item);	// owner
	bool pop_bottom(T* item);	// owner
	bool steal_top(T* item);	// thief

private:
	// Initialization order matters for these 2 since I'm using them immediately in the ctor
	uint64_t _capacity{ };
	uint64_t mask{ 0 };

	alignas(std::hardware_destructive_interference_size) 
		std::atomic<uint64_t> head{ 0 };
	alignas(std::hardware_destructive_interference_size) 
		std::atomic<uint64_t> tail{ 0 };

	T* buffer{ };
};