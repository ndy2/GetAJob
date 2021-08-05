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
int visited[10001];

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
    cin>>Q;
    int q;
    for(int i = 0; i <Q ; i++)
        {
            cin>>q;
            query.push_back(q);
        }
}

void dfs_foward(int idx)
{
    if(visited[idx])
        return;
    visited[idx] = 1;
    for(auto f : foward[idx])
        if(!visited[f])
            dfs_foward(f);
}

bool glb_meet = false;

void dfs_backward(int idx, int mark)
{
    if(glb_meet) return;
    if(visited[idx]==mark)
        return;
    else if(visited[idx]!=0 && visited[idx]!=mark)
    {
        glb_meet = true;
        return;
    }
    else
    {
        visited[idx] = mark;
        for(auto f : backward[idx])
            if(visited[f]!=mark && !glb_meet)
                dfs_backward(f,mark);
    }
}

void print_foward()
{
    for(int i = 1 ; i <=N ; i++)
    {
        cout<<"foward "<<i<<" ";
        for(auto f : foward[i])
            cout<<f<<" ";
        cout<<endl;
    }
    cout<<endl;
}

void solve(int tc)
{
    //Step 1 : find answer of day 0
    //choose random point and dfs forward, backward

    int mass_day_zero = 0;
    for(int idx = 1 ; idx <=N ; idx++)
    {
        if(visited[idx]!=0) continue;
        // visited[idx] = true;
        dfs_foward(idx);
        visited[idx] = 0;
        dfs_backward(idx,1);
        mass_day_zero++;
    }
    printf("#%d %d\n",tc, mass_day_zero);
    int cur = mass_day_zero;
    //executed query
    //만났었는데 안만나게 되면 +
    for(auto q : query)
    {
        memset(visited,0,sizeof(visited));
        int from = edges[q].first, to = edges[q].second;
        printf("executed query : remove edge %d from %d to %d\n",q, from,to);
        glb_meet = false;
        dfs_backward(from,1);
        dfs_backward(to,2);
        if(glb_meet){
            glb_meet = false;
            memset(visited,0,sizeof(visited));
            foward[from].erase(find(foward[from].begin(),foward[from].end(),to));
            backward[to].erase(find(backward[to].begin(),backward[to].end(),from));
            print_foward();
            dfs_backward(from,1);
            dfs_backward(to,2);
            if(!glb_meet)
                cur++;
        }
        printf("cur: %d\n\n",cur);
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