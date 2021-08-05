#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int N,M;
char map[50][50];
int map_fire[50][50];
bool visited[50][50];

vector<int> from, dest;

typedef struct info
{
    int y,x,t;
}info;

queue<info> q;

void input()
{
    cin>>N>>M;
    for(int r= 0 ;r < N ; r++)
    {
        string line;
        cin>>line;
        for(int c= 0 ;c < M ; c++)
            {
                if(line[c] == 'S')
                   {    
                        from = {r,c};
                        map[r][c] = 'S';
                   } 
                else if(line[c] =='D')
                    {
                        dest={r,c};
                        map[r][c] = 'D';
                    }
                else if(line[c] == '*')
                    {
                        visited[r][c] = true;
                        q.push({r,c,0});
                        map[r][c] = line[c];
                    }   
                else 
                    map[r][c] = line[c];

            }
    }
}

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

void set_map_fire()
{
    for(int r= 0 ;r < N ; r++)
        for(int c= 0 ;c < M ; c++)
            map_fire[r][c] = 987654321;

    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        // printf("%d %d %d\n",pos.y,pos.x,pos.t);
        map_fire[pos.y][pos.x] = pos.t;        
        for(int d= 0 ;d <4 ;d++)
        {
            int ty = pos.y+dy[d];
            int tx = pos.x+dx[d];
            if(ty>=0&&ty<N && tx>=0 &&tx<M && !visited[ty][tx] && map[ty][tx]!='X' && map[ty][tx]!='D')
                {
                    visited[ty][tx] = true;
                    q.push({ty,tx,pos.t+1});
                }
        }
    }
}

void print_fire_map()
{
    printf("fire_map\n");
    for(int r= 0 ;r < N ; r++)
    {
        for(int c= 0; c< M ; c++)
            if(map[r][c]=='X')
                printf("X ");
            else
                printf("%d ",map_fire[r][c]);
        printf("\n");
    }
    printf("\n\n");
}



void solve()
{
    int ans = 987654321;
    
    set_map_fire();
    // print_fire_map();
    memset(visited,0,sizeof(visited));

    visited[from[0]][from[1]] = true;
    q.push({from[0],from[1],0});
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        // printf("%d %d %d\n",pos.y,pos.x,pos.t);

        if(pos.y==dest[0] && pos.x==dest[1])
            {
                ans = pos.t;
                break;
            }   
        for(int d= 0 ;d <4 ;d++)
        {
            int ty = pos.y+dy[d];
            int tx= pos.x+dx[d];
            if(ty>=0&&ty<N && tx>=0 &&tx<M && !visited[ty][tx] && map[ty][tx]!='X' && map_fire[ty][tx] >pos.t+1)
                {   
                    visited[ty][tx] = true;
                    q.push({ty,tx,pos.t+1});
                }
        }
    }
    if(ans !=987654321)
        printf("%d",ans);
    else
        printf("KAKTUS");
}

int main()
{
    input();
    solve();
}