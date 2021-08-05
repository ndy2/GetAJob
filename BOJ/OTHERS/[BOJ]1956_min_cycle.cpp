#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#define INF 987654321
using namespace std;

int V,E;
bool visited[401];
unordered_map<int,vector<vector<int>>> map;

void input()
{
    cin>>V>>E;
    int a, b,c;
    for(int i = 0 ; i < E ; i++)
    {
        cin>>a>>b>>c;
        map[a].push_back({b,c});
    }
}

int back_cost[401];

int ans = INF;

void dfs(int idx, int cost)
{
    if(visited[idx])
    {
        //cycle detected
        ans = min(ans, back_cost[idx] + cost);
        return;
    }
    printf("idx %d cost %d \n",idx,cost);
    
    for(int i = 1 ; i <=V ; i++)
        if(visited[i])
            back_cost[i] +=cost;
    visited[idx] = true;
    for(int i = 1 ; i <=V ; i++)
        if(!visited[i])
            printf("N ");
        else
            printf("%d ",back_cost[i]);
    cout<<endl<<endl;
    
    for(auto n : map[idx])
    {
        dfs(n[0],n[1]);
        if(visited[n[0]]){
        visited[n[0]] = false;
        back_cost[n[0]] -=n[1];}
    }
}

void solve()
{
    dfs(1,0);
    printf("%d",ans);
}

int main()
{
    input();
    solve();
    return 0;
}