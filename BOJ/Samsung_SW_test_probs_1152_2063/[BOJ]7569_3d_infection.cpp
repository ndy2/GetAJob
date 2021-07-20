#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

int N,M,H;
bool is_wall[100][100][100];
bool is_init[100][100][100];
bool is_tomato_now[100][100][100];

bool visited[100][100][100];

int dz[6] = {0,0,0,0,1,-1};
int dy[6] = {0,0,1,-1,0,0};
int dx[6] = {1,-1,0,0,0,0};


void input()
{
    int pos;
    cin>>M>>N>>H;
    for(int h = 0 ; h <H ; h++)
        for(int r = 0 ; r < N ; r++)
            for(int c= 0 ;c < M ; c++)
                {
                    cin>>pos;
                    if(pos == -1)
                        is_wall[h][r][c] = true;
                    else if(pos ==1)
                        is_init[h][r][c] = true;
                }
}

typedef struct info{
    int z,y,x,days;
}info;

bool is_done()
{
    for(int h = 0 ; h <H ; h++)
        for(int r = 0 ; r < N ; r++)
            for(int c= 0 ;c < M ; c++)
                //has tomato but it is reddish
                if(!is_wall[h][r][c] && !is_tomato_now[h][r][c])
                    return false;
    return true;
}

void solve()
{
    queue<info> q;
    for(int h = 0 ; h <H ; h++)
        for(int r = 0 ; r < N ; r++)
            for(int c= 0 ;c < M ; c++)
                if(is_init[h][r][c])
                {
                    visited[h][r][c] = true;
                    q.push({h,r,c,0});
                }
    
    int ans = -1;
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        is_tomato_now[pos.z][pos.y][pos.x] = true;
        if(is_done())
        {
            ans = pos.days;
            break;
        }
        for(int d= 0 ;d < 6; d++)
        {
            int tz = pos.z + dz[d];
            int ty = pos.y + dy[d];
            int tx = pos.x + dx[d];
            if(tz>=0 && tz<H && ty >=0 && ty<N && tx >=0 && tx<M && !is_wall[tz][ty][tx] && !visited[tz][ty][tx])
            {
                visited[tz][ty][tx] = true;
                q.push({tz,ty,tx,pos.days+1});
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