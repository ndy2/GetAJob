#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>
#include <unordered_map>

using namespace std;


int N,t1,t2,R;
unordered_map<int, vector<int>> idx2child;
unordered_map<int, vector<int>> idx2parent;
bool visited[101];

void input()
{
    cin>>N>>t1>>t2>>R;
    int u,d;
    for(int i = 0 ; i < R ; i++)
    {
        cin>>u>>d;
        if(idx2child.find(u)!=idx2child.end())
            idx2child[u].push_back(d);
        else
            idx2child[u] = {d};
        
        if(idx2parent.find(d)!=idx2parent.end())
            idx2parent[d].push_back(u);
        else
            idx2parent[d] = {u};
    }
}

typedef struct info{
    int idx,cnt;
}info;

void solve()
{
    queue<info> q;
    q.push({t1,0});
    int ans = -1;
    visited[t1] = true;
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        if(pos.idx == t2)
            {
                ans = pos.cnt;
                break;
            }
        for(auto p : idx2parent[pos.idx])
            if(!visited[p])
            {   
                visited[p] = true;
                q.push({p,pos.cnt+1});
            }
        for(auto c : idx2child[pos.idx])
            if(!visited[c])
            {
                visited[c] = true;
                q.push({c,pos.cnt+1});
            }
    }
    cout<<ans;
}

int main()
{
    input();
    solve();
}