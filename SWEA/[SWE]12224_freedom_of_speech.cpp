#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

int N,M;
int Q;
vector<int> foward[10001];
vector<int> backward[10001];
vector<pair<int,int>> edges = {{0,0}};
vector<int> query;
bool visited_from[10001];
bool visited_to[10001];

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
    cin>>Q;
    for(int i = 0; i <Q ; i++)
        {
            cin>>q;
            query.push_back(q);
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
        if(visited_from[idx]!=0) continue;
        // visited[idx] = true;
        dfs_foward(idx,visited_from);
        visited_from[idx] = 0;
        dfs_backward(idx,visited_from);
        mass_day_zero++;
    }
    printf("#%d %d\n",tc, mass_day_zero);
    int cur = mass_day_zero;
    //executed query
    for(auto q : query)
    {
        memset(visited_from,0,sizeof(visited_from));
        memset(visited_to,0,sizeof(visited_to));

        int from = edges[q].first, to = edges[q].second;
        foward[from].erase(find(foward[from].begin(),foward[from].end(),to));
        backward[to].erase(find(backward[to].begin(),backward[to].end(),from));
        dfs_foward(from,visited_from);
        // dfs_backward(from,visited_from);
        dfs_foward(to,visited_to);
        // dfs_backward(to,visited_to);

        bool from_only=false;
        bool to_only = false;
        for(int i = 1 ; i<=N; i++)
            if(from_only && to_only)
                break;
            else
                if(visited_from[i] && !visited_to[i])
                    from_only = true;
                else if(!visited_from[i] && visited_to[i])
                    to_only = true;
        if(from_only && to_only)
            cur++;
        printf(" %d",cur);
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
    query.clear();
    memset(visited_from,0,sizeof(visited_from));
    memset(visited_to,0,sizeof(visited_to));
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