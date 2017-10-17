// Input: DataSetSize, BufferSize, DatasetFilename, OutputFilename
// Output: the file OutputFilename containing the sorted dataset.

#include <stdio.h>  // printf
#include <ctype.h>  // isspace()
#include <stdlib.h>  
#include <string.h>  
#include <time.h>

void loadDataset(int *dataset, char *fileName, int datasetSize);
double average(int *dataset, int datasize);
int maxvalue(int *dataset, int datasize);
int minvalue(int* dataset, int datasize);
void selectionSort(int arr[], int n);
float generateRandom(int rmax);
int writeDataset(char* outputfileName, int datasetSize, int* sortedDataset, int* avg, int* min, int* max);

int main(int argc, char* argv[]) {
    srand((unsigned int) time(NULL));
	char* fileName;
	double avg;
	int min;
	int max;
	int sds;

	size_t filenameSize = (strlen(argv[1]) + 1)*sizeof(char);
	fileName = malloc(filenameSize);
	strncpy(fileName, argv[1], filenameSize);

    int datasetSize = (atoi(argv[2]));

    int dataset[datasetSize];
	memset(dataset,0, datasetSize*sizeof(int));
	
    loadDataset(dataset, fileName, datasetSize);

    // sort the dataset and copy it into the memory area pointed by sds
    //sortedDataset = sortDataset(ds,sortingAlgorithm);
	selectionSort(dataset, datasetSize);
   
    // compute the average value of the dataset, i.e. sum_of_dataset_values / num_of_dataset_values
	avg = average(dataset, datasetSize);
    printf("average: %lf \n", avg);
	
    // find the max value in the dataset
	max = maxvalue(dataset, datasetSize);
	
    // find the min value in the dataset
	min = minvalue(dataset, datasetSize);
    printf("min: %d \n", min);

    // write the sorted array into a new file plus the values of the average, min and max as the first three records.
    writeDataset(OutputFilename,sds,Buffersize, avg, min, max);
    writeDataset(outputFileName, datasetSize, sortedDataset, &avg, &min, &max);
       
	free(fileName);

    return 0;
}

void loadDataset(int* dataset, char* fileName, int datasetSize) {
    int c, idx = 0;
    FILE* file;
    
    file = fopen(fileName, "r");

    if (file) {
        while ((c = getc(file)) != EOF) {
            if (isspace(c) == 0) {  // discard whitespace
                dataset[idx] = atoi(&c);
                idx++;
                //putchar(c);
            }
        }

        fclose(file);
    }
}

double average(int* dataset, int datasize){
	double value = 0;
	//printf("\n%d \n", datasize);

	for(int i = 0; i < datasize; i++) {
		value += dataset[i];
	}
	//printf("%lf \n", value);
	return value/datasize;
}

int maxvalue(int* dataset, int datasize){
	int value = dataset[0];

	for(int i = 0; i < datasize; i++) {
		if (value < dataset[i])
			value = dataset[i];
	}
	return value;
}

int minvalue(int* dataset, int datasize){
	int value = dataset[0];

	for(int i = 0; i < datasize; i++) {
		if (value > dataset[i])
			value = dataset[i];
	}
	return value;
}

void swap(int* xp, int* yp) {
    int temp = *xp;
    
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int arr[], int n) {
    int i, j, min_idx;

    for (int i = 0; i < n - 1; i++) {
        min_idx = i;

        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        swap(&arr[min_idx], &arr[i]);
    }
}

float generateRandom(int rmax) {
    return ((float) rand() / (float)(RAND_MAX) * rmax);
}

int writeDataset(char* fileName, int datasetSize, int* sortedDataset, int* avg, int* min, int* max) {
    int i = 0;
    FILE* file;

    file = fopen(filename, "w");

    if (file) {
        fwrite(avg, 1, sizeof(float), file);
        fwrite(min, 1, sizeof(float), file);
        fwrite(max, 1, sizeof(float), file);

        for (i = 1; i <= datasetSize, i++) {
            fwrite(sortedDataset[i], 1, sizeof(float), file);
        }

        fclose(file);
    }

    return 0;
}
