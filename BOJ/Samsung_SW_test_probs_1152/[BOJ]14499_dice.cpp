#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int dice[4][3];
int map[20][20];

int N,M,y,x;

//Dummy, E W N S
int dy[5] = {0,0,0,-1,1};
int dx[5] = {0,1,-1,0,0};

void roll(int t)
{
    int my = y+dy[t];
    int mx = x+dx[t];
    if(mx<0 || mx>=M || my<0 || my>=N)
        return;
    
    if(map[my][mx] == 0)
            map[my][mx] = dice[1+dy[t]][1+dx[t]];
    else{
        dice[1+dy[t]][1+dx[t]] = map[my][mx];
        map[my][mx] = 0;
    }

    if(t<=2){
        int t1,t2,t3,t4;
        t1 = dice[1][0];
        t2 = dice[1][1];
        t3 = dice[1][2];
        t4 = dice[3][1];
        //E
        if(t==1){
            dice[1][0] = t2;
            dice[1][1] = t3;
            dice[1][2] = t4;
            dice[3][1] = t1;

        }
        //W
        else{
            dice[1][0] = t4;
            dice[1][1] = t1;
            dice[1][2] = t2;
            dice[3][1] = t3;
        }
    }
    else{
        int t1,t2,t3,t4;
        t1 = dice[0][1];
        t2 = dice[1][1];
        t3 = dice[2][1];
        t4 = dice[3][1];
        //N
        if(t==4){
            dice[0][1] = t2;
            dice[1][1] = t3;
            dice[2][1] = t4;
            dice[3][1] = t1;
        }
        //S
        else{
            dice[0][1] = t4;
            dice[1][1] = t1;
            dice[2][1] = t2;
            dice[3][1] = t3;    
        }
    }

    y = my;
    x = mx;
    cout<<dice[3][1]<<endl;


}

int main() {
    int K;
    cin>>N>>M>>y>>x>>K;

    for(int r = 0 ; r < N; r ++)
        for(int c = 0 ; c < M ; c++)
            cin>>map[r][c];
    
    int ti;
    for(int t = 0 ; t < K ; t++)
        {
            cin>>ti;
            roll(ti);
        }
        
}       