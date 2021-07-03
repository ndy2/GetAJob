#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <set>

using namespace std;



int main()
{
    int n,k;
    cin>>n>>k;
    set<int> coins_set;
    vector<int> coins;
    int v;
    for(int i = 0 ; i < n ; i++)
        {
            cin>>v;
            if(v<=10000)
                coins_set.insert(v);
        }
    for(auto s : coins_set)
        coins.push_back(s);
    sort(coins.begin(), coins.end());
    
    n = coins.size();
    vector<int> dp(k+1,-1);
    int t = coins[0];
    dp[0] = 0;
    dp[t] = 1;
    for(int i = t+1; i<=k ; i++)
    {
        vector<int> cands;
        for(auto c : coins)
        {
            if(i-c>=0 && dp[i-c]!=-1)
                cands.push_back(dp[i-c]+1);
        }
        if(!cands.empty())
            dp[i] = *min_element(cands.begin(), cands.end());
    }
    cout<<dp[k];
}