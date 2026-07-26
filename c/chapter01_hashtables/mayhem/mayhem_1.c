#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PW_LEN 10
#define NUM_BITS 20
#define TABLE_SIZE ((size_t)1 << NUM_BITS) // size_t is more idiomatic than using 1UL << NUM_BITS

typedef struct password_node {
    char password[MAX_PW_LEN];
    int total;
    struct password_node *next;
} password_node;

// One at a time hash function
size_t oaat(const void* bytes, size_t len){

    const char* find = bytes;
    size_t hash = 0;

    for (size_t i = 0; i < len; i++) {
        hash += find[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    // Avalanche
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

//
password_node* in_hash_table(password_node* hash_table[], char *find) {

    // Computed bucket index
    size_t code;
    // Pointer to a password
    password_node* node_ptr = NULL;

    // Code for the pw in question
    code = oaat(find, strlen(find));
    code = code & (NUM_BITS - 1);

    // Check it out
    node_ptr = hash_table[code];

    // Compare to all entries in the bucket
    while (node_ptr != NULL) {

        // Found a match, return
        if (strcmp(node_ptr->password, find) == 0) return node_ptr;

        // Check next
        node_ptr = node_ptr->next;
    }

    return NULL;
    
}

void add_to_hash_table(password_node* hash_table[], char* pw) {

    size_t code;
    password_node* node_ptr;
    node_ptr = in_hash_table(hash_table, pw);

    if (!node_ptr) {

        code = oaat(pw, strlen(pw));
        code = code & (NUM_BITS - 1);

        node_ptr = malloc(sizeof(password_node));
        if (node_ptr == NULL) {
            fprintf(stderr, "malloc error\n");
            exit(1);
        }

        strcpy(node_ptr->password, pw);
        node_ptr->total = 0;
        node_ptr->next = hash_table[code];
        hash_table[code] = node_ptr;

    }

    ++node_ptr->total;
}

// `size_substrings` is the number of substrings available for `find`
int already_added(char all_substrings[][MAX_PW_LEN + 1], int size_substrings, const char* find) {
    int i;
    for (i = 0; i < size_substrings; i++) {

        if(strcmp(all_substrings[i], find) == 0) {
            return 1;
        }

    }

    return 0;
}

void free_hash_table(password_node *hash_table[])
{
    for (size_t i = 0; i < TABLE_SIZE; ++i) {
        password_node *current = hash_table[i];

        while (current != NULL) {

            // Track the next node before freeing `current`
            password_node *next = current->next;

            // rip
            free(current);

            // next in line
            current = next;
        }

        hash_table[i] = NULL;
    }
}

int main(void) {

    // unsigned long size = (unsigned long) 1 << NUM_BITS;
    static password_node* hash_table[TABLE_SIZE]; // = {NULL}; // static storage (.bss segment)
                                                  // = {NULL} is not requried here, as .bss is zero-initialized by default.
                                                  // A static array is reasonable when the table has a fixed maximum size.
                                                  // Heap allocation is better when you want runtime sizing, 
                                                  // multiple independent tables, resizing, or explicit ownership

    int num_ops, i, j, op, op_type;
    char password[MAX_PW_LEN + 1];      // tmp password storage
    char substring[MAX_PW_LEN + 1];     // tmp substring storage
    password_node* node;
    int total_substrings = 0;
    char all_substrings[MAX_PW_LEN * MAX_PW_LEN][MAX_PW_LEN + 1];

    printf("Num Ops: ");
    scanf("%d", &num_ops);

    for(op = 0; op < num_ops; op++) {

        scanf("%d%s", &op_type, password);

        if (op_type == 1) {

            total_substrings = 0;
            for(i = 0; i < strlen(password); i++) {
                for(j = 0; j < strlen(password); j++) {

                    strncpy(substring, &password[i], j - i + 1);
                    substring[j - i + 1] = '\0';
                    if (!already_added(all_substrings, total_substrings, substring)) {

                        add_to_hash_table(hash_table, substring);
                        strcpy(all_substrings[total_substrings], substring);
                        total_substrings++;
                    }
                }
            }

        } else {

            node = in_hash_table(hash_table, password);
            if (!node) {
                printf("0\n");
            } else {
                printf("%d\n", node->total);
            }

        }

    }

    return 0;
}