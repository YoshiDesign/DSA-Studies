#include <stdio.h>
#include <string.h>
#define SIZE 1000000

// A program to illustrate that hashtables
// aren't always necessary. 

/*
 * Invariant: strlen(s2) == strlen(s1) - 1
 */

// length of common prefix
int prefix_length(char s1[], char s2[]) {
    int i = 1;
    while (s1[i] == s2[i]) i++;

    printf("Longest Common Prefix: %d\n", i - 1);
    return i-1;
}

// Length of common suffix
int suffix_length(char s1[], char s2[], int len) {


    printf("S1: %s\n", &s1[1]); // or use arithmentic:  printf("S1: %s\n", s1 + 1);


    int i = len;
    while(i >= 2 && s1[i] == s2[i - 1]) {
        i--;
    }
    printf("Longest Common Suffix: %d\n", len - i);
    return len - i;
}

int main(void) {

    static char s1[SIZE + 2], s2[SIZE + 2];
    int len, prefix, suffix, total;

    /* Note: due to the use of fgets, the input will contain the newline from pressing "Enter" */
    if(fgets(&s1[1], sizeof(s1) - 1, stdin) == NULL) return 0;
    if(fgets(&s2[1], sizeof(s2) - 1, stdin) == NULL) return 0;
    /* It can be removed like so, replacing newlines with a null terminator: */
    s1[1 + strcspn(&s1[1], "\n")] = '\0';
    s2[1 + strcspn(&s2[1], "\n")] = '\0';

    len = strlen(&s1[1]);
    prefix = prefix_length(s1, s2);
    suffix = suffix_length(s1, s2, len);
    total = (prefix + 1) - (len - suffix) + 1;

    if (total < 0) {
        total = 0;
    }

    printf("%d\n", total);

    for (int i = 0; i < total; i++) {
        printf("%d", i + len-suffix);

        if (i < total - 1)  printf(" ");
        else                printf("\n");

    }
    return 0;
}