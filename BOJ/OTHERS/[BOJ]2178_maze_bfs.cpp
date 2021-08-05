#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int N,M;
bool map[101][101];
bool visited[101][101];

void input()
{
    cin>>N>>M;
    for(int r= 1 ; r <= N ; r++)
    {
        string line;
        cin>>line;
        for(int c= 1 ; c <=M ; c++)
            map[r][c] = line[c-1]=='1';
    }
}

typedef struct info{
    int y,x,len;
}info;

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

void solve()
{
    queue<info> q;
    visited[1][1] = true;
    q.push({1,1,1});
    int ans;
    while(!q.empty())
    {
        info pos =q.front();
        q.pop();

        if(pos.y==N && pos.x ==M)
        {
            ans = pos.len;
            break;
        }
        for(int d= 0 ; d<4 ; d++)
        {
            int ty = pos.y+dy[d];
            int tx = pos.x+dx[d];

            if(ty>=1 && ty<=N && tx>=1 && tx<=M && map[ty][tx] && !visited[ty][tx])
            {
                visited[ty][tx] =true;
                q.push({ty,tx,pos.len+1});
            }
        }
    }

    cout<<ans;
}



int main()
{
    input();
    solve();
}