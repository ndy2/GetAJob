#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <queue>

using namespace std;

int N,M,K;
bool map[1000][1000];
bool visited[1000][1000][11];

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

typedef struct info{
    int y,x,remain,dist;
}info;

void solve()
{
    queue<info> q;
    q.push({0,0,K,1});
    visited[0][0][K] = true;
    int ans = -1;
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        if(pos.y == N-1 && pos.x ==M-1){
            ans = pos.dist;
            break;
        }
            
        // printf("row : %d col : %d remain : %d, dist : %d\n",pos.y,pos.x,pos.remain,pos.dist);

        for(int d= 0 ; d < 4; d++)
        {
            int ty = pos.y+dy[d];
            int tx = pos.x+dx[d];
            if(ty>=0&&ty<N && tx>=0 && tx<M && !visited[ty][tx][pos.remain])
            {
                //map[ty][tx] : wall -> if remain>0 go through
                if(map[ty][tx] && pos.remain>0)
                {
                    visited[ty][tx][pos.remain-1] = true;
                    // printf("pushed :  row : %d col : %d remain : %d, dist : %d\n",ty,tx,pos.remain-1,pos.dist+1);
                    q.push({ty,tx,pos.remain-1,pos.dist+1});
                }

                //map[ty][tx] : not wall -> go throught
                else if(!map[ty][tx])
                {
                    visited[ty][tx][pos.remain] = true;
                    // printf("pushed :  row : %d col : %d remain : %d, dist : %d\n",ty,tx,pos.remain,pos.dist+1);
                    q.push({ty,tx, pos.remain, pos.dist+1});                    
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