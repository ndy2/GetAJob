#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <queue>

using namespace std;

int N = 12,M = 6;
char map[12][6];

void input()
{
    for(int r = N-1 ; r >=0 ; r--)
        {
            string line;
            cin>>line;
            for(int c= 0 ; c < M ; c++)
                map[r][c] = line[c];
        }
}

typedef struct cor{
    int y,x;
}cor;

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};
bool visited[12][6];

vector<cor> bfs(int r,int c, char t)
{
    queue<cor> q;
    vector<cor> out;
    q.push({r,c});
    visited[r][c] = true;
    while(!q.empty())
    {
        cor pos = q.front();
        q.pop();
        out.push_back(pos);
        for(int d= 0 ;d < 4; d ++)
        {
            int ty = pos.y + dy[d];
            int tx = pos.x + dx[d];
            if(ty>=0&& ty<N && tx>=0 && tx<M && !visited[ty][tx] &&map[ty][tx]==t)
                {
                    visited[ty][tx] = true;
                    q.push({ty,tx});
                }
        }
    }
    return out;
}

bool explosion()
{
    memset(visited,false,sizeof(visited));
    bool is_explode = false;
    for(int r = 0 ;r < N ; r++ )
        for(int c= 0 ; c < M ; c++)
            if(map[r][c]!='.' && !visited[r][c])
            {
                vector<cor> connected = bfs(r,c,map[r][c]);
                if(connected.size()>=4)
                {
                    is_explode = true;
                    for(auto p : connected)
                        map[p.y][p.x] = '.';
                }
            }
    return is_explode;
}

void drop()
{
    for(int col = 0 ; col < M; col++)
    {
        int drop_idx = 0;
        for( int move_idx = 0; move_idx<N ; move_idx++)
        {
            swap(map[drop_idx][col], map[move_idx][col]);
            if(map[drop_idx][col] !='.')
                drop_idx++;
        }
    }
}

void solve()
{
    int combo = 0;
    while(1)
    {
        if(!explosion())
            break;
        combo++;
        drop();
    }
    cout<<combo;
}

int main()
{
    input();
    solve();

    return 0;
}