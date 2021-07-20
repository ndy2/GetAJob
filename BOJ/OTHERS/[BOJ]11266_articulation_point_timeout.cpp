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
vector<int> num_family(10001,0);
vector<int> num_family_removed(10001,0);

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

int dfs_remove(int remove, int cur)
{
    if(visited[cur])
        return -1;
    visited[cur] = true;
    family.push_back(cur);
    for(auto n : edges[cur])
        if(!visited[n] && n !=remove)
            dfs_remove(remove,n);
    return family.size();
}

vector<int> sol_tree(vector<int> tree)
{
     vector<int> ans;
     for(int i = 0 ; i < tree.size() ; i++ )
     {
         visited = vector<bool> (10001,false);
         for(int j = 0 ; j < tree.size() ; j++)
            {
                if (i==j) continue;
                family.clear();

                int num_family = dfs_remove(tree[i],tree[j]);
                if(num_family == -1) continue;
                else if (num_family != tree.size() -1) {
                    ans.push_back(tree[i]);
                    j = tree.size();
                    continue;
                }
            }
     }
     return ans;
}

void solve()
{   
    vector<int> ans;
    //step one
    //check size of graph for each edges
    vector<vector<int>> forest = init_num_family();
    visited = vector<bool> (10001, false);
    
    for(auto tree : forest)
    {
        vector<int> out = sol_tree(tree);
        for(auto o : out)
            ans.push_back(o);
    }
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<endl;
    for(auto a : ans)
        cout<<a<<" ";
}

int main()
{
    input();
    solve();
}