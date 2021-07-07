#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int N,M;
vector<vector<int>> map;

int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

int visited[20][20];
int score = 0;

void input()
{
    cin>>N>>M;
    vector<vector<int>> map_save(N,vector<int>(N,0));
    for(int r = 0 ; r <N; r++)
        for(int c = 0 ; c < N ; c++)
            cin>>map_save[r][c];
    map = map_save;
}

vector<vector<int>> block_list;

typedef struct block_info{
    int block_cnt,rainbow_block_cnt,r,c;
    vector<vector<int>> cors;
}block_info;

block_info info;

bool mysort(block_info a, block_info b)
{
    if(a.block_cnt != b.block_cnt)
        return a.block_cnt>b.block_cnt;
    else if(a.rainbow_block_cnt!=b.rainbow_block_cnt)
        return a.rainbow_block_cnt>b.rainbow_block_cnt;
    else if (a.r !=b.r)
        return a.r>b.r;
    else
        return a.c>b.c;
}

void init_info()
{
    info.block_cnt=0;
    info.rainbow_block_cnt =0;
    info.r = 0;
    info.c = 0;
    info.cors.clear();
}

void dfs(int r, int c, int target, bool init)
{
    if(visited[r][c])
        return;
    if(map[r][c] == -1 || map[r][c] == 77)
        return;
    if(map[r][c] !=target && map[r][c]!=0)
        return;
    if(init)
        {info.r = r; info.c =c; }
    visited[r][c] = 1;
    info.block_cnt++;
    if(map[r][c] == 0)
          info.rainbow_block_cnt++;
    info.cors.push_back({r,c});

    for(int d = 0 ; d < 4 ; d++)
    {
        int ty = r+dy[d];
        int tx = c+dx[d];
        if(ty>=0 && ty<N && tx>=0 && tx<N && !visited[ty][tx] && (map[r][c]==target || map[r][c] ==0 ) )
            dfs(ty,tx, target,false);
    }
}

void set_rainbow_block_unvisited()
{
    for(int r=  0 ; r<N ; r++)
        for(int c=  0 ; c < N ; c++)
            if(map[r][c]==0)
                visited[r][c] = false;
}

pair<bool,block_info> stage_one(vector<vector<int>> map)
{
    vector<block_info> vi;
    memset(visited,0,sizeof(visited));
    for(int r = 0 ; r < N ; r++ )
        for(int c= 0 ; c<N; c++)
            {
                if(map[r][c]!=0)
                {
                    init_info();
                    dfs(r,c, map[r][c],true);
                    set_rainbow_block_unvisited();
                    if(info.block_cnt>=2)
                        vi.push_back(info);
                }
            }
    
    sort(vi.begin(), vi.end(), mysort);
    
    if(vi.empty()) return {false, {0,0,0,0,{}}};
    else return {true,vi[0]};
}

void stage_two(block_info bi)
{
    //erase cor : 0 or coloridx -> 77
    for(auto cor : bi.cors)
    {
        map[cor[0]][cor[1]] = 77;
    }

    //add score
    score +=bi.block_cnt * bi.block_cnt;
}


void gravity()
{
    for(int c = 0 ; c < N ; c++)
    {
        int droped_row = N-1;

        for(int r = N-1; r >=0 ; r--)
        {
            if(map[r][c] == 77)
                continue;
            else if(map[r][c] == -1)
                droped_row = r-1;
            else{
                if(map[droped_row][c] == 77)
                    {
                        map[droped_row][c] = map[r][c];
                        map[r][c] = 77;
                
                    }
                droped_row --;

            }
        }
    }
}

void rotate_map_ccw90()
{
    vector<vector<int>> map_rotate(N,vector<int>(N,0));
    for(int r= 0 ; r< N ; r++)
        for(int c = 0 ; c <N; c++)
            map_rotate[r][c] = map[c][N-r-1];
    map = map_rotate;
}

void solve()
{
    while(1){
        //stage one
        pair<bool,block_info> out =stage_one(map);
        if(!out.first)
            break;
        block_info bi = out.second;
        //stage two
        stage_two(bi);
        //stage 3 4 5
        gravity();
        rotate_map_ccw90();
        gravity();
    }   
    cout<<score;
}

int main() {
    input();
    solve();
    
    return 0;
}       