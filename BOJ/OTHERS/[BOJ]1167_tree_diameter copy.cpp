#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

#include <string.h>

using namespace std;

int N;
unordered_map<int, vector<vector<int>>> T;
int idx;

void input()
{
    cin>>N;
    for(int i = 1; i<=N ; i++)
    {
        cin>>idx;
        int neighbor = 0, dist;

        while(1)
        {   
            cin>>neighbor;
            if(neighbor==-1)
                break;
            cin>>dist;
            T[idx].push_back({neighbor,dist});
        }
    }
}

int find_end_point(int idx)
{
    vector<bool> visited(N+1,false);
    queue<int> q;
    q.push(idx);
    visited[idx] = true;
    int num_visited = 1;
    while(!q.empty())
    {
        int pos = q.front();
        q.pop();

        for(auto e : T[pos])
        {
            if(!visited[e[0]])
                {
                    visited[e[0]] = true;
                    num_visited++;
                    if(num_visited == N)
                        return e[0];
                    q.push(e[0]);
                }
        }

    }
    return -777;
}

typedef struct info{
    int idx, dist;
}info;

info search_all_end_to_end_from(int idx)
{
    info ret = {-1,-1};
    queue<info> q;
    q.push({idx,0});
    vector<bool> visited(N+1,false);
    visited[idx] = true;
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();

        int num_pushed = 0;
        for(auto e : T[pos.idx])
        {
            if(!visited[e[0]])
            {
                num_pushed++;
                visited[e[0]] = true;
                q.push({e[0], pos.dist + e[1]});
            }
        }
        if(num_pushed ==0 && pos.dist>ret.dist)
            ret = pos; 
            
    }

    return ret;
}

void solve()
{
    int end_point = find_end_point(idx);
    info ans0 = search_all_end_to_end_from(end_point);
    info ans1 = search_all_end_to_end_from(ans0.idx);

    cout<<max(ans0.dist, ans1.dist);
}

int main()
{
    input();
    solve();
}