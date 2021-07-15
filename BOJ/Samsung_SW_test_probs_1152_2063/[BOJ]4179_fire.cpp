#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int N,M;
char map[1000][1000];
bool visited[1000][1000];

vector<vector<int>> map_jihun(1000,vector<int>(1000,0));
vector<vector<int>> map_fire(1000,vector<int>(1000,0));

vector<int> init_jihun;
vector<vector<int>> init_fire;

void input()
{
    cin>>N>>M;
    for(int r= 0 ; r <N ; r++)
        {
            string line;
            cin>>line;
            for(int c= 0 ;c < M; c++)
                {
                    map[r][c] = line[c];
                    if(map[r][c] == 'J')
                        init_jihun = {r,c};
                    else if(map[r][c] == 'F')
                        init_fire.push_back({r,c});
                }
        }
}


typedef struct info{
    vector<int> cor;
    int cnt;
}info;

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

void set_maps(vector<vector<int>> &board, vector<vector<int>> pos, bool is_jihun)
{
    queue<info> q;
    for(auto p : pos)
    {
        q.push({{p[0],p[1]},1});
        visited[p[0]][p[1]] = true;
    }
        
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        int r = pos.cor[0];
        int c = pos.cor[1];
        int cnt = pos.cnt;
        board[r][c] = cnt;
        for(int d = 0 ; d < 4; d++)
            {
                int ty = r + dy[d];
                int tx = c + dx[d];

                if(ty>=0&&ty<N && tx>=0 &&tx<M &&!visited[ty][tx] && map[ty][tx]!='#')
                    {
                        if(is_jihun && map_fire[ty][tx] <=cnt+1 && map_fire[ty][tx]!=0)
                            continue;
                        visited[ty][tx] = true;
                        q.push({{ty,tx},cnt+1});
                    }
            }
    }
    memset(visited, 0,sizeof(visited));
}

int get_ans(vector<vector<int>> j , vector<vector<int>> f)
{
    int ans = 1e9;
    for(int dist = 0 ; dist < M; dist++)
        {
            //TOP
            if(j[0][dist]>0 &&(j[0][dist] < f[0][dist]||f[0][dist]==0))
                ans = min(ans, j[0][dist]);
            //BOTTOM
            if(j[N-1][M-dist-1]>0 &&( j[N-1][M-dist-1] < f[N-1][M-dist-1]||f[N-1][M-dist-1]==0))
                ans = min(ans, j[N-1][M-dist-1]);
        }
    for(int dist = 0 ; dist < N; dist++)
        {
            //RIGHT
            if(j[dist][M-1]>0 &&( j[dist][M-1] < f[dist][M-1]||f[dist][M-1] == 0))
                ans = min(ans, j[dist][M-1]);
            //LEFT
            if(j[N-dist-1][0]>0 &&( j[N-dist-1][0] < f[N-dist-1][0] || f[N-dist-1][0] ==0))
                ans = min(ans, j[N-dist-1][0]);
        }
    return ans;
}

void print_vvi(vector<vector<int>> vvi)
{
    for(int r = 0 ; r < N ; r++)
        {
            for(int c = 0; c < M ; c++)
                cout<<vvi[r][c]<<" ";
            cout<<endl;
        }
    cout<<endl;
}

void solve()
{
    set_maps(map_fire, init_fire , false);
    set_maps(map_jihun, {init_jihun}, true);
    // print_vvi(map_fire);
    // print_vvi(map_jihun);
    
    int ans = get_ans(map_jihun, map_fire);
    if(ans!=1e9)
        cout<<ans;
    else
        cout<<"IMPOSSIBLE";
}

int main()
{
    input();
    solve();
}