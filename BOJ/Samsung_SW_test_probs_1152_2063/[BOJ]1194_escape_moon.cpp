#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N,M;
char map[50][50];
bool visited[64][50][50];

typedef struct info{
    int cnt,keys,y,x;
}info;

vector<int> from;
vector<vector<int>> dest;

void input()
{
    cin>>N>>M;
    string line;
    for(int r= 0 ;r <N; r++){
        cin>>line;
        for(int c= 0 ; c< M ; c++)
            {
                map[r][c] = line[c];
                if(line[c] == '0')
                {
                    from = {r,c};
                    map[r][c] = '.';
                }
                else if(line[c] =='1')
                    dest.push_back({r,c});
            }
    }
        
}

int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

bool is_key(char c){
    return c>='a' && c<='f';
}

bool is_door(char c){
    return c>='A' && c<='F';
}

void solve()
{
    queue<info> q;
    q.push({0,0,from[0],from[1]});
    int ans =-1;
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();

        if(visited[pos.keys][pos.y][pos.x])
            continue;
        visited[pos.keys][pos.y][pos.x] = true;
        vector<int> cor = {pos.y, pos.x};
        if(find(dest.begin(), dest.end(), cor) != dest.end())
        {
            ans = pos.cnt;
            break;
        }
            
        for(int d= 0 ; d < 4; d++)
        {
            int ty = pos.y + dy[d];
            int tx = pos.x + dx[d];
            
            if(ty>=0 && ty< N && tx >=0 && tx <M && map[ty][tx] !='#' )
            {
                if(is_key(map[ty][tx]))
                    {
                        int key_idx = map[ty][tx] - 'a';
                        int new_key = pos.keys | (1<<key_idx);
                        q.push({pos.cnt+1, new_key, ty,tx});
                    }
                else if(is_door(map[ty][tx]))
                {
                    int door_idx = map[ty][tx] - 'A';
                    if((1<<door_idx) & pos.keys)
                        q.push({pos.cnt+1, pos.keys, ty,tx});

                }
                else
                    q.push({pos.cnt+1, pos.keys, ty,tx});
            }
        }
    }

    // cout<<ans;
}
int main()
{
    input();
    solve();
}