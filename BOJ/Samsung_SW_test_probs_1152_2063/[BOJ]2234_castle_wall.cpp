#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int N,M;
int map[50][50];
int board[50][50];

bool visited[50][50];

int dy[4] = {0,-1,0,1};
int dx[4] = {-1,0,1,0};


void input()
{
    cin>>M>>N;
    for(int r = 0 ; r < N ; r ++)
        for(int c =0 ; c < M ; c++)
            cin>>map[r][c];
}

bool is_movable(int dir, int from)
{
    return !((from>>dir)&1);
}

int room_size = 0;
void dfs(int y, int x, int idx)
{
    if(visited[y][x])
        return;

    visited[y][x] = 1;
    board[y][x] = idx;
    room_size ++;
    for(int d = 0 ; d < 4 ;d++)
    {
        if(is_movable(d,map[y][x]))
        {
            int ty = y+dy[d];
            int tx = x+dx[d];
            if(ty>=0 && ty<N && tx>=0 && tx<M && !visited[ty][tx])
                dfs(ty,tx,idx);
        }
        
    }        
}

void solve()
{
    int room_idx = 0 ;
    vector<int> room_size_vec;
    for(int r = 0 ; r < N ; r++)
        for(int c = 0 ;c < M ; c++)
        {
            dfs(r,c,room_idx);
            if(room_size !=0)
                {
                    room_size_vec.push_back(room_size);
                    room_size = 0;
                    room_idx ++;
                }
        }
    
    int n = room_size_vec.size();
    printf("%d\n" ,room_size_vec.size()); 
    printf("%d\n" , *max_element(room_size_vec.begin(), room_size_vec.end()));
    int max_connection = 0;

    for(int r = 0 ; r < N ; r++)
        for(int c= 0 ; c < M; c++)
                for(int d = 0 ; d < 4; d++)
                {
                    int ty = r+dy[d];
                    int tx = c+dx[d];
                    if(ty>=0&& ty<N && tx>=0 && tx<M && board[r][c] != board[ty][tx])
                        max_connection = max(max_connection, room_size_vec[board[r][c]]+room_size_vec[board[ty][tx]]);

                }

    printf("%d",max_connection);    


}


int main()
{
    input();
    solve();

    return 0;
}