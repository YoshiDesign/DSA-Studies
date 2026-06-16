// Snowflakes
#include <stdio.h>

#define MAX_SNOWFLAKES 100000

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

int are_identical(int snow1[], int snow2[]) {
	int start;
	for (start = 0; start < 6; start++) {
		if(identical_right(snow1, snow2, start)) { printf("Identical Right!!\n"); return 1; }
		if(identical_left(snow1, snow2, start)) { printf("Identical Left!!\n"); return 1; }
	}

	printf("No identical conditions found\n");

	return 0;
}

void identify_identical(int (*snowflakes)[6], int n) {

	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 1; j < n; j++) {
			if (are_identical(snowflakes[i], snowflakes[j])) {
				printf("Twin snowflakes found!\n");
				// return;
			}
			printf("[%d, %d] Nope...\n", i, j);
		}
	
	}

	printf("No matches found...\n");
	return;

}

int main(void) {

	static int snow1[MAX_SNOWFLAKES][6]; 

	int n, i, j;
	printf("Number of snowflakes: ");
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
	
		for (j = 0; j < 6; j++) {
			printf("[%d, %d]: ");	
			scanf("%d", i, j, &snowflakes[i][j]);
		}
	}

	identify_identical(snow1, 4);

	/*
	for (int i = 0; i < MAX_SNOWFLAKES; i++) {
		printf("Round %d...\n", i);
		are_identical(snow1[i], snow2[i]);	
	}
	*/

	printf("Done!\n");

	return 0;
}
