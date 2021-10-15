#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define NILVAL -2016310703


typedef struct _node{

    int val;
    char color;
    struct _node * parent;
    struct _node * left;
    struct _node * right;

}node;
typedef struct _tree{
    int m;
    node * root;
    node * nil;
    bool * exist;
}tree;


/**
* constructor
**/
node * createNode(int val, node*nilRef){
    node * n = (node*)malloc(sizeof(node));
    n->val = val;
    n->color = 'r';
    n->parent = NULL;
    n->left = nilRef;
    n->right = nilRef;
    return n;
}
node * createNil(){
    node * nil = (node*)malloc(sizeof(node));
    nil->color = 'b';
    nil->val = NILVAL;
    return nil;
}
tree createTree(int m){
    tree t;
    t.root = NULL;
    t.nil = createNil();
    t.m = m;
    t.exist = (bool*)malloc(sizeof(bool)*m);
    memset(t.exist,false,m*sizeof(bool));
    return t;
}


/**
* utils
**/
void initArrRand(int arr[], int size, int m){
    srand(time(NULL));
    int * check = (int*)malloc(sizeof(int)*m);
    memset(check, 0, sizeof(check));
    int num;
    for(int i = 0 ; i < size ; i++){
        do{
            num = rand()%60;
        }while(check[num]==1);
        check[num] = 1;
        arr[i] = num;
    }
}
void printArr(int arr[],int size){
    for(int i = 0 ; i < size; i++){
        printf("%d ",arr[i]);
    }
    printf("\n\n");
}

// copy util
node* copyNode(node *root, node* nilRef, node * parent){
    if(root->val == NILVAL)
        return nilRef;
    node* n = createNode(root->val,nilRef);
    n->color = root->color;
    n->parent = parent;
    n->left = copyNode(root->left,nilRef,n);
    n->right = copyNode(root->right,nilRef,n);
    return n;
}
tree copyTree(tree in){
    tree t;
    t.nil= createNil();             //create new nil reference
    
    t.m=in.m;   
    t.root= copyNode(in.root,t.nil,t.root);
    
    t.exist = (bool*)malloc(sizeof(bool)*in.m);
    for(int i = 0 ; i < in.m ; i++)
        t.exist[i] = in.exist[i];   //copy arr
    
    return t;
}

// 3.1.c
int _print_t(node *tree, int is_left, int offset, int depth, char s[20][400])
{
    char b[20];
    int width = 5;

    if (tree->val == -2016310703) return 0;

    sprintf(b, " %03d%c", tree->val,tree->color);

    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }

    return left + width + right;
}
void print_t(node *tree)
{
    char s[20][400];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%120s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}



/**
* helper
**/
bool isRoot(node * n, tree t){
    return n->parent==t.nil;
}
bool isNil(node * n, tree t){
    return n==t.nil;
}
bool isEmpty(tree t){
    return t.root==NULL;
}


/**
* rotates
**/
void leftRotate(tree * in, node * x){
    tree t = *in;
    node * y = x->right;
    x->right = y->left;

    if(!isNil(y->left,t))
        y->left->parent=x;
    
    y->parent=x->parent;

    if(isNil(x->parent,t))
        t.root=y;
    else if(x==x->parent->left)
        x->parent->left=y;
    else
        x->parent->right=y;

    y->left = x;
    x->parent=y;
    *in = t;
}
void rightRotate(tree *in, node * y){
    tree t = *in;
    node * x = y->left;
    y->left = x->right;
    if(!isNil(x->right,t))
        x->right->parent=y;
    
    x->parent = y->parent;
    if(isNil(y->parent,t))
        t.root = x;
    else if(y==y->parent->left)
        y->parent->left = x;
    else
        y->parent->right =x;

    x->right = y;
    y->parent = x;

    *in = t;
}


/**
* insert
* 3.1.a
**/
void insertFixUp(tree * in, node * z){
    tree t = *in;
    int val_save = z->val;
        
    while(z->parent->color=='r')
        {
            if(z->parent==z->parent->parent->left){
                node * y = z->parent->parent->right; //uncle
                if(y->color=='r'){                   //push blackness down from grandparent
                    z->parent->color='b';
                    y->color='b';
                    z->parent->parent->color='r';
                    z=z->parent->parent;
                }
                else{ 
                    if(z==z->parent->right){        // angle shape (<) => make linear shape
                        z = z->parent;
                        leftRotate(&t,z);
                    }
                    z->parent->color='b';           // linear shape (/)
                    z->parent->parent->color='r';
                    rightRotate(&t,z->parent->parent);
                }
            }
            else{
                node * y = z->parent->parent->left; //uncle
                if(y->color=='r'){                  //push blackness down from grandparent
                    z->parent->color='b';       
                    y->color='b';
                    z->parent->parent->color='r';
                    z=z->parent->parent;
                }
                else{ 
                    if(z==z->parent->left){         // angle shape (>) => make linear shape
                        z = z->parent;
                        rightRotate(&t,z);
                    }
                    z->parent->color='b';           // linear shape (\)
                    z->parent->parent->color='r';
                    leftRotate(&t,z->parent->parent);
                    
                }
            }
        }

    t.root->color ='b';
    *in = t;
}
void insert(tree * in, node* z){
    tree t = *in;
    if(isEmpty(t))
        {
            z->color = 'b';
            z->parent = t.nil;
            t.root = z;
        }
    else{
            node * y = t.nil;
            node * x = t.root;

            while(!isNil(x,t)){
                y = x;
                if(z->val < x->val)
                    x = x->left;
                else x = x->right;
            }
            z->parent=y;

            if(isNil(y,t))
                t.root = z;
            else if(z->val<y->val)
                y->left = z;
            else y->right = z;

            insertFixUp(&t, z);
        }
    *in = t;
}
bool insertVal(tree *in, int val){
    if(in->exist[val]) return false;
    tree t = *in;
    node* z = createNode(val,t.nil);
    insert(&t,z);
    *in = t;
    return true;
}
void insertArr(tree *in, int arr[],int size, bool print){

    if(print) {
        printf("====== insert Keys ======\n");
        printArr(arr,size);
    }
    tree t = *in;
    for(int i = 0 ; i < size ; i++){
        int val = arr[i];
        bool out = insertVal(&t,arr[i]);
        t.exist[val] = true;

        if(print){
            if(out){
                printf("insert %d complete\n", val);
                printf("result : \n");
                print_t(t.root);
            }else{
                printf("value %d already exists, nothing happend\n",val);
            }
        }
        
    }
    *in = t;
}


