// Input: DataSetSize, BufferSize, DatasetFilename, OutputFilename
// Output: the file OutputFilename containing the sorted dataset.

#include <stdio.h>  // printf
#include <ctype.h>  // isspace()
#include <stdlib.h>  
#include <string.h>  
#include <time.h>

void loadDataset(float* v, int datasize, char *fileName);
float average(float *dataset, int datasize);
float maxvalue(float *dataset, int datasize);
float minvalue(float *dataset, int datasize);
void createDataset(int datasize, char *fileName);
float* selectionSort(float* dataset, int datasetSize);
float* sortData(float* dataset, int datasetSize, char* sortingAlgorithm);
float generateRandom(int rmax);
int writeDataset(char* fileName, int datasetSize, float* sortedDataset, float avg, float min, float max);

int main(int argc, char* argv[]) {
    srand((unsigned int) time(NULL));
	char* fileName;
	double avg;
	float min;
	float max;
	float sds;
    float* sortedDataset;

	//size_t filenameSize = (strlen(argv[1]) + 1)*sizeof(char);
	//fileName = malloc(filenameSize);
	//strncpy(fileName, argv[1], filenameSize);

    int datasetSize = 102400;

    float dataset[datasetSize];
	//memset(dataset,0, datasetSize*sizeof(int));
    
    //createDataset(datasetSize, fileName);
	
    loadDataset(dataset, datasetSize, "dataset");


    // compute the average value of the dataset, i.e. sum_of_dataset_values / num_of_dataset_values
	avg = average(dataset, datasetSize);
	
    // find the max value in the dataset
	max = maxvalue(dataset, datasetSize);
	
    // find the min value in the dataset
	min = minvalue(dataset, datasetSize);

    // write the sorted array into a new file plus the values of the average, min and max as the first three records.
    // sort the dataset and copy it into the memory area pointed by sds
    sortedDataset = sortData(dataset, datasetSize, "quicksort");
	//sortedDataset = selectionSort(dataset, datasetSize);
    //writeDataset(OutputFilename,sds,Buffersize, avg, min, max);
    writeDataset("outputFile", datasetSize, sortedDataset, avg, min, max);
       
	//free(fileName);

    return 0;
}

void loadDataset(float* v, int datasize, char *fileName) {

	FILE* f;
	f = fopen(fileName, "r");
	for(int i = 0; i < datasize; i++) {
		fread(&v[i], sizeof(float), 1, f);
	}
	fclose(f);
}

float average(float* dataset, int datasize){
	float value = 0;
	for(int i = 0; i < datasize; i++) {
		value += dataset[i];
	}

	return value/datasize;
}

float maxvalue(float* dataset, int datasize){
	float value = dataset[0];

	for(int i = 1; i < datasize; i++) {
		if (value < dataset[i])
			value = dataset[i];
	}
	return value;
}

float minvalue(float* dataset, int datasize){
	float value = dataset[0];

	for(int i = 1; i < datasize; i++) {
		if (value > dataset[i])
			value = dataset[i];
	}
	return value;
}

void createDataset(int datasize, char *fileName){

	float v[datasize];
	
	for(int i = 0; i < datasize; i++){
		v[i] = generateRandom(999);
	}

	FILE *f = fopen(fileName, "w");
	for(int i = 0; i < datasize; i++) {
		float value = v[i];
		fwrite(&value, sizeof(float), 1, f);
	}
	fclose(f);
}

int cmpfunc(const void *first, const void *second) {
    return (*(int *) first - *(int *) second);
}

float* sortData(float* dataset, int datasetSize, char* sortingAlgorithm) {
    float* ret;

    if (strcmp(sortingAlgorithm, "quicksort") == 0) {
        puts("quicksort selected");
        qsort(dataset, datasetSize, sizeof(float), cmpfunc);
        ret = dataset;
    } else if(strcmp(sortingAlgorithm, "selectionsort") == 0 ) {
        puts("selectionsort selected");
        ret = selectionSort(dataset, datasetSize);
    }

    return ret;
}

void swap(float* xp, float* yp) {
    float temp = *xp;
    
    *xp = *yp;
    *yp = temp;
}

float* selectionSort(float* dataset, int datasetSize) {
    int i, j, min_idx;

    for (int i = 0; i < datasetSize - 1; i++) {
        min_idx = i;

        for (j = i + 1; j < datasetSize; j++) {
            if (dataset[j] < dataset[min_idx]) {
                min_idx = j;
            }
        }

        swap(&dataset[min_idx], &dataset[i]);
    }

    return dataset;
}


float generateRandom(int rmax) {
    return ((float) rand() / (float)(RAND_MAX) * rmax);
}

int writeDataset(char* fileName, int datasetSize, float* sortedDataset, float avg, float min, float max) {
    int i = 0;
    FILE* file;

    file = fopen(fileName, "w");

    if (file) {
        fprintf(file, "avg: %f\n", 1, avg);
        fprintf(file, "min: %f\n", 1, min);
        fprintf(file, "max: %f\n\n", 1, max);

        for (i = 0; i < datasetSize; i++) {
            fprintf(file, "%f\n", 1, sortedDataset[i]);
        }

        fclose(file);
    }

    return 0;
}
