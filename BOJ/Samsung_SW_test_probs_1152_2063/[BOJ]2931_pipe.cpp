#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N,M;
vector<vector<int>> end_points = {{0,0},{0,0}};
vector<int> ans;
int board[26][26];

void input()
{
    cin>>N>>M;
    for(int r = 1 ; r <= N ; r++)
    {
        string line;
        cin>>line;
        for(int c= 1 ;c <= M ; c++)
            if(line[c-1] == '.')
                continue;
            else if(line[c-1] =='M')
            {
                board[r][c] = 8;
                end_points[0] = {r,c};
            }
            else if(line[c-1] =='Z')
            {
                board[r][c] = 8;
                end_points[1] = {r,c};
            }
            else if(line[c-1] == '|')
                board[r][c] = 5;
            else if(line[c-1] =='-')
                board[r][c] = 6;
            else if(line[c-1] == '+')
                board[r][c] = 7;
            else 
                board[r][c] = line[c-1]-'0';
    }
}

//L R U D
#define L 0
#define R 1
#define U 2
#define D 3

int dy[4] = {0,0,-1,1};
int dx[4] = {-1,1,0,0};
int flip[4] = {R,L,D,U};
int dir =0;
vector<vector<int>> block2neighbor = {{},{R,D},{U,R},{L,U},{L,D},{U,D},{L,R},{L,R,U,D},{}};

char dir2char[16];

void set_dir2char()
{
    dir2char[5] = '3';
    dir2char[6] = '2';
    dir2char[9] = '4';
    dir2char[10] = '1';
    dir2char[3] = '-';
    dir2char[12] = '|';
    dir2char[15] = '+';
}

void solve()
{
    for(int r= 1 ; r <= N ; r++)
        for(int c= 1 ; c <= M ; c++)
            for(auto d  :block2neighbor[board[r][c]])
            {
                int ty = r+dy[d];
                int tx = c+dx[d];
                if(board[ty][tx]==0 )
                {
                    // printf("%d %d %d\n",ty,tx,d);
                    ans = {ty,tx};
                    dir |=1<<flip[d];
                }
            }
    set_dir2char();
    if(dir2char[dir] == 0)
        for(int i = 0 ; i < 2; i++)
            for(auto d  :block2neighbor[7])
                {
                    int ty = end_points[i][0]+dy[d];
                    int tx = end_points[i][1]+dx[d];
                    if(ty == ans[0] && tx ==ans[1])
                    {
                        // printf("%d %d %d\n",ty,tx,d);
                        ans = {ty,tx};
                        dir |=1<<flip[d];
                        break;
                    }
                }
    printf("%d %d %c",ans[0],ans[1],dir2char[dir]);
}

int main()
{
    ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    input();
    solve();
}