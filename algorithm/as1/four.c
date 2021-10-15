#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int addCnt;
int mulCnt;
int subCnt;

void initRandIntMatrix(int *** mat, int d){
    int ** A = (int**)malloc(sizeof(int*)*d);
    for(int r = 0 ; r < d ; r++){
        A[r] = (int*)malloc(sizeof(int)*d);
        for(int c = 0 ; c < d ; c++)
            A[r][c] = rand()%1000;
    }
    *mat = A;
}

void printTwoMatrix(int ** A, int **B, int d)
{
    for(int r = 0 ; r < d; r++){
        for(int c = 0 ; c < d; c++)
            printf("%5d",A[r][c]);
        printf("     ");
        for(int c = 0 ; c < d; c++)
            printf("%5d",B[r][c]);
        printf("\n");
    }
    printf("\n");
}

void printOneMatrix(int ** C, int d)
{
    for(int r = 0 ; r < d; r++){
        for(int c = 0 ; c < d; c++)
            printf("%15d",C[r][c]);
        printf("\n");
    }
    printf("\n");
}


void matMulStandard(int **A, int **B, int ***C, int d){
    int ** out = (int**)malloc(sizeof(int*)*d);

    for(int i = 0 ; i < d ; i++ )
    {
        out[i] = (int*)malloc(sizeof(int)*d);
        for(int j = 0 ; j < d; j++)
            {
                int sum = 0;
                for(int k = 0 ; k < d; k++)
                    {
                        int mul = A[i][k] * B[k][j];
                        sum += mul;
                    }
                out[i][j] = sum;
                addCnt += d-1;
                mulCnt += d;
            }
    }
    *C = out;
}

void initEmptyMat(int ***A, int d){
    int ** out = (int**)malloc(sizeof(int*)*d);
    for(int i = 0 ; i < d ; i++ )
        out[i] =  (int*)malloc(sizeof(int)*d);
    *A = out;
}

void matSum(int ** A, int ** B, int ***C,int d){
    int ** out = (int**)malloc(sizeof(int*)*d);
    for(int r = 0 ; r < d;  r++){
        out[r] = (int*)malloc(sizeof(int)*d);
        for(int c = 0 ;c < d; c++){
            out[r][c] = A[r][c] + B[r][c];
            addCnt+=1;
        }
            
    }
    *C = out;
}

void matSub(int ** A, int ** B, int ***C,int d){
    int ** out = (int**)malloc(sizeof(int*)*d);
    for(int r = 0 ; r < d;  r++){
        out[r] = (int*)malloc(sizeof(int)*d);
        for(int c = 0 ;c < d; c++){
            out[r][c] = A[r][c] - B[r][c];
            subCnt+=1;
        }
            
    }
    *C = out;
}

void matSum3Sub1(int ** A0, int ** A1, int **A2, int **B, int ***C,int d){
    int ** out = (int**)malloc(sizeof(int*)*d);
    for(int r = 0 ; r < d;  r++){
        out[r] = (int*)malloc(sizeof(int)*d);
        for(int c = 0 ;c < d; c++){
            out[r][c] = A0[r][c] +  A1[r][c] +  A2[r][c] - B[r][c];
            addCnt+=2;
            subCnt+=1;
        }
    }
    *C = out;
}


