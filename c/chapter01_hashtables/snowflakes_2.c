// Snowflakes
#include <stdio.h>
#include <stdlib.h>

#define MAX_SNOWFLAKES 100000

typedef struct snowflake_node {
	int snowflake[6];
	struct snowflake_node* next;
} snowflake_node;

/**/

int  code(int snowflake[]);
void identify_identical(snowflake_node *snowflakes[]);
int  are_identical(int snow1[], int snow2[]);
int  identical_right(int snow1[], int snow2[], int start);
int  identical_left(int snow1[], int snow2[], int start);

int main(void) {

	// Static causes this variable to live in the Global/static data segment, not on the stack or the heap
	// where it could easily cause a stack overflow. 
	// This is the same behavior as defining snowflakes without `static`, outside of main(), however
	// This would cause it to become a global variable. With `static` we gain the lifetime benefits
	// of a global without the actual global scope.
	static snowflake_node *snowflakes[MAX_SNOWFLAKES] = {NULL};
	snowflake_node* snow;

	int n, i, j, snowflake_code;

	printf("Num Snowflakes: ");
	scanf("%d", &n);
	printf("------------------\n");

	for (i = 0; i < n; i++) {
	
		// Weather allocation
		snow = malloc(sizeof(snowflake_node));
		if (snow == NULL) {
			fprintf(stderr, "err 1\n");
			exit(1);
		}

		for (j = 0; j < 6; j++) {
			scanf("%d", &snow->snowflake[j]);
		}

		snowflake_code = code(snow->snowflake);
		snow->next = snowflakes[snowflake_code]; // snow->next points to whatever is at snowflake_code
		snowflakes[snowflake_code] = snow;		 // update [snowflake_code]. It now contains a pointer to `snow`
		
	}

	return 0;
}

int code(int snowflake[]) {

	return (snowflake[0] + snowflake[1] + snowflake[2] + 
			snowflake[3] + snowflake[4] + snowflake[5]) % MAX_SNOWFLAKES;
}

void identify_identical(snowflake_node *snowflakes[]) {

	snowflake_node *node1, *node2;
	int i;

	for (i = 0; i < MAX_SNOWFLAKES; i++) {
		node1 = snowflakes[i];
		if (node1 != NULL) {
			
		}
	}
}

int are_identical(int snow1[], int snow2[]) {
	int start;
	for (start = 0; start < 6; start++) {
		if(identical_right(snow1, snow2, start)) { printf("Identical Right!!\n"); return 1; }
		if(identical_left(snow1, snow2, start)) { printf("Identical Left!!\n"); return 1; }
	}

	printf("No identical conditions found\n");

	return 0;
}

// Clockwise comparison
int identical_right(int snow1[], int snow2[], int start) {

	int offset, index2;
	for (offset = 0; offset < 6; offset++) {
		index2 = (start + offset) % 6;
		if(snow1[offset] != snow2[index2]) {
			// Obviously not identical. return falsey
			return 0;
		}
	}
	return 1;
}

int identical_left(int snow1[], int snow2[], int start) {

	int offset, index2;

	for (offset=0; offset < 6; offset++) {
		index2 = start - offset;
		if(index2 < 0) { index2 += 6; }
		if(snow1[offset] != snow2[index2]) { return 0; }	
	}

	return 1;

}