/**
* delete
* 3.1.b
**/
void transplant (tree * in, node * u, node *v){
    tree t = *in;
    if(isNil(u->parent,t))
        t.root = v;
    else if(u==u->parent->left)
        u->parent->left=v;
    else
        u->parent->right=v;
    v->parent=u->parent;
    *in = t;    
}
node * getMinNode(node * root){
    while (root->left->val!=NILVAL) {
    root = root->left;
  }
  return root;
}
node * findByVal(tree t, int val){
    node * z = NULL;

    node * cur = t.root;
    while(!isNil(cur,t)){
        if(val == cur->val)
            return cur;
        else if(val<cur->val)
            cur = cur->left;
        else
            cur = cur->right;
    }

    return z;
}
void deleteFixUp(tree * in, node *x){
    tree t = *in;

    while(!isNil(x,t) && x->color=='b'){
        if(x==x->parent->left){
            node * w = x->parent->right;
            if(w->color=='r'){
                w->color='b';
                x->parent->color='r';
                leftRotate(&t,x->parent);
                w=x->parent->right;
            }

            if(w->left->color=='b' && w->right->color=='b'){
                w->color='r';
                x=x->parent;
            }
            else{ 
                if(w->right->color =='b'){
                    w->left->color='b';
                    w->color='r';
                    rightRotate(&t,w);
                    w=x->parent->right;
                }
                w->color=x->parent->color;
                x->parent->color='b';
                w->right->color='b';
                leftRotate(&t,x->parent);
                x=t.root;
            }
        }
        else{
            node * w = x->parent->left;
            if(w->color=='r'){
                w->color='b';
                x->parent->color='r';
                rightRotate(&t,x->parent);
                w=x->parent->left;
            }

            if(w->right->color=='b' && w->left->color=='b'){
                w->color='r';
                x=x->parent;
            }
            else{ 
                if(w->left->color =='b'){
                    w->right->color='b';
                    w->color='r';
                    leftRotate(&t,w);
                    w=x->parent->left;
                }
                w->color=x->parent->color;
                x->parent->color='b';
                w->left->color='b';
                rightRotate(&t,x->parent);
                x=t.root;
            }
        }
    }
    x->color = 'b';
    *in = t;
}
void deleteNode(tree * in, node * z){
    tree t = *in;
    node * y = z;
    node * x;
    char yOrigColer= y->color;
    if(isNil(z->left,t)){
        x = z->right;
        transplant(&t,z,z->right);
    }
    else if(isNil(z->right,t)){
        x = z->left;
        transplant(&t,z,z->left);
    }
    else{
        y = getMinNode(z->right);
        yOrigColer=y->color;
        x = y->right;
        
        if(y->parent==z){
            x->parent = y->right;
        }
        else{
            transplant(&t,y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(&t,z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if(yOrigColer == 'b'){
        deleteFixUp(&t, x);
    }

    *in = t;    
}
bool deleteVal(tree *in, int val){
    tree t = *in;
    
    node * z = findByVal(t, val);
    if(z==NULL){
        return false;
    }
    deleteNode(&t,z);
    *in = t;
    return true;
}
void deleteArr(tree *in, int arr[], int size, bool print){
    if(print){
        printf("====== delete Keys ======\n");
        printArr(arr,size);
    }
    tree t = *in;
    for(int i = 0 ; i < size ; i++){
        int val = arr[i];
        bool out = deleteVal(&t,arr[i]);
        t.exist[val] = false;
        if(print){
            if(out){
                printf("delete %d complete\n", val);
                printf("result : \n");
                print_t(t.root);
            }else{
                printf("value %d does not exist, nothing happend\n", val);
            }
        }
    }
    *in = t;
}

int main(){
    
    int m = 60;
    tree t = createTree(m);
    
    // 3.2
    int arr[20]; int size =20;
    initArrRand(arr,size,m);
    printf("====== insert Keys ======\n");
    printArr(arr,size);
    insertArr(&t,arr,size,false);
    print_t(t.root);
    tree t2 = copyTree(t);

    // 3.3
    int arrInsert[5] = {33,12,27,41,25}; 
    insertArr(&t,arrInsert,5,true);

    // 3.4
    int delArr[5] = {41,27,25,12,33};
    deleteArr(&t2,delArr,5,true);
}
