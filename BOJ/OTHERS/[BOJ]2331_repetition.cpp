#include <iostream>
#include <cmath>

using namespace std;

int getNextA(int A, int P){
    int nextA = 0;
    string aString = to_string(A);
    for(char c : aString){
        int i = c-'0';
        nextA += pow(i,P);
    }
    return nextA;
}

int logging[1000000];

int main(){
    int A,P;
    cin>>A>>P;
    logging[A] = 1;

    while(1){
        int nextA = getNextA(A, P);
        // printf("nextA : %d\n", nextA);
        int prevLog = logging[A];
        int v = logging[nextA];
        if(v!= 0){
            printf("%d", v-1);
            break;
        }
        else{
            logging[nextA] = prevLog+1;
            A = nextA;
        }
    }

}