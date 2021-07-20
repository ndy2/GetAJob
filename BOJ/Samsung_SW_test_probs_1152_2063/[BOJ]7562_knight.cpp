#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

int N;
vector<int> init(2,0);
vector<int> dest(2,0);

bool board[300][300] ;
bool visited[300][300] ;

int dy_knight[] = {-1,-2,-2,-1,1,2,2,1};
int dx_knight[] = {-2,-1,1,2,2,1,-1,-2};

void input()
{
    cin>>N>>init[0]>>init[1]>>dest[0]>>dest[1];
}

typedef struct info
{
    int y,x,cnt;
}info;

void solve()
{
    queue<info> q;
    q.push({init[0],init[1],0});
    visited[init[0]][init[1]] = true;
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();

        if(pos.y == dest[0] && pos.x == dest[1])
            {
                cout<<pos.cnt<<endl;
                return;
            }

        for(int d = 0 ; d < 8 ; d++)
        {
            int ty = pos.y+dy_knight[d];
            int tx = pos.x+dx_knight[d];

            if(ty>=0 && ty<N && tx>=0 && tx<N && !visited[ty][tx])
            {
                visited[ty][tx] = true;
                q.push({ty,tx,pos.cnt+1});
            }
            
        }
    }
}

void clean()
{
    memset(visited,0,sizeof(visited));
    init = {0,0};
    dest = {0,0};
}

int main()
{
    int tc;
    cin>>tc;
    for(int i = 1 ; i <=tc ; i++)
    {
        input();
        solve();
        clean();
    }
    
}