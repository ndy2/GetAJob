#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

int N,M,H;
bool is_wall[1000][1000];
bool is_init[1000][1000];
bool is_tomato_now[1000][1000];

bool visited[1000][1000];

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};


void input()
{
    int pos;
    cin>>M>>N;
    for(int r = 0 ; r < N ; r++)
        for(int c= 0 ;c < M ; c++)
            {
                cin>>pos;
                if(pos == -1)
                    is_wall[r][c] = true;
                else if(pos ==1)
                    is_init[r][c] = true;
            }
}

typedef struct info{
    int y,x,days;
}info;

bool is_done()
{
    for(int r = 0 ; r < N ; r++)
        for(int c= 0 ;c < M ; c++)
            //has tomato but it is reddish
            if(!is_wall[r][c] && !is_tomato_now[r][c])
                return false;
    return true;
}

void solve()
{
    queue<info> q;
    for(int r = 0 ; r < N ; r++)
        for(int c= 0 ;c < M ; c++)
            if(is_init[r][c])
            {
                visited[r][c] = true;
                q.push({r,c,0});
            }
    
    int ans = -1;
    int cur_days = -1;
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        is_tomato_now[pos.y][pos.x] = true;
        if((pos.days - cur_days == 1 || q.empty()) && is_done())
        {
            ans = pos.days;
            break;
        }
        cur_days = pos.days;
        for(int d= 0 ;d < 4; d++)
        {
            int ty = pos.y + dy[d];
            int tx = pos.x + dx[d];
            if(ty >=0 && ty<N && tx >=0 && tx<M && !is_wall[ty][tx] && !visited[ty][tx])
            {
                visited[ty][tx] = true;
                q.push({ty,tx,pos.days+1});
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