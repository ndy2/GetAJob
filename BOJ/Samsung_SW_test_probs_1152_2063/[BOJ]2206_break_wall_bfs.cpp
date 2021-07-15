#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N,M;
bool map[1000][1000];

void input()
{
    cin>>N>>M;
    string line;
    for(int r = 0 ; r < N ; r++)
    {
        cin>>line;
        for(int c= 0 ; c < M ; c++)
            map[r][c] = (line[c]-'0'); 
    }
}

int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

bool visited[2][1000][1000];
typedef struct info{
    int cnt,y,x;
    bool used;
}info;

void solve()
{
    int ans = -1;
    queue<info> q;
    q.push({1,0,0,0});
    visited[0][0][0] = true;

    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        // printf("%d %d %d %d \n", pos.cnt,pos.y,pos.x, pos.used);
        
        if(pos.y == N-1 && pos.x == M-1)
        {
            ans = pos.cnt;
            break;
        }
        for(int d= 0 ; d < 4; d++)
        {
            int ty = pos.y+dy[d];
            int tx = pos.x+dx[d];
            // printf("%d %d\n",ty,tx);
            if(ty>=0 && ty<N && tx>=0&& tx<M)
            {
                //already broke a wall
                if(pos.used == 1 && map[ty][tx] ==0 && !visited[1][ty][tx])
                {
                    visited[1][ty][tx] = 1;
                    q.push({pos.cnt+1, ty,tx, 1});
                }
                //keep its oppertunity
                else if(pos.used ==0 && map[ty][tx]==0&& !visited[0][ty][tx])
                {
                    visited[0][ty][tx] = true;
                    q.push({pos.cnt+1, ty,tx, 0});
                }
                //break wall at this move
                else if(pos.used ==0 && map[ty][tx]==1&& !visited[1][ty][tx])
                {
                    visited[1][ty][tx] = true;
                    q.push({pos.cnt+1, ty,tx, 1});
                }
            }
        }
    }
    cout<<ans;
}
int main()
{
    input();
    solve();

    return 0;
}