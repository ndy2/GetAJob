#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int N;
int n_tile;
vector<vector<int>> tiles;

void input()
{
    cin>>N;
    n_tile = N*N - N/2;
    vector<vector<int>> tiles_copy(n_tile,vector<int>(2,0));
    for(int t = 0 ; t < n_tile;t++)
        cin>>tiles_copy[t][0]>>tiles_copy[t][1];
    
    tiles = tiles_copy;
}

//LEFT, LEFT UP, RIGHT UP, RIGHT, RIGTH DOWM , LEFT DOWN
int di[6];

void set_directions()
{
    di[0] = -1;
    di[1] = -N;
    di[2] = -(N-1);
    di[3] = +1;
    di[4] = +N;
    di[5] = N-1;
}

typedef struct info{
    int idx,len;
    vector<int> path;
}info;

bool value_check(int dir, int from, int dest)
{
    if(dir == 0 || dir == 1 || dir == 5)
        return tiles[from][0] == tiles[dest][1];
    else
        return tiles[from][1] == tiles[dest][0];
}

void solve()
{
    set_directions();
    int ans = 1e9;
    int period = N+(N-1);
    queue<info> q;
    vector<bool> visited(n_tile,false);
    visited[0] = true;
    info init ={0,0,{0}};
    q.push(init);
    info largest_idx_info = init;

    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        if(pos.idx == n_tile-1)
        {
            largest_idx_info = pos;
            break;
        }
        
        if(largest_idx_info.idx < pos.idx)
            largest_idx_info = pos;

        for(int d = 0 ; d < 6; d++)
        {
            int ti = pos.idx+di[d];
            //range check
            if(ti<0 || ti>=n_tile)
                continue;
            else {
                if(visited[ti])
                    continue;
                //index validation
                int orig = pos.idx + 10*period;
                if(orig % period ==0 &&(d==0||d==1||d==5))
                    continue;
                else if(orig % period ==N-1 &&(d==2||d==3||d==4))
                    continue;
                else if(orig % period ==N && d==0)
                    continue;
                else if(orig % period == period-1 && d==3)
                    continue;
                //value check
                if(value_check(d,pos.idx,ti))
                {
                    visited[ti] = true;
                    vector<int> new_path =pos.path;
                    new_path.push_back(ti);
                    q.push({ti,pos.len+1,new_path});
                }
            }
        }
    }


    cout<<largest_idx_info.len+1<<endl;
    for(auto i : largest_idx_info.path)
        cout<<i+1<<" ";
}

int main()
{
    input();
    solve();

    return 0;
}