#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct r{
    int x1,y1,x2,y2;
}r;
int N,M,K;
int map[100][100];
int visited[100][100];


vector<r> regions;

void input()
{
    int x1,y1,x2,y2;
    cin>>N>>M>>K;
    for(int i = 0 ; i < K ; i++)
        {
            cin>>x1>>y1>>x2>>y2;
            regions.push_back({x1,y1,x2,y2});
        }
}

void set_map()
{
    for(auto region : regions)
    {
        for(int row = region.y1 ; row<region.y2; row++)
            for(int col =region.x1 ; col<region.x2 ; col++)
                map[row][col]=1;
    }
}

void print_map()
{
    cout<<endl;
    for(int r = N-1 ; r >=0 ; r--)
        {
        for(int c= 0 ; c <M ; c++)
            cout<<map[r][c]<<" ";
        cout<<endl;
        }
}

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

vector<int> region_size;

int glb_cnt = 0;
void dfs(int r, int c, bool root)
{
    if(map[r][c]==1 || visited[r][c])
        return;
    visited[r][c] = true;
    glb_cnt++;
    for(int d= 0 ;d <4 ;d++)
    {
        int ty =r+dy[d];
        int tx =c+dx[d];
        if(ty>=0&& ty<N && tx>=0 && tx<M && map[ty][tx]==0 && !visited[ty][tx])
            dfs(ty,tx,false);
    }
    if(root) {
        region_size.push_back(glb_cnt);
        glb_cnt = 0;
    }
    return;
}

void region_cnt()
{
    int cnt=0;
    for(int r= 0 ;r < N ; r++)
        for(int c= 0 ;c < M; c++)
                dfs(r,c,true);
    sort(region_size.begin(), region_size.end());
}

void solve()
{
    set_map();
    // print_map();
    region_cnt();

    cout<<region_size.size()<<endl;
    for(auto r: region_size)
        cout<<r<<" ";
    
}

int main()
{
    input();
    solve();
}