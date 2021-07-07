#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <cmath>
#include <unordered_map>

using namespace std;

int N;
int map_class[21][21];

int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

bool mysort2(vector<int> a, vector<int> b)
{
    if(a[2]!=b[2])
        return a[2]>b[2];
    else if(a[0]!=b[0])
        return a[0]<b[0];
    return a[1]<b[1];
}


vector<vector<int>> test_one(int idx, vector<int> pref)
{
    vector<vector<int>> list;
    int map_adj[21][21];
    memset(map_adj, 0, sizeof(map_adj));
    for(int r = 1 ; r <=N ; r++)
        for(int c = 1; c <=N ; c++)
        {
            if(map_class[r][c]!=0 && find(pref.begin(), pref.end(), map_class[r][c]) != pref.end())
            {
                for(int d = 0 ; d < 4; d++)
                    {
                        int ty = r+dy[d];
                        int tx = c+dx[d];
                        if(ty>=1 && ty <=N && tx >=1 && tx <=N)
                            map_adj[ty][tx]++;
                    }
            }
        }
    
    int max_val = 0;
    vector<vector<int>> max_adj_cor;
    for(int r = 1; r <=N ; r++)
        for(int c = 1; c <= N ; c++)
        {
            if(map_class[r][c]!=0)
                continue;
            else if(max_val> map_adj[r][c])
                continue;
            else if(max_val == map_adj[r][c])
                max_adj_cor.push_back({r,c});
            else
                {
                    max_val = map_adj[r][c];
                    max_adj_cor = {{r,c}};
                }
        }
    return max_adj_cor;
}

vector<vector<int>> test_two_three(vector<vector<int>> cors)
{
    for(auto& cor : cors)
    {
        int adj_empty_cnt = 0;
        for(int d = 0 ; d < 4 ; d++)
        {
            int ty = cor[0]+dy[d];
            int tx = cor[1]+dx[d];
            if(ty>=1 && ty <=N && tx >=1 && tx <=N && map_class[ty][tx] ==0)
                    adj_empty_cnt++;
        }
        cor.push_back(adj_empty_cnt);
    }
    sort(cors.begin(),cors.end(),mysort2);
    return cors;
}

int get_ans(unordered_map<int, vector<int>> pref_map)
{
    int ans = 0;
    for(int r = 1 ; r <=N; r++)
        for(int c = 1; c <=N; c++)
        {
            int e =0;
            vector<int> pref = pref_map.find(map_class[r][c]) ->second;
            for(int d = 0 ; d < 4 ; d++)
            {
                int ty = r+dy[d];
                int tx = c+dx[d];
                if(ty>=1 && ty <=N && tx >=1 && tx <=N && find(pref.begin(), pref.end(),map_class[ty][tx]) != pref.end())
                    e++;
                        
            }
            int add = e==0?0:pow(10,e-1);
            ans += add;
        }
    return ans;
}

void solve()
{
    cin>>N;
    unordered_map<int, vector<int>> pref_map;
    for(int tc = 1 ; tc <=pow(N,2) ; tc++)
    {
        //init
        int idx;
        vector<int> pref(4,0);
        cin>>idx;
        for(int i = 0 ; i < 4 ; i++)
            cin>>pref[i];
        pref_map[idx] = pref;
        //test one
        vector<vector<int>> max_adj_pref_cor = test_one(idx, pref);

        //if done
        if(max_adj_pref_cor.size() ==1 )
            {
                int r = max_adj_pref_cor[0][0];
                int c = max_adj_pref_cor[0][1];
                map_class[r][c] = idx;
                continue;
            }
        
        //test_two_three;
        vector<vector<int>> max_adj_empty_cor = test_two_three(max_adj_pref_cor);
        int r = max_adj_empty_cor[0][0];
        int c = max_adj_empty_cor[0][1];
        map_class[r][c] = idx;
    }
    cout<<get_ans(pref_map);
}

int main() {
    solve();
    
    return 0;
}       