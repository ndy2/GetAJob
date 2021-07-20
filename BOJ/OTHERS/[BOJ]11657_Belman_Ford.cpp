#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include <string.h>
#define INF 987654321
using namespace std;

int N,M;
unordered_map<int, vector<vector<int>>> map;

void input()
{
    cin>>N>>M;
    int a,b,c;
    for(int i = 1 ; i <=M ; i++)
    {
        cin>>a>>b>>c;
        map[a].push_back({b,c});
    }
}

void solve()
{
    vector<long long> idx2dist(510, INF);
    idx2dist[1] = 0;
    
    for(int i = 1 ; i <=N-1 ; i++)
        for(int j = 1 ; j <=N ; j++)
            if(map.find(j)!=map.end() && idx2dist[j] !=INF)
                for(auto e : map[j])
                    idx2dist[e[0]] = min(idx2dist[e[0]], idx2dist[j] + e[1]);
    
    for(int i = 1 ; i <=N ; i++)
        if(map.find(i)!=map.end()&&idx2dist[i] !=INF)
             for(auto e : map[i])
                 if(idx2dist[e[0]] > idx2dist[i] + e[1])
                    {
                        cout<<-1<<endl;
                        return;
                    }                 
    
    for(int i = 2 ; i <=N ; i++)
    {
        if(idx2dist[i] ==INF) cout<<-1<<endl;
        else cout<<idx2dist[i]<<endl;
    }
    
}

int main()
{
    input();
    solve();
}