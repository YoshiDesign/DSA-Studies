#include <stdio.h>
#include <stdint.h>

#define BITS 17
#define SIZE ((size_t)1 << BITS)  // 131072
// #define hashsize(n) ((size_t) 1 << n)
// #define hashmask(n) (hashsize(n) - 1)

size_t oaat(void* byte, size_t len) {

    unsigned char* data = byte;

    size_t hash, i;

    for (hash = 0, i = 0; i < len; i++) {
        hash += data[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    // "Avalanche" - The Surfaris
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;

}

int main() {

    int counts[SIZE] = {0};

    for (size_t i = 0; i < SIZE; i++) {

        size_t code = oaat(&i, sizeof(size_t));
        code = code & (SIZE - 1);
        counts[code]++;
    }

    return 0;

}