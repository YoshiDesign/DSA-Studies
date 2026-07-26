#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define BITS 17
#define SIZE ((size_t)1 << BITS)  // 131072
// #define hashsize(n) ((size_t) 1 << n)
// #define hashmask(n) (hashsize(n) - 1)

// Const to tell us that bytes won't be modified.
size_t oaat(const void* bytes, size_t len) {

    // effectively casting bytes to something indexable
    const unsigned char* data = bytes;

    size_t hash;

    for (size_t i = 0; i < len; i++) {
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

int main(void) {


    // Don't use clock() for benchmarking. It is historically intended for checking on
    // how many CPU clock cycles your program is using
    
    // Low-Res clock
    // clock_t start = clock();

    int counts[SIZE] = {0};

    // For High-Res clock
    struct timespec hrStart;
    struct timespec hrEnd;

    // Greeting
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char buffer[64];
    strftime(buffer, 
        sizeof(buffer),
        "%Y-%m-%d %H-%M-%S",
        local
    );
    printf("Good day! [%s]\n", buffer);

    // High-res
    clock_gettime(CLOCK_MONOTONIC, &hrStart);
    for (size_t i = 0; i < SIZE * 3; i++) {

        size_t code = oaat(&i, sizeof(i));
        code = code & (SIZE - 1);
        counts[code]++;
    }
    clock_gettime(CLOCK_MONOTONIC, &hrEnd);

    size_t total = 0;
    size_t empty_buckets = 0;
    int maximum_count = 0;

    for (size_t i = 0; i < SIZE; i++) {

        total += (size_t) counts[i];

        if(counts[i] == 0) {
            empty_buckets++;
        }

        if(counts[i] > maximum_count) {
            maximum_count = counts[i];
        }

    }

    printf("Values Hashed:  %zu\n", total);
    printf("Buckets:        %zu\n", (size_t)SIZE);
    printf("Empty Buckets:  %zu\n", empty_buckets);
    printf("Largest Bucket: %d\n",  maximum_count);

    // clock_t end = clock();
    // double elapsed = ((double)(end - start) * 1000)/ CLOCKS_PER_SEC;

    // Standard formula for dependable hi-res timing
    double elapsed_hr = 
        (hrEnd.tv_sec - hrStart.tv_sec) + // 0 unless the program crosses the 1s boundary at any point.
        (hrEnd.tv_nsec - hrStart.tv_nsec) / 1e9; // Nanoseconds

    long long ns =
        (hrEnd.tv_sec - hrStart.tv_sec) * 1000000000LL +
        (hrEnd.tv_nsec - hrStart.tv_nsec);

    printf("Hashtable completed in %f seconds\n", elapsed_hr);      // standard formulat
    printf("Hashtable completed in %f us\n",  ns / 1000.0);
    printf("Hashtable completed in %f ms\n",  ns / 1000000.0);
    printf("Hashtable completed in %f sec\n", ns / 1000000000.0);   // just for completeness
    // printf("Program completed in %f ms\n", elapsed);

    return 0;

}