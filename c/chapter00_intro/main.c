#include <stdio.h>

int main(void) {

	int nlines;
	int nwalkins;

	printf("Number of lines: ");
	scanf("%d", &nlines);

	// Array for number of ppl in each line
	int linelens[nlines];

	printf("Number of walkins: ");
	scanf("%d", &nwalkins);

	for(int i = 0; i < nlines; i++) {
		printf("Enter n people in line %d:", i + 1);	
		int np;
		scanf("%d", &np);
		linelens[i] = np;
		
	}

	// Line with the least number of people
	int shortest = 0;

	for(int i = 0; i < nwalkins; i++) {
		printf("\n\n");	

		for (int j = 0; j < nlines; j++) {
			printf("Line %d has %d people\n", j, linelens[j]);
			printf("Shortest has: %d\n", shortest);
			// j represents the line number
			if(linelens[j] < linelens[shortest]) {
				// found new shortest line
				printf("Found new shortest line: %d\n", j);
				shortest = j;
			}
		}
		
		// Add person to shortest line
		linelens[shortest]++;

		// print lines visually
		for (int j = 0; j < nlines; j++) {

			printf("[line %d]: ", j);	

			for (int k = 0; k < linelens[j]; k++) {
				printf("# ");
			}

			printf("\n");
		}
	}

	return 0;

}
