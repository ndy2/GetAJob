#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LIN 1
#define QUAD 2
#define DOU 3

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


typedef struct _hash{
    int * arr;
    int m;

    int numInsert;
    int sumProbes;
}hash;

int getMaxClusterLength(hash h){
    int * arr = h.arr;
    int max = 0;
    int combo = 0;
    for(int i = 0 ; i < h.m ; i++){
        if(arr[i]!=-1){
            combo++;
            if(combo > max) max = combo;
        }
        else{
            combo=0;
        }
    }
    return max;
}

hash createHash(int m){
    hash h;
    int * arr = (int*)malloc(sizeof(int)*m);
    for(int i = 0 ; i < m ; i++)
        arr[i] = -1;
    h.m=m;
    h.arr =arr;
    h.numInsert=0;
    h.sumProbes=0;
    return h;
}


int prob(hash h, int key,int type){
    
    int key_save = key;
    int cnt = 0;
    int i =0;
    int pos;
    do{
        key %=h.m; // h'(k)
        if(type == LIN){
            pos = key + i;
        }
        else if(type == QUAD){
            pos = key + i + 3*i*i;
        }
        else if(type == DOU){
            int key2 = key_save%(h.m-1); //h_2(k)
            pos = key + i * key2;
        }
        pos %= h.m; // final modulo operation
        i ++;       //keep count
    }while(h.arr[pos]!=-1);

    h.arr[pos] = key_save;
    

    return i;
}

void insert(hash *in, int arr[],int size,int type){
    hash h = *in;
    for(int i = 0 ; i < size; i++){
        int key = arr[i];
        printf("%d ",key);
        h.sumProbes+= prob(h,key,type);
        h.numInsert+=1;
    }
    printf("\n");
   *in = h;
}

void printHash(hash h){
    for(int i = 0 ; i < h.m; i++){
        printf("%d ",h.arr[i]);
    }
    printf("\n");
    printf("avg probes per insertion : %f\n", (float)h.sumProbes/(float)h.numInsert);
    printf("largest cluster length : %d\n\n", getMaxClusterLength(h));
}

void printArr(int arr[],int size){
    for(int i = 0 ; i < size; i++){
        printf("%d ",arr[i]);
    }
    printf("\n\n");
}

void freeHash(hash h){
    free(h.arr);
}

int main(){
    int keys[35];
    initArrRand(keys);
    printf("========keys===========\n");
    printArr(keys,35);

    printf("========Linear Hashing ===========\n");
    hash lin = createHash(41);
    insert(&lin,keys,35,LIN);
    printHash(lin);
    freeHash(lin);

    printf("========Quad Hashing ===========\n");
    hash quad = createHash(41);
    insert(&quad,keys,35,QUAD);
    printHash(quad);
    freeHash(quad);

    printf("========Dobule Hashing ===========\n");
    hash _double = createHash(41);
    insert(&_double,keys,35,DOU);
    printHash(_double);
    freeHash(_double);

    return 0;
}