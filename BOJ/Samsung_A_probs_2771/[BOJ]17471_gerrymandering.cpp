#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>

using namespace std;

int map[11][11];
int population[11];
int N;

void input()
{
    cin>>N;
    int c,e;
    for(int i = 1; i <=N ;i++)
        cin>>population[i];
    for(int i = 1; i<=N ; i++)
    {
        cin>>c;
        for(int j = 0 ; j <c; j++)
            {
                cin>>e;
                map[i][e] = 1;
            }
    }
}

bool is_connected (set<int> a)
{
    bool visited[11]={false,};
    set<int> vs;
    queue<int> q;
    
    q.push(*a.begin());
    while(!q.empty())
    
    {
        int f = q.front();
        q.pop();
        if(visited[f]) continue;
        visited[f] = true;
        vs.insert(f);

        for(int i = 1; i <=N; i++)
            if(map[f][i] ==1 && find(a.begin(), a.end(), i)!= a.end() &&!visited[i])
                q.push(i);
    }
    return a==vs;    
}



int pop_gap(set<int> a, set<int> b)
{
    int pop_a=0, pop_b = 0;
    for(auto i : a)
        pop_a +=population[i];
    for(auto i : b)
        pop_b +=population[i];
    return abs(pop_a - pop_b);
}

void solve()
{
    int l = N/2;
    int ans = 1e9;
    for(int i = 1 ; i<= l ; i++)
    {
        vector<int> idx (N,0);
        for(int j = N-i; j<N; j++)
            idx[j] = 1;
        do{
            set<int> city_a, city_b;
            for(int j = 0 ; j <N ; j++)
                if(idx[j]==0)
                    city_a.insert(j+1);
                else
                    city_b.insert(j+1);
            
            if(is_connected(city_a) && is_connected(city_b))
                ans = min(ans, pop_gap(city_a, city_b));
            

        }while(next_permutation(idx.begin(), idx.end()));
    }
    if(ans == 1e9) ans = -1;
    cout<<ans;
}

int main() {
    input();
    solve();

    return 0;
}       