/*
 * matching.c
 *
 *  Created on: Feb 18, 2023
 *      Author: micchen
 */

#include <stdio.h>

// Function that returns 1 if the value is in the array, 0 otherwise
int is_in(int val, int results[]) {
	for (int i = 0; i < 5; i++) {
		if (val == results[i]) {
			return 1;
		}
	}
	return 0;
}

// Function that returns the index that a specific value is at in an array
int find_index(int val, int results[]){
	for (int i = 0; i < 5; i++) {
		if (val == results[i]) {
			return i;
		}
	}
	return 0;
}

int main() {

	FILE *fptr;
	char file_name[100];
	int departments[5][5], programmers[5][5], results[5] = {0, 0, 0, 0, 0};
	int *temp = NULL;

	// Open and read in the input file
	printf("Enter the name of the input file: ");
	scanf("%s", file_name);
	fptr = fopen(file_name, "r");

	if (fptr == NULL) { // Catch potential error
		printf("failed to open file\n");
		return 1;
	}

	// Read in the file, filling out the departments and programmers accordingly
	for (int i = 0; i < 10; i++) {
		if (i < 5) {
			fscanf(fptr, "%d %d %d %d %d", &departments[0][i], &departments[1][i], &departments[2][i], &departments[3][i], &departments[4][i]);
		} else {
			for (int j = 0; j < 5; j++) {
				fscanf(fptr, "%d %d %d %d %d", &programmers[0][j], &programmers[1][j], &programmers[2][j], &programmers[3][j], &programmers[4][j]);
			}
		}
	}

	// Matching algorithm that runs until all matches are made
	while (is_in(0, results)) {
		for (int dept = 0; dept < 5; dept++) {

			if (results[dept] == 0){ // Continue if the department does not have a match
				for (int d_pref = 0; d_pref < 5; d_pref++) {

					if (is_in(departments[dept][d_pref], results) == 1) { // Continue if the desired programmer has already been matched
						temp = &dept; // Pointer used as breakpoint
						for (int p_pref = 0; p_pref < 5; p_pref++) {

							if (programmers[departments[dept][d_pref] - 1][p_pref] == dept + 1) {
								break;
							} else if (programmers[departments[dept][d_pref] - 1][p_pref] == find_index(departments[dept][d_pref], results) + 1) {
								temp = NULL; // Other department has priority, try another programmer
								break;
							}
						}

						if (temp == &dept) { // Move the programmer to the current department
							results[find_index(departments[dept][d_pref], results)] = 0; // Remove programmer from other department
							results[dept] = departments[dept][d_pref]; // Add programmer to current department
							break;
						}

					} else { // Continue if the desired programmer has not been matched
						results[dept] = departments[dept][d_pref]; // Add programmer to current department
						break;
					}
				}
			}
		}
	}

	for (int k = 0; k < 5; k++) { // Print final match results
		printf("\nDepartment #%d will get Programmer #%d", k + 1, results[k]);
	}

	return 0;
}
