#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int numComp;

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    int L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {
        numComp++;
        if (L[i] > R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
 
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
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
    int check[1000];
    srand(time(NULL));
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
    int arr[100];
    int n = 100;
    printf("Prob 2 \n");
    printf("2-1) Rand\n");

    initArrRand(arr);
    printArray("unsorted\n", arr, n);
    mergeSort(arr, 0, n - 1);
    printArray("sorted \n",arr, n);
    printf("numComp : %d\n\n", numComp);
    numComp = 0;

    printf("2-2) Desc\n");
    initArrDesc(arr);
    printArray("unsorted\n", arr, n);
    mergeSort(arr, 0, n - 1);
    printArray("sorted \n",arr, n);
    printf("numComp : %d\n\n", numComp);
    numComp = 0;

    printf("2-3) Asc\n");
    initArrAsc(arr);
    printArray("unsorted\n", arr, n);
    mergeSort(arr, 0, n - 1);
    printArray("sorted \n",arr, n);
    printf("numComp : %d\n\n", numComp);
    numComp = 0;

    return 0;
}