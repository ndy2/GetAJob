#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct NODE{
    int data;
    struct NODE * next;
}NODE;

NODE * getNode(int _data){
    NODE * _node = (NODE*)malloc(sizeof(NODE));
    _node->data = _data;
    return _node;
}


int initRandomList(NODE ** head, int len){
    int idx = rand()%len;
    int removeNum;
    *head = getNode(-1);
    NODE * cur = *head;
    for(int i = 0 ; i < len ; i++)
    {
        int data = rand()%100;
        if(idx == i) removeNum = data;
        NODE * newNode = getNode(data);
        cur->next = newNode;
        cur = cur->next;
    }
    return removeNum;
}

int removeNode(NODE ** head, int len, int num){
    int removedLen = 0;
    NODE * removedList =  getNode(-1);
    NODE * cur = removedList;

    NODE * target = (*head)->next;
    for(int i = 0 ; i < len ; i++)
    {
        if(target->data != num){
            cur->next = target;
            cur = cur->next;
            removedLen++;
        }
        target = target->next;
    }

    (*head) = removedList;

    return removedLen;
}

void printList(NODE * list, int len){
    NODE * cur = list->next;
    for(int i = 0 ; i < len ; i++){
        if(i==len/2) printf("\n");
        printf("%d ",cur->data);
        cur = cur->next;
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));
    for(int repeat = 1 ; repeat <= 3;  repeat++){
        
        printf("============REPEAT # %d============\n", repeat);
        int dummy = -1;
        NODE * list;
        int len = 100;
        int removeNum = initRandomList(&list,len);
        printList(list,len);
        printf("remove Num = %d\n", removeNum);
        int removedLen = removeNode(&list, len,  removeNum);
        printf("removed Len = %d\n", removedLen);
        printList(list,removedLen);
        printf("===================================\n");
    }
    return 0;
}