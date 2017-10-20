#include <stdio.h>  // printf
#include <ctype.h>  // isspace()
#include <time.h>
#include <stdlib.h>  
#include <string.h>  

float generateRandom(int rmax);
void createDataset(int datasize, char *fileName);

int main(int argc, char* argv[]) {
    srand((unsigned int) time(NULL));
	char* fileName = "dataset";
	size_t datasetSize = atoi(argv[1]);	

	createDataset(datasetSize, fileName);
}

void createDataset(int datasize, char *fileName){

	FILE *f = fopen(fileName, "w");
	for(int i = 0; i < datasize; i++) {
		float value = generateRandom(999);
		fwrite(&value, sizeof(float), 1, f);
	}
	fclose(f);
}

float generateRandom(int rmax) {
    return ((float) rand() / (float)(RAND_MAX) * rmax);
}

