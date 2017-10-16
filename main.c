// Input: DataSetSize, BufferSize, DatasetFilename, OutputFilename
// Output: the file OutputFilename containing the sorted dataset.

#include <stdio.h>  // printf
#include <ctype.h>  // isspace()

void loadDataset(int* dataset, char* fileName, int datasetSize);

int main(int argc, char* argv[]) {
    int i;
    char* fileName = argv[1];
    int datasetSize = atoi(argv[2]);
    
    int dataset[datasetSize];
    
    loadDataset(dataset, fileName, datasetSize);

    // debug, printing to make sure it's all there
    for (i = 0; i < datasetSize; i++) {
        printf("%d ", dataset[i]);
    }
    
    // compute the average value of the dataset, i.e. sum_of_dataset_values / num_of_dataset_values
    //avg = average(ds)
    // find the max value in the dataset
    //max = maxvalue(ds)
    // find the min value in the dataset
    //min = minvalue(ds)
    // sort the dataset and copy it into the memory area pointed by sds
    //sds = sortDataset(ds,sortingAlgorithm);
    // write the sorted array into a new file plus the valies of the average, min and max as the first three records.
    //writeDataset(OutputFilename,sds,Buffersize, avg, min, max)
    
    printf("argc = %d\n", argc);

    return 0;
}

void loadDataset(int* dataset, char* fileName, int datasetSize) {
    int c, idx = 0;
    FILE* file;
    
    file = fopen(fileName, "r");

    if (file) {
        while ((c = getc(file)) != EOF) {
            if (isspace(c) == 0) {  // discard whitespace
                dataset[idx] = atoi(c);
                idx++;
                //putchar(c);
            }
        }

        fclose(file);
    }
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
