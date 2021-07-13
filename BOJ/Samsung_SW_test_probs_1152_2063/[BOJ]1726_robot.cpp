#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

int N,M;
bool map[101][101];
bool visited[101][101][4];

int dy[5] = { 0, 0,0,1,-1};
int dx[5] = { 0, 1,-1,0,0};

vector<int> from(3,0);
vector<int> dest(3,0);

unordered_map<int,int> to_left = {{1,4},{4,2},{2,3},{3,1}};
unordered_map<int,int> to_right = {{4,1},{2,4},{3,2},{1,3}};

typedef struct info{
    int cnt,y,x,dir;
}info;

void input()
{
    cin>>N>>M;
    for(int r = 1 ; r<= N ; r++)
        for(int c= 1; c <= M ; c++)
            cin>>map[r][c];
    for(int i = 0 ; i < 3; i++)
        cin>>from[i];
    for(int i = 0 ; i < 3; i++)
        cin>>dest[i];
}

vector<info> proc_rotate(info pos)
{
    vector<info> ret;
    info turn_left = {pos.cnt+1, pos.y, pos.x, to_left[pos.dir]};
    info turn_right = {pos.cnt+1, pos.y, pos.x, to_right[pos.dir]};
    if(!visited[turn_left.y][turn_left.x][turn_left.dir])
        ret.push_back(turn_left);
    if(!visited[turn_right.y][turn_right.x][turn_right.dir])
        ret.push_back(turn_right);
    
    return ret;
}

vector<info> proc_move(info pos)
{
    vector<info> ret;
    for(int i = 1 ; i <= 3; i++)
    {
        int ty = pos.y + i*dy[pos.dir];
        int tx = pos.x + i*dx[pos.dir];
        
        if(ty>=1 && ty<=N && tx>=1 && tx <=M && map[ty][tx]==0 && !visited[ty][tx][pos.dir])
            ret.push_back({pos.cnt+1, ty, tx, pos.dir});
        else
            break;
    }
    return ret;
}



void solve()
{
    queue<info> q;
    q.push({0,from[0],from[1],from[2]});
    int ans = 0;
    while(!q.empty())
    {
        info pos=q.front();
        q.pop();
        if(visited[pos.y][pos.x][pos.dir])
            continue;
        visited[pos.y][pos.x][pos.dir] = true;

        if(dest[0] == pos.y && dest[1] == pos.x && dest[2] == pos.dir)
            {
                ans = pos.cnt;
                break;
            }

        vector<info> vi_rotate = proc_rotate(pos);
        vector<info> vi_move   = proc_move(pos);
        for(auto p : vi_rotate)
            q.push(p);
          
        for(auto p : vi_move)
            q.push(p);
    }
    cout<<ans;
}

int main()
{
    input();
    solve();

    return 0;
}