void matMulDevideAndConquer(int **A, int **B, int ***C, int d, int printPartial){
    int dd = d/2;
    if(d==1){
        int ** out = (int**)malloc(sizeof(int*));
        out[0] = (int*)malloc(sizeof(int));
        out[0][0] = A[0][0] * B[0][0];
        mulCnt+=1;
        *C = out;
    }
    else{
        int ** A00, ** A01;
        int ** A10, ** A11;
        
        int ** B00, ** B01;
        int ** B10, ** B11;

       initEmptyMat(&A00,dd);
       initEmptyMat(&A01,dd);
       initEmptyMat(&A10,dd);
       initEmptyMat(&A11,dd);
        for(int r = 0 ;r < dd ; r++)
            for(int c = 0 ; c < dd ; c++)
                A00[r][c] = A[r][c];
        
        for(int r = 0 ;r < dd ; r++)
            for(int c = dd ; c < d ; c++)
                A01[r][c-dd] = A[r][c];

        for(int r = dd ;r < d ; r++)
            for(int c = 0 ; c < dd ; c++)
                A10[r-dd][c] = A[r][c];
        
        for(int r = dd ;r < d ; r++)
            for(int c = dd ; c < d ; c++)
                A11[r-dd][c-dd] = A[r][c];

       initEmptyMat(&B00,dd);
       initEmptyMat(&B01,dd);
       initEmptyMat(&B10,dd);
       initEmptyMat(&B11,dd);
       
        for(int r = 0 ;r < dd ; r++)
            for(int c = 0 ; c < dd ; c++)
                B00[r][c] = B[r][c];
        
        for(int r = 0 ;r < dd ; r++)
            for(int c = dd ; c < d ; c++)
                B01[r][c-dd] = B[r][c];

        for(int r = dd ;r < d ; r++)
            for(int c = 0 ; c < dd ; c++)
                B10[r-dd][c] = B[r][c];
        
        for(int r = dd ;r < d ; r++)
            for(int c = dd ; c < d ; c++)
                B11[r-dd][c-dd] = B[r][c];

        int ** C00_a, ** C00_b, ** C00;
        int ** C01_a, ** C01_b, ** C01;
        int ** C10_a, ** C10_b, ** C10;
        int ** C11_a, ** C11_b, ** C11;
        
        initEmptyMat(&C00_a,dd);
        initEmptyMat(&C00_b,dd);
        initEmptyMat(&C00,dd);

        initEmptyMat(&C00_a,dd);
        initEmptyMat(&C01_b,dd);
        initEmptyMat(&C01,dd);

        initEmptyMat(&C10_a,dd);
        initEmptyMat(&C10_b,dd);
        initEmptyMat(&C10,dd);

        initEmptyMat(&C11_a,dd);
        initEmptyMat(&C11_b,dd);
        initEmptyMat(&C11,dd);

        matMulDevideAndConquer(A00,B00,&C00_a,dd,printPartial);
        matMulDevideAndConquer(A01,B10,&C00_b,dd,printPartial);
        matSum(C00_a, C00_b, &C00,dd);

        matMulDevideAndConquer(A00,B01,&C01_a,dd,printPartial);
        matMulDevideAndConquer(A01,B11,&C01_b,dd,printPartial);
        matSum(C01_a, C01_b, &C01,dd);

        matMulDevideAndConquer(A10,B00,&C10_a,dd,printPartial);
        matMulDevideAndConquer(A11,B10,&C10_b,dd,printPartial);
        matSum(C10_a, C10_b, &C10,dd);

        matMulDevideAndConquer(A10,B01,&C11_a,dd,printPartial);
        matMulDevideAndConquer(A11,B11,&C11_b,dd,printPartial);
        matSum(C11_a, C11_b, &C11,dd);

        int ** out;
        initEmptyMat(&out,d);

        for(int r = 0 ;r < dd ; r++)
            for(int c = 0 ; c < dd ; c++)
                out[r][c] = C00[r][c];
        
        for(int r = 0 ;r < dd ; r++)
            for(int c = dd ; c < d ; c++)
                out[r][c] = C01[r][c-dd];

        for(int r = dd ;r < d ; r++)
            for(int c = 0 ; c < dd ; c++)
                out[r][c] = C10[r-dd][c];
        
        for(int r = dd ;r < d ; r++)
            for(int c = dd ; c < d ; c++)
                out[r][c] = C11[r-dd][c-dd];
        
        if(printPartial) printOneMatrix(out,d);
        *C = out;
    } 
}

