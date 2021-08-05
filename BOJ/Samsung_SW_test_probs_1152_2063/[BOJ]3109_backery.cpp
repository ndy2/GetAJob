#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N,M;
bool board[10000][500];
bool visited[10000][500];

void input()
{
    cin>>N>>M;
    for(int r = 0 ; r < N ; r++)
    {
        string line;
        cin>>line;
        for(int c= 0 ;c < M ; c++)
            if(line[c] == 'x')
                board[r][c] = true;
    }
}

int dy[3] = {-1,0,1};
bool glb_reached = false;

bool dfs(int r, int c)
{
    if(visited[r][c])
        return false;
    visited[r][c] = true;
    
    if(c==M-1) 
        return true;
    
    for(int d = 0 ; d < 3 ; d++)
    {
        int ty = r + dy[d];
        int tx = c +1;
        bool ret = false;
        if(ty>=0 && ty<N && tx<M && !board[ty][tx])
            if(dfs(ty,tx))
                return true;
    }
    // visited[r][c] = false;
    return false;
}

void solve()
{
    int ans = 0;
    for(int row = 0 ; row < N ; row++)
        if(dfs(row,0))
            ans++;
    cout<<ans;
}

int main()
{
    ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    input();
    solve();
}