// Input: DataSetSize, BufferSize, DatasetFilename, OutputFilename
// Output: the file OutputFilename containing the sorted dataset.

#include <stdio.h>  // printf
#include <ctype.h>  // isspace()
#include <stdlib.h>  
#include <string.h>  
#include <time.h>

void loadDataset(float* v, int datasize, char *fileName, int buffsize);
float average(float *dataset, int datasize);
float maxvalue(float *dataset, int datasize);
float minvalue(float *dataset, int datasize);
int cmpfunc(const void *first, const void *second);
void createDataset(int datasize, char *fileName);
float* selectionSort(float* dataset, int datasetSize);
float* sortData(float* dataset, int datasetSize, char* sortingAlgorithm);
float generateRandom(int rmax);
int writeDataset(char* fileName, int datasetSize, float* sortedDataset, float avg, float min, float max, int buffsize);


int main(int argc, char* argv[]) {
    srand((unsigned int) time(NULL));
	char* fileName;
	double avg;
	float min;
	float max;
	float sds;
    float* sortedDataset;

	fileName = "dataset";

    size_t datasetSize = atoi(argv[1]);
	int buffsize = atoi(argv[2]);


	size_t dataset_size = (datasetSize)*sizeof(float);
	float *dataset = malloc(dataset_size);
		
    loadDataset(dataset, datasetSize, fileName, buffsize);


    // write the sorted array into a new file plus the values of the average, min and max as the first three records.
    // sort the dataset and copy it into the memory area pointed by sds
    sortedDataset = sortData(dataset, datasetSize, "quicksort");
	// sortedDataset = selectionSort(dataset, datasetSize);
    //writeDataset(OutputFilename,sds,Buffersize, avg, min, max);
    // compute the average value of the dataset, i.e. sum_of_dataset_values / num_of_dataset_values
	avg = average(dataset, datasetSize);
	
    // find the max value in the dataset
	max = sortedDataset[datasetSize -1];
	
    // find the min value in the dataset
	min = sortedDataset[0];

    writeDataset("outputFile", datasetSize, sortedDataset, avg, min, max, buffsize);
	
	free(dataset);

    return 0;
}

void loadDataset(float* v, int datasize, char *fileName, int buffsize) {

	FILE* f;
	f = fopen(fileName, "r");
	if(f != NULL){
		for(int i = 0; i < datasize; i+= buffsize) {
			fread(&v[i], sizeof(float), buffsize, f);
	}
	fclose(f);
}
	
	
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

int cmpfunc(const void *first, const void *second) {
    return (*(int *) first - *(int *) second);
}

float* sortData(float* dataset, int datasetSize, char* sortingAlgorithm) {
    float* ret;

    if (strcmp(sortingAlgorithm, "quicksort") == 0) {
        qsort(dataset, datasetSize, sizeof(float), cmpfunc);
        ret = dataset;
    } else if(strcmp(sortingAlgorithm, "selectionsort") == 0 ) {
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




int writeDataset(char* fileName, int datasetSize, float* sortedDataset, float avg, float min, float max, int buffsize) {
    int i = 0;
    FILE* file;

    file = fopen(fileName, "w");

    if (file) {
        fwrite(&avg, 4, sizeof(avg), file);
        fwrite(&min, 4, sizeof(min), file);
        fwrite(&max, 4, sizeof(max), file);

		for(int i = 0; i < datasetSize; i+= buffsize) 
			fwrite(&sortedDataset[i], buffsize,sizeof(sortedDataset), file);

        fclose(file);
    }

    return 0;
}
