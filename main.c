// Input: DataSetSize, BufferSize, DatasetFilename, OutputFilename
// Output: the file OutputFilename containing the sorted dataset.

#include <stdio.h>  // printf
#include <ctype.h>  // isspace()
#include <stdlib.h>  
#include <string.h>  

void loadDataset(int *dataset, char *fileName, int datasetSize);
float average(float *dataset, int datasize);
float maxvalue(float *dataset, int datasize);
float minvalue(float *dataset, int datasize);
void createDataset(int datasize, char *fileName);

int main(int argc, char* argv[]) {
	char* fileName;
	double avg;
	float min;
	float max;
	float sds;

	size_t filenameSize = (strlen(argv[1]) + 1)*sizeof(char);
	fileName = malloc(filenameSize);
	strncpy(fileName, argv[1], filenameSize);

    	int datasetSize = (atoi(argv[2]));


    	float dataset[datasetSize];
	memset(dataset,0, datasetSize*sizeof(int));

    
    createDataset(datasetSize, fileName);
	
    _loadDataset(dataset, datasetSize, fileName);

    // debug, printing to make sure it's all there
   
    // compute the average value of the dataset, i.e. sum_of_dataset_values / num_of_dataset_values
	avg = average(dataset, datasetSize);
    	printf("average: %lf \n", avg);
	
    // find the max value in the dataset
	max = maxvalue(dataset, datasetSize);
    	printf("max: %lf \n", max);
	
    // find the min value in the dataset
	min = minvalue(dataset, datasetSize);
    	printf("min: %lf \n", min);

    // sort the dataset and copy it into the memory area pointed by sds
    //sds = sortDataset(ds,sortingAlgorithm);
    // write the sorted array into a new file plus the valies of the average, min and max as the first three records.
    //writeDataset(OutputFilename,sds,Buffersize, avg, min, max)
    
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

void _loadDataset(float* v, int datasize, char *fileName) {

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
		v[i] = rand() % 100;
	}

	FILE *f = fopen(fileName, "w");
	for(int i = 0; i < datasize; i++) {
		float value = v[i];
		fwrite(&value, sizeof(float), 1, f);
	}
	fclose(f);
}
/*void swap(int* xp, int* yp) {
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

        swap(&arr[min_idx], %arr[i]);
    }
}*/
