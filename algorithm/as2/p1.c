#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

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

typedef struct _node {
    int val;
    struct _node * next;
}node;

typedef struct _hash{
    int m;
    node *** h;
}hash;

node * createNode(int val){
    node *n = (node*)malloc(sizeof(node));
    n->val = val;
    n->next = NULL;
    return n;
}

void insertLast(node ** head, int key){
    node * newNode = createNode(key);

    if(*head == NULL)
         *head = newNode;
    else
    {
        node *lastNode = *head;
        
        while(lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
}

hash createHash(int m){
    hash res;
    res.m = m;
    res.h = (node ***) malloc(sizeof(node**)*m);
    for(int i = 0 ; i < m ; i++ ){
        res.h[i] =(node**)malloc(sizeof(node*));
        *res.h[i] = NULL;
    }
        
    return res;
}

typedef struct _lenInfo{
    int max;
    int min;
    float avg;
}lenInfo;


lenInfo insert(hash h, int arr[], int size){

    int * len = (int *) malloc(sizeof(int)*size);
    for(int i = 0 ; i < size ; i++){
        len[i] = 0;
    }
    for(int i = 0 ; i < size ; i++){
        int key = arr[i];

        int val = key%h.m;
        len[val]++;
        insertLast(h.h[val],key);
    }

    int sum = 0;
    int max = len[0];
    int min = len[0];
    for (int i = 0; i < h.m; i++) {
        if (len[i] > max) max = len[i];
        if (len[i] < min) min = len[i];
        sum+=len[i];
    }
    float avg = (float)sum/(float)h.m;
    lenInfo info;
    info.max=max;
    info.min=min;
    info.avg=avg;
    return info;
}

void printLinkedList(node ** head){
    node *tmp = *head;

    while(tmp != NULL){
        if(tmp->next == NULL){
            printf("%d", tmp->val);
        }
        else{
            printf("%d, ", tmp->val);
        }
        tmp = tmp->next;
    }
    printf("\n");
}

void printHash(hash h,lenInfo info){
    printf("Hash with size %d\n", h.m);
    int m = h.m;
    for(int i = 0 ; i <m ; i++){
        printLinkedList(h.h[i]);
    }
    printf("\n");
    printf("shortest len : %d\n",info.min);
    printf("longest len : %d\n",info.max);
    printf("average len : %f\n",info.avg);
    printf("===================\n\n");
}

int main(){
    int keys[50];
    initArrRand(keys);

    hash hash_7 = createHash(7);
    hash hash_11 = createHash(11);
    hash hash_12 = createHash(12);

    lenInfo info_7 = insert(hash_7, keys, 50);
    lenInfo info_11 = insert(hash_11, keys, 50);
    lenInfo info_12 = insert(hash_12, keys, 50);

    printHash(hash_7,info_7);
    printHash(hash_11,info_11);
    printHash(hash_12,info_12);

    return 0;
}