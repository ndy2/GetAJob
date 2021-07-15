#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int N,M;
int map[300][300];
int reduce_map[300][300];
bool visited[300][300];

void input()
{
    cin>>N>>M;
    for(int r= 0 ;r < N ; r++)
        for(int c= 0 ;c < M ; c++)
            cin>>map[r][c];
}

bool check_done()
{
    for(int r= 0 ;r < N ; r++)
        for(int c= 0 ;c < M ; c++)
            if(map[r][c] !=0)
                return false;
    return true;
}

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

void set_reduce_map()
{
    for(int r= 0; r<N; r++)
        for(int c= 0 ;c < M ;c++)
            if(map[r][c]>0)
            {
                int reduction_amount =0;
                for(int d = 0 ; d<4; d++)
                    {
                        int ty = r+dy[d];
                        int tx = c+dx[d];
                        if(ty>=0 && ty<N && tx>=0 && tx<M && map[ty][tx]==0)
                            reduction_amount++;
                    }
                reduce_map[r][c] = reduction_amount;
            }
}

void reduction()
{
    for(int r= 0; r<N; r++)
        for(int c= 0 ;c < M ;c++)
            if(map[r][c]>0)
                map[r][c] = max(0, map[r][c]- reduce_map[r][c]);
}

bool dfs(int r, int c)
{
    if(map[r][c] == 0 || visited[r][c])
        return false;
    
    visited[r][c] = true;
    for(int d= 0 ; d < 4 ;d++)
    {
        int ty = r+dy[d];
        int tx = c+dx[d];
        if(ty>=0 && ty<N && tx>=0 && tx<M && map[ty][tx]!=0 && !visited[ty][tx])
            dfs(ty,tx);
    }
    return true;
}

int iceberg_cnt()
{
    int cnt = 0;
    for(int r= 0 ;r < N ; r++)
        for(int c= 0 ; c <M; c++)
            {
                bool out = dfs(r,c);
                if(out)
                    cnt++;
            }
    return cnt;
}

void solve()
{
    int year = 0;
    while(1)
    {
        if(check_done())
        {
            year = 0;
            break;
        }
        if(iceberg_cnt()>=2)
            break;

        set_reduce_map();
        reduction();
        year++;

        memset(visited,false,sizeof(visited));
        memset(reduce_map,0,sizeof(reduce_map));
    }
    cout<<year;
}

int main()
{
    input();
    solve();
}