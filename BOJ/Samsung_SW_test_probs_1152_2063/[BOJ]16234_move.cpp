#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>

using namespace std;
int map[50][50];
int visited[50][50];

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};


int N,L,R;
vector<vector<vector<int>>>feds;
vector<vector<int>> fed;

void input()
{
    cin>>N>>L>>R;
    for(int r = 0 ; r < N ; r++)
        for(int c = 0 ; c < N ; c++)
            cin>>map[r][c];
}

void dfs(int r, int c)
{
    if(visited[r][c])
        return;
    else
    {
        visited[r][c] = true;
        fed.push_back({r,c});
        for(int d = 0 ; d<4; d++)
        {
            int ty = r+ dy[d];
            int tx = c+ dx[d];
            if(ty>=0 && ty<N &&tx>=0 && tx<N && abs(map[ty][tx]-map[r][c])>= L && abs(map[ty][tx]-map[r][c])<=R)
                dfs(ty,tx);
            
        }
    }
}

void solve()
{
    int answer =0;
    int days =0;
    while(1)
    {
        days++;
        for(int r = 0 ; r < N ; r++)
            for(int c = 0 ; c < N ; c++)
                {
                    dfs(r,c);
                    if(fed.size()>1)
                        feds.push_back(fed);
                    fed.clear();
                }

        if(feds.empty())
            break;
        int sum,avg;
        for(auto f : feds)
        {
            answer++;
            sum =0;
            for(auto c : f)
                sum+=map[c[0]][c[1]];
            avg = sum/f.size();
            for(auto c : f)
                map[c[0]][c[1]] = avg;
        }
        feds.clear();
        memset(visited, 0, sizeof(visited));
    }

    cout<<days-1;           
}

int main() {
    input();
    solve();

    return 0;
}       