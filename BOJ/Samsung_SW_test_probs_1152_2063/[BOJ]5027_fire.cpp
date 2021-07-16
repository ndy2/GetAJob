#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int N,M;
bool map[1000][1000];
int fire_spread_time[1000][1000];
int sanguen_run_time[1000][1000];

bool visited[1000][1000];

vector<int> init;
vector<vector<int>> init_fires;

void input()
{
    cin>>M>>N;
    for(int r = 0 ;r < N ;r ++)
        {
            string line;
            cin>>line;
            for(int c= 0 ;c < M ; c++)
            {
                if(line[c] == '@')
                {
                    init = {r,c};
                    line[c] = '.';
                }
                else if(line[c] =='*')
                {
                    init_fires.push_back({r,c});
                    line[c] = '.';
                }
                if(line[c] =='.')
                    map[r][c] = 0;
                else
                    map[r][c] = 1;
            }
        }
}

int dy[4] = {0,0,-1,1};
int dx[4] = {1,-1,0,0};

typedef struct info
{
    int y,x,time;
}info;

void set_fires_map()
{
    queue<info> q;
    for(auto f : init_fires)
        {
            q.push({f[0],f[1],1});
            visited[f[0]][f[1]] = true;
        }
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        fire_spread_time[pos.y][pos.x] = pos.time;
        for(int d= 0 ; d < 4; d++)
        {
            int ty = pos.y+dy[d];
            int tx= pos.x+dx[d];
            if(ty>=0 && ty<N && tx>=0 && tx<M && !map[ty][tx]&&!visited[ty][tx])
                {
                    visited[ty][tx] = true;
                    q.push({ty,tx,pos.time+1});
                }
        }
    }

    memset(visited,0,sizeof(visited));
}


void set_sanguen_map()
{
    queue<info> q;
    
    q.push({init[0],init[1],0});
    visited[init[0]][init[1]] = true;
        
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        sanguen_run_time[pos.y][pos.x] = pos.time;
        for(int d= 0 ; d < 4; d++)
        {
            int ty = pos.y+dy[d];
            int tx= pos.x+dx[d];
            if(ty>=0 && ty<N && tx>=0 && tx<M && !map[ty][tx]&&!visited[ty][tx] && (fire_spread_time[ty][tx]==0 || fire_spread_time[ty][tx]-1>pos.time+1))
                {
                    visited[ty][tx] = true;
                    q.push({ty,tx,pos.time+1});
                }
        }
    }
    memset(visited,0,sizeof(visited));
}

void print_maps1()
{
    for(int r= 0 ;r < N ; r++)
    {
        for(int c= 0 ;c < M ; c++)
            cout<<fire_spread_time[r][c]<<" ";
        cout<<endl;
    }
    cout<<endl;

}

void print_maps2()
{
    for(int r= 0 ;r < N ; r++)
    {
        for(int c= 0 ;c < M ; c++)
            cout<<sanguen_run_time[r][c]<<" ";
        cout<<endl;
    }
    cout<<endl;

}

int get_ans()
{
    int ans = 1e9;
    for(int dist = 0 ; dist < M ; dist++)
        {
            if(!map[0][dist] &&  sanguen_run_time[0][dist]>0 &&(fire_spread_time[0][dist] ==0  || (fire_spread_time[0][dist] > sanguen_run_time[0][dist]+1)))
                ans = min(ans,sanguen_run_time[0][dist] +1);
            if(!map[N-1][M-dist-1] && sanguen_run_time[N-1][M-dist-1]>0 && (fire_spread_time[N-1][M-dist-1] ==0  || (fire_spread_time[N-1][M-dist-1] > sanguen_run_time[N-1][M-dist-1]+1)))
                ans = min(ans,sanguen_run_time[N-1][M-dist-1] +1);
            if(!map[dist][M-1] && sanguen_run_time[dist][M-1]>0 && (fire_spread_time[dist][M-1] ==0  || (fire_spread_time[dist][M-1] > sanguen_run_time[dist][M-1]+1)))
                ans = min(ans,sanguen_run_time[dist][M-1] +1);
            if(!map[N-dist-1][0] && sanguen_run_time[N-dist-1][0]>0 && (fire_spread_time[N-dist-1][0] ==0 || (fire_spread_time[N-dist-1][0] > sanguen_run_time[N-dist-1][0]+1)))
                ans = min(ans,sanguen_run_time[N-dist-1][0] +1);
        }
    return ans;
}

bool is_sanguen_edge()
{
    return (init[0] == 0 || init[0] ==N-1 || init[1] == 0 || init[1] == M-1);
}

void solve()
{
    if(is_sanguen_edge())
    {
        cout<<1<<endl;
        return;
    }

    set_fires_map();
    set_sanguen_map();
    // printf("fires\n");
    // print_maps1();
    
    // printf("sanguen\n");
    // print_maps2();
    int ans = get_ans();
    if(ans == 1e9)
        cout<<"IMPOSSIBLE"<<endl;
    else
        cout<<ans<<endl;
}

void clean()
{
    memset(visited,0,sizeof(visited));
    memset(map,0,sizeof(map));
    memset(fire_spread_time,0,sizeof(fire_spread_time));
    memset(sanguen_run_time,0,sizeof(sanguen_run_time));
    init.clear();
    init_fires.clear();
}

int main()
{
    int TC;
    cin>>TC;
    for(int i = 1 ; i <= TC ; i++)
    {     
        input();
        solve();
        clean();
    }

    return 0;
}