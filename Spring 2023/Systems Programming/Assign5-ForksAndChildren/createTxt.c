#include <stdio.h>

int main() {

	FILE *file = fopen("example.txt", "w");
	for (int i = 0; i < 100000; i++) {
		fprintf(file, "This is a random line with eight words\n");

	}
	fclose(file);
}
