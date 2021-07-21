#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

int N,M;
int map[1000][1000];
vector<int> robot(2,0);
int dy[4]={0,0,0,0};
int dx[4]={0,0,0,0};
int d = 0;
void input()
{
    cin>>N>>M;
    int k;
    cin>>k;
    int br,bc;
    for(int i = 1; i <=k ; i++)
    {
        cin>>br>>bc;
        map[br][bc] = -1;
    }
    cin>>robot[0]>>robot[1];
    int dir;
    int dy_d[5] = {0,-1,1,0,0};
    int dx_d[5] = {0,0,0,-1,1};
    for(int i = 0 ; i < 4; i++)
    {
        cin>>dir;
        dy[i] = dy_d[dir];
        dx[i] = dx_d[dir];
    }
}



//cor, d, visited
bool move()
{
    int search_cnt = 0;
    while(1)
    {   
        if(search_cnt == 4)
           return false;
    
            
        search_cnt ++;
        int ty = robot[0] + dy[d];
        int tx = robot[1] + dx[d];
        if(ty<0 || ty>=N || tx<0 || tx>=M || map[ty][tx] != 0) 
            {
                d = (d+1)%4;
                continue;
            }
        robot[0] = ty;
        robot[1] = tx;
        return true;
    }
}

void solve()
{
    while(1)
    {
        map[robot[0]][robot[1]] = 1;
        if(!move())
            break;
    }

    cout<<robot[0]<<" "<<robot[1];
}

int main()
{
    input();
    solve();

    return 0;
}