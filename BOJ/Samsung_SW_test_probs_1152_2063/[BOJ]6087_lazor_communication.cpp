#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int N,M;
bool map[100][100];
bool visited[4][100][100];
int  cur_min_mirror[4][100][100];

int dy[4] = {0,-1,0,1};
int dx[4] = {-1,0,1,0};


vector<vector<int>> target;

void input()
{
    cin>>M>>N;
    for(int r= 0 ; r < N ; r ++)
        {
            string line;
            cin>>line;
            for(int c= 0 ;c  < M ; c++)
            {
                if(line[c]=='C')
                {
                    target.push_back({r,c});
                    line[c] = '.';
                }
                if(line[c] == '*')
                    map[r][c] = true;
            }
        }
}

typedef struct info
{
    int y,x,len,cnt;
    int is_horizontal;
    int in_dir;
}info;
//is_horizontal : 0 : both (init) 1 : hor, -1 : vertical

void solve()
{
    queue<info> q;
    q.push({target[0][0],target[0][1],0,0,0,0});

    for(int d= 0 ; d <4;d++)
        visited[d][target[0][0]][target[0][1]] = true;

    int min_len = 1e9;
    int ans = 1e9;
    
    while(!q.empty())
    {
        // printf("========\n");        
        info pos = q.front();
        // cout<<pos.y<<" "<<pos.x<<" "<<pos.len<<" "<<pos.cnt<<" "<<pos.is_horizontal<<endl;

        q.pop();
        if(pos.y == target[1][0] && pos.x == target[1][1])
        {
            ans = min(ans,pos.cnt);
            min_len = pos.len;
        }

        if(cur_min_mirror[pos.in_dir][pos.y][pos.x] != pos.cnt)
            continue;

        // if(pos.len >min_len)
        //     break;
        for(int d = 0 ;d < 4; d++)
        {
            int ty = pos.y+dy[d];
            int tx = pos.x+dx[d];
            
            int mirror = (pos.is_horizontal>0 && d%2==1) ||(pos.is_horizontal<0 && d%2==0);
            if(ty>=0&& ty<N && tx>=0 && tx<M && !map[ty][tx] && (!visited[d][ty][tx] || visited[d][ty][tx] &&cur_min_mirror[d][ty][tx] > pos.cnt+mirror))
            {
                visited[d][ty][tx] = true;
                cur_min_mirror[d][ty][tx] = pos.cnt+mirror;
                //1) prev move hor but vertical this move
                //2) prev move vert but hor this move
                q.push({ty,tx,pos.len+1, pos.cnt+mirror, (d%2)?-1:1 ,d});
                // printf("%d : %d %d %d %d %d \n",d, ty,tx,pos.len+1,pos.cnt+mirror,(d%2)?-1:1  );

            }
        }
        // printf("========\n");

    }
    cout<<ans;
}

int main()
{
    input();
    solve();

    return 0;
}