#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

int in;
int target;
int visited[10000];



void input(){
    memset(visited,false,sizeof(visited));
    cin>>in;
    cin>>target;
}

typedef struct _info{
    int cur;
    string log;
}info;

info opDouble(info in){
    return {2*in.cur%10000, in.log+"D"};
}

info opSubtract(info in){
    return {(in.cur+9999)%10000, in.log+"S"};
}


info opLeftShift(info in){
    int inValue = in.cur;

    int in3 = inValue/1000;
    inValue -= in3 * 1000;

    int in2 = inValue/100;
    inValue -= in2 * 100;
    
    int in1 = inValue/10;
    inValue -= in1 * 10;

    int in0 = inValue;

    return {1000*in2 + 100*in1 + 10*in0 + in3,in.log+"L"};
}

info opRightShift(info in){
    int inValue = in.cur;

    int in3 = inValue/1000;
    inValue -= in3 * 1000;

    int in2 = inValue/100;
    inValue -= in2 * 100;
    
    int in1 = inValue/10;
    inValue -= in1 * 10;

    int in0 = inValue;

    return {1000*in0 + 100*in3 + 10*in2 + in1, in.log+"L"};
}

void solve(){
    queue<info> q;
    q.push({in,""});

    while(!q.empty()){
        info pos = q.front();
        q.pop();
        
        if (pos.cur == target){
            cout<<pos.log<<endl;
            break;
        }

        info D = opDouble(pos);
        info S = opSubtract(pos);
        info L = opLeftShift(pos);
        info R = opRightShift(pos);
        if(!visited[D.cur]) {visited[D.cur]=true ; q.push(D);}
        if(!visited[S.cur]) {visited[S.cur]=true ; q.push(S);}
        if(!visited[L.cur]) {visited[L.cur]=true ; q.push(L);}
        if(!visited[R.cur]) {visited[R.cur]=true ; q.push(R);}
    }
}

int main()
{
   int tc;
   cin>>tc;
   for(int t= 0 ; t < tc; t++){
       input();
       solve();
   }

}