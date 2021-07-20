#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string.h>

using namespace std;

int V,E;
unordered_map<int, vector<int>> edges;

void input()
{
    cin>>V>>E;
    int a,b;
    for(int i = 0 ; i < E ; i++)
    {
        cin>>a>>b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
}

vector<bool> visited(10001,false);
vector<int> family;

bool dfs(int idx)
{
    if(visited[idx])
        return false;
    visited[idx] = true;
    family.push_back(idx);
    for(auto n : edges[idx])
        if(!visited[n])
            dfs(n);
    return true;
}

vector<vector<int>> init_num_family()
{
    vector<vector<int>> forest;
    for(int i = 1 ; i <= V ; i++)
        if(dfs(i))
            {
                forest.push_back(family);
                family.clear();
            }
    return forest;
}

void solve()
{   
    cout<<init_num_family().size();
}

int main()
{
    input();
    solve();
}