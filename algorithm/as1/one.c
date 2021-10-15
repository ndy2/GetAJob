#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int insertionSort(int arr[], int n)
{   
    int numComp = 0;
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j>=0 &&(++numComp) &&arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
    return numComp;
}
 
void printArray(char* s,int arr[], int n)
{
    printf("%s",s);
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n\n");
}

void initArrRand(int arr[]){
    srand(time(NULL));
    int check[1000];
    memset(check, 0, sizeof(check));
    int num;
    for(int i = 0 ; i < 100 ; i++){
        do{
            num = rand()%1000;
        }while(check[num]==1);
        check[num] = 1;
        arr[i] = num;
    }
}


void initArrAsc(int arr[]){
    for(int i = 0 ; i < 100 ; i++)
        arr[i] = i+1;
}

void initArrDesc(int arr[]){
    for(int i = 0 ; i < 100 ; i++)
        arr[i] = 100-i;
}

int main()
{
    printf("Prob 1 \n");
    int arr[100];
    int n = 100;
    int numComp;

    printf("1-1) Rand\n");
    initArrRand(arr);
    printArray("unsorted\n",arr,n);
    numComp = insertionSort(arr, n);
    printArray("sorted\n",arr, n);
    printf("numComp : %d\n\n",numComp);
 
    printf("1-2) Asc\n");
    initArrAsc(arr);
    printArray("unsorted\n",arr,n);
    numComp = insertionSort(arr, n);
    printArray("sorted\n",arr, n);
    printf("numComp : %d\n\n",numComp);

    printf("1-3) Desc\n");
    initArrDesc(arr);
    printArray("unsorted\n",arr,n);
    numComp = insertionSort(arr, n);
    printArray("sorted\n",arr, n);
    printf("numComp : %d\n\n",numComp);

    return 0;
}