void matMulStrassen(int **A, int **B, int ***C, int d, int printPartial){
    int dd = d/2;
    if(d==1){
        int ** out = (int**)malloc(sizeof(int*));
        out[0] = (int*)malloc(sizeof(int));
        out[0][0] = A[0][0] * B[0][0];
        mulCnt+=1;
        *C = out;
    }
    else{
        int ** A00, ** A01;
        int ** A10, ** A11;
        
        int ** B00, ** B01;
        int ** B10, ** B11;

       initEmptyMat(&A00,dd);
       initEmptyMat(&A01,dd);
       initEmptyMat(&A10,dd);
       initEmptyMat(&A11,dd);
        for(int r = 0 ;r < dd ; r++)
            for(int c = 0 ; c < dd ; c++)
                A00[r][c] = A[r][c];
        
        for(int r = 0 ;r < dd ; r++)
            for(int c = dd ; c < d ; c++)
                A01[r][c-dd] = A[r][c];

        for(int r = dd ;r < d ; r++)
            for(int c = 0 ; c < dd ; c++)
                A10[r-dd][c] = A[r][c];
        
        for(int r = dd ;r < d ; r++)
            for(int c = dd ; c < d ; c++)
                A11[r-dd][c-dd] = A[r][c];

       initEmptyMat(&B00,dd);
       initEmptyMat(&B01,dd);
       initEmptyMat(&B10,dd);
       initEmptyMat(&B11,dd);
       
        for(int r = 0 ;r < dd ; r++)
            for(int c = 0 ; c < dd ; c++)
                B00[r][c] = B[r][c];
        
        for(int r = 0 ;r < dd ; r++)
            for(int c = dd ; c < d ; c++)
                B01[r][c-dd] = B[r][c];

        for(int r = dd ;r < d ; r++)
            for(int c = 0 ; c < dd ; c++)
                B10[r-dd][c] = B[r][c];
        
        for(int r = dd ;r < d ; r++)
            for(int c = dd ; c < d ; c++)
                B11[r-dd][c-dd] = B[r][c];

        int ** M1, ** M2, ** M3, ** M4, ** M5, ** M6, ** M7;
        int ** M1_a, **M1_b, **M2_a, **M3_b, **M4_b, **M5_a,**M6_a,**M6_b,**M7_a, **M7_b;

        
        int ** C00, **C01, **C10, **C11;
        
        initEmptyMat(&M1,dd);
        initEmptyMat(&M1_a,dd);
        initEmptyMat(&M1_b,dd);
        matSum(A00,A11,&M1_a,dd);
        matSum(B00,B11,&M1_b,dd);

        initEmptyMat(&M2,dd);
        initEmptyMat(&M2_a,dd);
        matSum(A10,A11,&M2_a,dd);

        initEmptyMat(&M3,dd);
        initEmptyMat(&M3_b,dd);
        matSub(B01,B11,&M3_b,dd);

        initEmptyMat(&M4,dd);
        initEmptyMat(&M4_b,dd);
        matSub(B10,B00,&M4_b,dd);

        initEmptyMat(&M5,dd);
        initEmptyMat(&M5_a,dd);
        matSum(A00,A01,&M5_a,dd);

        initEmptyMat(&M6,dd);
        initEmptyMat(&M6_a,dd);
        initEmptyMat(&M6_b,dd);
        matSub(A10,A00,&M6_a,dd);
        matSum(B00,B01,&M6_b,dd);

        initEmptyMat(&M7,dd);
        initEmptyMat(&M7_a,dd);
        initEmptyMat(&M7_b,dd);
        matSub(A01,A11,&M7_a,dd);
        matSum(B10,B11,&M7_b,dd);

        matMulStrassen(M1_a,M1_b,&M1,dd,printPartial);
        matMulStrassen(M2_a,B00,&M2,dd,printPartial);
        matMulStrassen(A00,M3_b,&M3,dd,printPartial);
        matMulStrassen(A11,M4_b,&M4,dd,printPartial);
        matMulStrassen(M5_a,B11,&M5,dd,printPartial);
        matMulStrassen(M6_a,M6_b,&M6,dd,printPartial);
        matMulStrassen(M7_a,M7_b,&M7,dd,printPartial);


        initEmptyMat(&C00,dd);
        initEmptyMat(&C01,dd);
        initEmptyMat(&C10,dd);
        initEmptyMat(&C11,dd);

        matSum3Sub1(M1,M4,M7,M5,&C00,dd);
        matSum(M3,M5,&C01,dd);
        matSum(M2,M4,&C10,dd);
        matSum3Sub1(M1,M3,M6,M2,&C11,dd);

        int ** out;
        initEmptyMat(&out,d);

        for(int r = 0 ;r < dd ; r++)
            for(int c = 0 ; c < dd ; c++)
                out[r][c] = C00[r][c];
        
        for(int r = 0 ;r < dd ; r++)
            for(int c = dd ; c < d ; c++)
                out[r][c] = C01[r][c-dd];

        for(int r = dd ;r < d ; r++)
            for(int c = 0 ; c < dd ; c++)
                out[r][c] = C10[r-dd][c];
        
        for(int r = dd ;r < d ; r++)
            for(int c = dd ; c < d ; c++)
                out[r][c] = C11[r-dd][c-dd];
        
        if(printPartial) printOneMatrix(out,d);
        *C = out;
    }

}

int main()
{
    srand(time(NULL));
    int ** A,**B,**C;
    int d = 8;
    initRandIntMatrix(&A,d);
    initRandIntMatrix(&B,d);
    printTwoMatrix(A,B,d);
    printf("Standard Algorithm AxB\n");
    addCnt = 0;
    mulCnt = 0;
    matMulStandard(A,B,&C,d);
    printOneMatrix(C,d);
    memset(C,0,sizeof(C));
    printf("add Cnt : %d      mul Cnt : %d\n\n",addCnt,mulCnt);
    
    printf("==========================\n");
    printf("Devide And Conquer AxB\n");
    addCnt = 0;
    mulCnt = 0;
    matMulDevideAndConquer(A,B,&C,d,1);
    printOneMatrix(C,d);
    memset(C,0,sizeof(C));
    printf("add Cnt : %d      mul Cnt : %d\n\n",addCnt,mulCnt);

    printf("==========================\n");
    printf("Strassen Algorithm AxB\n");
    addCnt = 0;
    mulCnt = 0;
    subCnt = 0;
    matMulStrassen(A,B,&C,d,1);
    printOneMatrix(C,d);
    memset(C,0,sizeof(C));
    printf("add Cnt : %d      mul Cnt : %d      sub Cnt : %d\n\n",addCnt,mulCnt,subCnt);

    return 0;
}