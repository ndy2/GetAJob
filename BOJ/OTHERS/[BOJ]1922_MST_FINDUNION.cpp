#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string.h>

using namespace std;

bool mysort(vector<int> a, vector<int> b)
{
    return a[2]<b[2];
}

int N,M;
vector<vector<int>> edges;
int parents[1001];
int set_size[1001];

void input()
{
    cin>>N>>M;
    vector<vector<int>> map_copy (N+1, vector<int>(N+1,0));

    int a,b,c;
    for(int i = 0 ; i <M ; i++)
    {
        cin>>a>>b>>c;
        if(a==b) continue;
        edges.push_back({a,b,c});
    }
}

void init()
{
    for(int i = 1 ; i<=N ; i++)
    {
        parents[i] = i;
        set_size[i] = 1;
    }
}

int find_(int idx)
{
    if(idx ==parents[idx])
        return idx;
    return parents[idx] = find_(parents[idx]);
}

void union_(int idx0, int idx1)
{
    idx0 = find_(idx0);
    idx1 = find_(idx1);
    if(set_size[idx0] < set_size[idx1])
        swap(idx0,idx1);
    parents[idx1] = parents[idx0];
    set_size[idx0] +=set_size[idx1];
    set_size[idx1] = 0;
}

void solve()
{
    int ans =0;
    
    sort(edges.begin(), edges.end(),mysort);
    init();
    
    for(auto e : edges)
    {
        if(find_(e[0]) != find_(e[1]))
        {
            union_(e[0],e[1]);
            ans +=e[2];
        }
    }
    cout<<ans;
}

int main()
{
    input();
    solve();
}