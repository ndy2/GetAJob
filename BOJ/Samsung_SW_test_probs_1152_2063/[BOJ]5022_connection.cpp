#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int N,M;

vector<vector<int>> as(2,vector<int>(2,0));
vector<vector<int>> bs(2,vector<int>(2,0));

void input()
{
    cin>>M>>N;
    for(int i = 0 ; i <2 ;i++)
        cin>>as[i][1]>>as[i][0];
    for(int i = 0 ; i <2 ;i++)
        cin>>bs[i][1]>>bs[i][0];
}

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

typedef struct info{
    int y,x,len;
    vector<vector<int>> path;
}info;

bool visited[101][101];
bool occupied[101][101];

int min_len(vector<vector<int>> a)
{
    int len;
    vector<vector<int>> path;
    
    queue<info> q;
    vector<vector<int>> dummy = {{a[0][0],a[0][1]}};
    q.push({a[0][0],a[0][1],0,dummy});
    visited[a[0][0]][a[0][1]] = true;
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        if(pos.y == a[1][0] && pos.x == a[1][1])
            {
                len = pos.len;
                path = pos.path;
                break;
            }
        for(int d= 0 ; d < 4; d++)
        {
            int ty = pos.y+dy[d];
            int tx = pos.x+dx[d];
            if(ty>=0 && ty<=N && tx>=0 && tx<=M && !visited[ty][tx] &&!occupied[ty][tx])
                {
                    visited[ty][tx]= true;
                    vector<vector<int>> new_path = pos.path;
                    new_path.push_back({ty,tx});
                    q.push({ty,tx,pos.len+1,new_path});
                }
        }
    }
    for(auto cor : path)
        occupied[cor[0]][cor[1]] = true;
        
    memset(visited,0,sizeof(visited));
    return len;
}

typedef struct info2{
    int y,x,len;
}info2;

int min_len_restricted(vector<vector<int>> b)
{
    int len=1e9;
    queue<info2> q;
    q.push({b[0][0],b[0][1],0});
    visited[b[0][0]][b[0][1]] = true;
    while(!q.empty())
    {
        info2 pos = q.front();
        q.pop();
        if(pos.y == b[1][0] && pos.x == b[1][1])
            {
                len = pos.len;
                break;
            }
        for(int d= 0 ; d < 4; d++)
        {
            int ty = pos.y+dy[d];
            int tx = pos.x+dx[d];
            if(ty>=0 && ty<=N && tx>=0 && tx<=M && !visited[ty][tx] &&!occupied[ty][tx])
                {
                    visited[ty][tx]= true;
                    q.push({ty,tx,pos.len+1});
                }
        }
    }
    memset(visited,0,sizeof(visited));
    memset(occupied,0,sizeof(occupied));
    return len;
}

void solve()
{
    int len_one;
    
    occupied[bs[0][0]][bs[0][1]] = true;
    occupied[bs[1][0]][bs[1][1]] = true;
    int min_len_a = min_len(as);
    
    occupied[bs[0][0]][bs[0][1]] = false;
    occupied[bs[1][0]][bs[1][1]] = false;
    int len_b_restricted = min_len_restricted(bs);
    len_one = min_len_a + len_b_restricted;

    int len_two;
    occupied[as[0][0]][as[0][1]] = true;
    occupied[as[1][0]][as[1][1]] = true;
    int min_len_b = min_len(bs);
    
    occupied[as[0][0]][as[0][1]] = false;
    occupied[as[1][0]][as[1][1]] = false;
    int len_a_restricted = min_len_restricted(as);
    len_two = min_len_b + len_a_restricted;
    int ans = min(len_one,len_two);
    if(ans >=1e9)
        cout<<"IMPOSSIBLE";
    else
        cout<<ans;
}

int main()
{
    input();
    solve();

    return 0;
}