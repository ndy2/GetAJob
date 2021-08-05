#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>

using namespace std;

int N,M;
int Q;
vector<int> foward[10001];
vector<int> backward[10001];
vector<pair<int,int>> edges = {{0,0}};
queue<int> query;
bool visited[10001];

void input()
{
    cin>>N>>M;
    int a,b;
    for(int i = 0 ; i < M ; i++)
    {
        cin>>a>>b;
        edges.push_back(make_pair(a,b));
        foward[a].push_back(b);
        backward[b].push_back(a);
    }
    int q;
    // cin>>Q;
    for(int i = 0; i <Q ; i++)
        {
            cin>>q;
            query.push(q);
        }
}

void dfs_foward(int idx, bool visited[])
{
    if(visited[idx])
        return;
    else
    {
        visited[idx] = true;
        for(auto f : foward[idx])
            if(!visited[f])
                dfs_foward(f,visited);
    }
}

void dfs_backward(int idx, bool visited[])
{
    if(visited[idx])
        return;
    else
    {
        visited[idx] = true;
        for(auto b : backward[idx])
            if(!visited[b])
                dfs_backward(b,visited);
    }
}


void solve(int tc)
{
    //Step 1 : find answer of day 0
    //choose random point and dfs forward, backward

    int mass_day_zero = 0;
    for(int idx = 1 ; idx <=N ; idx++)
    {
        if(visited[idx]) continue;
        // visited[idx] = true;
        // dfs_foward(idx,visited);
        visited[idx] = false;
        dfs_backward(idx,visited);
        mass_day_zero++;
    }
    printf("#%d %d\n",tc, mass_day_zero);
    int cur = mass_day_zero;
    while(!query.empty())
    {
        memset(visited,0,sizeof(visited));

        int q= query.front();
        query.pop();
        int from = edges[q].first, to = edges[q].second;
        foward[from].erase(find(foward[from].begin(),foward[from].end(),to));
        backward[to].erase(find(backward[to].begin(),backward[to].end(),from));
        
        int mass_day = 0;
        for(int idx = 1 ; idx <=N ; idx++)
        {
            if(visited[idx]) continue;
            // visited[idx] = true;
            dfs_foward(idx,visited);
            visited[idx] = false;
            dfs_backward(idx,visited);
            mass_day++;
        }
        printf(" %d",mass_day);
    }
    printf("\n");
}

void clear()
{
    for(int i = 0 ; i < M ; i++)    
        {
            foward[i].clear();
            backward[i].clear();
        }
    memset(visited,0,sizeof(visited));
}

int main()
{
    int TC;
    cin>>TC;
    for(int tc = 1; tc<=TC; tc++)
    {
        input();
        solve(tc);
        clear();
    }
}