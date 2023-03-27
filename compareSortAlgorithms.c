#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge (int arr[], int l, int m, int r)
{
	int *temp, i, len, cout1, cout2, index;

	len = r - l + 1;
	temp = (int*)malloc(len*sizeof(int));

	cout1 = l;
	cout2 = m +1;

	index = 0;

	// copy array into temp array
	while((cout1 <= m)&&(cout2 <= r))
	{
		if (arr[cout1] < arr[cout2])
		{
			temp[index] = arr[cout1];
			cout1++;
			index++;
		}
		else
		{
			temp[index] = arr[cout2];
			index++;
			cout2++;
		}	
	}
		
	while (cout1 <= m)
	{
		temp[index] = arr[cout1];
		index++;
		cout1++;
	}

	while (cout2 <= r)
	{
		temp[index] = arr[cout2];
		index++;
		cout2++;
	}
	

	for (i = l; i <= r; i++)
	{
		arr[i] = temp[i-l];
	}

	free(temp);
}

void mergeSort(int pData[], int l, int r)
{
	if (l < r)
	{
	// find the middle point to divide the array into two halves
	int m = (l+r)/2;

	//call mergeSort for first half
	mergeSort(pData, l, m);

	// call mergeSort for second half
	mergeSort(pData, m+1, r);

	merge(pData, l, m, r);

	extraMemoryAllocated += sizeof(l) + sizeof(r);
	}
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int i, j, temp;
	for (i = 1; i < n; i ++)
	{
		temp = pData[i];
		j = i - 1;
		while((temp < pData[j])&& (j >= 0))
		{
			pData[j+1] = pData[j];
			j--;
		}
		pData[j+1] = temp;
	}
	extraMemoryAllocated = 0;
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated

void bubbleSort(int* pData, int n)
{
	int i, j, temp;
	for (i=0; i < n-1; i++)
	{
		for (j = 0; j < n-i-1; j++)
		{
			if (pData[j] > pData[j+1])
			{
				temp = pData[j];
				pData[j]=pData[j+1];
				pData[j+1]=temp;
			}
		}
	}
	extraMemoryAllocated = 0;
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int i, j, min, temp;

	for (i = 0; i < n-1; i++)
	{
		min = i;
		for (j = i+1; j < n; j++)
		{
			if (pData[j] < pData[min])
			{
				min = j;
			}
		}

		temp = pData[i];
		pData[i] = pData[min];
		pData[min] = temp;

	}
	extraMemoryAllocated = 0;
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		for (int i = 0; i < dataSz; i++)
		{
			fscanf(inFile, "%d", &(*ppData)[i]);
		}
		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}