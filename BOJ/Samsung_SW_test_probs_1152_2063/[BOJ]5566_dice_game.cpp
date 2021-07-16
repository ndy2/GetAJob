#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int N,M;
int board[1001];
int play[1001];
void input()
{
    cin>>N>>M;
    for(int i = 1; i <=N ; i++)
        cin>>board[i];
    for(int i = 1; i<=M ; i++)
        cin>>play[i];
}



void solve()
{
    int turn =0;
    int cur_pos = 1;
    while(1)
    {
        if(cur_pos >= N)
            break;
        turn++;
        // printf("@ turn %d \n",turn);
        // printf("dice out : %d\n" , play[turn]);

        cur_pos+=play[turn];
        // printf("board out : %d\n" , board[cur_pos]);
        cur_pos += board[cur_pos];
        // printf("resulted pos : %d\n\n\n" ,cur_pos);
    }
    cout<<turn;
}

int main()
{
    input();
    solve();

    return 0;
}