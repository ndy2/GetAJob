#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int visited[51][51];
int board[51][51];

int dy[] = {0,0,1,-1, 1,1,-1,-1};
int dx[] = {1,-1,0,0, -1,1,-1,1};

int N,M;

int dfs(int r, int c)
{
    if(visited[r][c] == 1 ||board[r][c] ==0)
        return 0;

    else
    {
        visited[r][c]  = 1;
        for(int d = 0; d < 8; d++)
        {
            int ty = r + dy[d];
            int tx = c + dx[d];
            if(ty>=0 && ty<N && tx >=0 && tx <M && !visited[ty][tx] &&board[ty][tx]==1)
                dfs(ty,tx);
        }
    }
    return 1;
}

int main()
{
    while(1)
    {
        cin>>M>>N;
        if(N==0)
            break;
        for(int r= 0 ; r < N ; r ++)
            for(int c= 0 ; c < M ; c++)
                cin>>board[r][c];
        
        int ans = 0;
        for(int r= 0 ; r < N ; r ++)
            for(int c= 0 ; c < M ; c++)
                ans += dfs(r,c);
            
        memset(visited, 0, sizeof(visited));
        memset(board, 0, sizeof(board));

        cout<<ans<<"\n";
    }
}