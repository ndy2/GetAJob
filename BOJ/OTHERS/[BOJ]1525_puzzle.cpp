#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>
#include <unordered_map>

using namespace std;

vector<vector<int>> map_init(3,vector<int>(3,0));

typedef struct info{
    int y,x,cnt;
    vector<vector<int>> map;
}info;

unordered_map<long long,bool> visited;

long long info2bit(info pos)
{
    int shift = 0;
    long long bit = 0;

    for(int r = 0  ;r < 3 ; r++)
        for(int c= 0 ;c < 3 ; c++)
            {
                if(pos.map[r][c]==0) continue;
                bit |=(long long)pos.map[r][c] <<shift;
                shift+=4;
            }
    bit |=(long long)pos.y<<shift;
    shift+=4;
    bit |=(long long)pos.x<<shift;
    return bit;
}

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

vector<vector<int>> proc(vector<vector<int>> arr, int y1,int x1, int y2, int x2)
{
    swap(arr[y1][x1], arr[y2][x2]);
    return arr;
}

bool is_done(vector<vector<int>> map)
{
    if(map[0][0]!=1) return false;
    else if(map[0][1]!=2) return false;
    else if(map[0][2]!=3) return false;
    else if(map[1][0]!=4) return false;
    else if(map[1][1]!=5) return false;
    else if(map[1][2]!=6) return false;
    else if(map[2][0]!=7) return false;
    else if(map[2][1]!=8) return false;
    else if(map[2][2]!=0) return false;
    
    return true;
}

int main()
{
    vector<int> cor_init;
    for(int r = 0 ; r< 3 ; r++)
        for(int c= 0 ;c < 3 ;c ++)
        {
            cin>>map_init[r][c];
            if(map_init[r][c] ==0)
                cor_init = {r,c};
        }
    info init = {cor_init[0],cor_init[1],0,map_init};
    long long bit_init = info2bit(init);
    visited[bit_init]=1;
    // printf("%x\n",bit_init);
    queue<info> q;
    q.push(init);
    int ans = -1;
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        if(is_done(pos.map))
        {
            ans = pos.cnt;
            break;
        }
        for(int d= 0 ;d < 4 ; d++)
        {
            int ty = pos.y + dy[d];
            int tx = pos.x + dx[d];
            if(ty<0 || ty>=3 || tx<0 || tx>=3)
                continue;
            
            vector<vector<int>> t_map = proc(pos.map, pos.y,pos.x,ty,tx);
            info t_info = {ty,tx,pos.cnt+1,t_map};
            long long bit = info2bit(t_info);
            // printf("%x\n",bit);
            if(visited.find(bit) != visited.end())
                continue;

            visited[bit]=1;
            q.push(t_info);
        }
    }
    cout<<ans;
}