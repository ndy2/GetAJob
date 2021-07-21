#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

int N,M,K;
bool map[1000][1000];
bool visited[1000][1000];

void input()
{
    cin>>N>>M>>K;
    for(int r= 0 ; r < N ; r ++)
        {
            string line;
            cin>>line;
            for(int c = 0 ; c <=M ; c++)
                map[r][c] = line[c]-'0';
        }
}


int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};
bool found;
int ans = 1e9;

int l1_dist(int x0,int y0,int x1, int y1)
{
    return abs(x0-x1) + abs(y0-y1);
}

void dfs(int r, int c, int remain , int dist)
{
    if(visited[r][c])
        return;
    if(found && ans - dist <=l1_dist(r,c,N-1,M-1))
        return;
    // printf("row : %d col : %d remain : %d, dist : %d\n",r,c,remain,dist);
    if(r==N-1 && c == M-1){
        found = true;
        ans = min(ans ,dist);
        return;
    }
    visited[r][c] = true;
    for(int d= 0 ; d < 4; d++)
    {
        int ty = r+dy[d];
        int tx = c+dx[d];
        if(ty>=0 && ty<N && tx>=0 && tx<M && !visited[ty][tx])
        {
            //map[ty][tx] : wall -> if remain>0 go through
            if(map[ty][tx] && remain>0)
            {
                dfs(ty,tx,remain-1,dist+1);
                visited[ty][tx] = false;
            }

            //map[ty][tx] : not wall -> go throught
            else if(!map[ty][tx])
            {
                dfs(ty,tx, remain, dist+1);
                visited[ty][tx] = false;
            }
                
        }
    }
}

void solve()
{
    dfs(0,0,K,1);
    if(ans ==1e9)
        printf("-1");
    else
        printf("%d",ans);
}

int main()
{
    input();
    solve();

    return 0;
}