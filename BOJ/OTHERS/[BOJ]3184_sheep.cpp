#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N,M;
char map[252][252];
bool visited[252][252];

void input()
{
    cin>>N>>M;
    for(int r= 1 ; r<= N ; r++)
        {
            string line;
            cin>>line;
            for(int c= 1 ; c <=M ; c++)
                map[r][c] = line[c-1];    
        }
}

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

vector<int> sheep_wolf_cur;
void dfs(int r, int c)
{
    if(visited[r][c] || map[r][c] == '#') return;
    visited[r][c] = true;
    if(map[r][c] == 'v') sheep_wolf_cur[1]++;
    else if(map[r][c] =='o') sheep_wolf_cur[0]++;
    for(int d= 0 ;d <4 ;d++)
    {
        int ty = r+dy[d];
        int tx= c+dx[d];
        if(ty>=0&&ty<=N+2&& tx>=0 && tx<=M+2&&!visited[ty][tx] && map[ty][tx]!='#')
            dfs(ty,tx);
    }
}

void solve()
{
    vector<int> ans = {0,0};
    dfs(0,0);
    for(int r = 0 ; r < N+2; r++)
        for(int c= 0 ;c < M+2; c++)
        {
            sheep_wolf_cur={0,0};
            dfs(r,c);
            if(sheep_wolf_cur[0] > sheep_wolf_cur[1])
                ans[0] +=sheep_wolf_cur[0];
            else
                 ans[1]+=sheep_wolf_cur[1];
        }
    printf("%d %d",ans[0],ans[1]);
}

int main()
{
    input();
    solve();
}