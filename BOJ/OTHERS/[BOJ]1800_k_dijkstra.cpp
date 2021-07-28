#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define INF 987654321
using namespace std;

int N,P,K;
int dp[1001][1001];

typedef struct info{
    int idx,len;
}info;

struct compare{
    bool operator()(info a, info b){
        return a.len>b.len;
    }
};

void init_dp()
{
    for(int k = 0 ; k <=K ; k++)
    {
        for(int idx = 2 ; idx<= N ; idx++)
            dp[k][idx] = INF;
    }
}

int main()
{
    cin>>N>>P>>K;
    init_dp();
    vector<vector<int>> edges[1001];
    int f,t,l;
    for(int i = 0 ; i < P ; i++)
    {
        cin>>f>>t>>l;
        edges[f].push_back({t,l});
        edges[t].push_back({f,l});
    }
    
    for(int k = 0 ; k <= K ; k++)
    {
        priority_queue<info, vector<info>, compare> pq;
        pq.push({1,0});
        
        while(!pq.empty())
        {
            info pos = pq.top();
            pq.pop();

            if(dp[k][pos.idx] < pos.len) continue;
            for(int i = 0 ; i < edges[pos.idx].size(); i++)
            {
                int next_idx = edges[pos.idx][i][0];
                int next_dist = min(dp[k][next_idx], max(dp[k][pos.idx],edges[pos.idx][i][1]));
                if(k!=0)
                    next_dist = min(next_dist, dp[k-1][pos.idx]);
                if(next_dist < dp[k][next_idx])
                    {
                        dp[k][next_idx] = next_dist;
                        pq.push({next_idx, next_dist});
                    }
            }
        }
    }
    int ans = dp[K][N]==INF?-1:dp[K][N];
    printf("%d",ans);
}