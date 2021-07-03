#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <string.h>
#include <algorithm>



using namespace std;
int map[20][20];
int visited[20][20];

int dy[4] = {-1,0,0,+1};
int dx[4] = {0,-1,1,0};

int N;
int time = 0;
vector<int> bs_glb;

bool mysort(vector<int> a, vector<int> b)
{
    return a[2]<b[2]?true:
            a[2]>b[2]?false:
            a[0]<b[0]?true:
            a[0]>b[0]?false:
            a[1]<b[1]?true:false;
}

void print_map()
{
    for(int r = 0 ; r < N ; r++)
        {
            for(int c= 0 ; c<N ; c++)
                cout<<map[r][c]<<" ";
            cout<<endl;
        }
    cout<<endl;
}

void input()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(nullptr);
    int m;
    cin>>N;
    for(int r = 0 ; r < N ; r++)
        for(int c = 0 ; c < N ; c++)
        {
            cin>>m;
            if(m==9)
                bs_glb={r,c,2,0};
            map[r][c]=m;
            
        }
}

vector<int> bfs(vector<int> bs)
{
    queue<vector<int>> q;
    vector<int> init = {bs[0], bs[1], 0};
    q.push(init);
    int bs_size = bs[2];
    visited[bs[0]][bs[1]] = true;
    int target_y;
    int target_x;
    
    vector<vector<int>> eatable;
    bool set = 0;
    int least_time;

    while(!q.empty())
    {
        vector<int> pos = q.front();
        q.pop();
        if(map[pos[0]][pos[1]]>0 &&  map[pos[0]][pos[1]]<bs_size)
            eatable.push_back(pos);
        for(int i = 0 ; i<4 ; i++)
        {
            int ty = pos[0]+dy[i];
            int tx = pos[1]+dx[i];
            if(ty>=0 && ty<N && tx >=0 && tx <N && !visited[ty][tx] &&map[ty][tx] <=bs_size)
            {
                visited[ty][tx] = true;
                q.push({ty,tx,pos[2]+1});
            }
                
        }
    }
    if(eatable.empty())
        return {-1};
    sort(eatable.begin(), eatable.end(), mysort);

    bs[0] = eatable[0][0];
    bs[1] = eatable[0][1];
    map[bs[0]][bs[1]] = 0;
    
    bs[3] +=1;
    if(bs[2]==bs[3])
    {
        bs[2]+=1;
        bs[3] =0;
    }
    time += eatable[0][2];
    memset(visited,0,sizeof(visited));
    return bs;
}

void solve()
{
    map[bs_glb[0]][bs_glb[1]]  = 0;
    while (bs_glb[0]!=-1)
    {
        bs_glb = bfs(bs_glb);
        // for(int i = 0 ; i < 4 ; i++)
        //     cout<<bs_glb[i]<<" ";
        // cout<<endl<<endl;

    }
    cout<<time;
}


int main() {
    input();
    solve();

    return 0;
}       