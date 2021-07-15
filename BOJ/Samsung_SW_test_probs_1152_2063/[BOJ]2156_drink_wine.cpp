#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dp[3][10001];

int main()
{
    int N,first;
    cin>>N;
    cin>>first;

    dp[1][1] = first;
    int cur_val;
    for(int i = 2;  i<= N ; i++)
    {
        cin>>cur_val;
        dp[0][i] = max(max(dp[0][i-1],dp[1][i-1]),dp[2][i-1]);
        dp[1][i] = dp[0][i-1] + cur_val;
        dp[2][i] = dp[1][i-1] + cur_val;
    }
    cout<<max(max(dp[0][N],dp[1][N]),dp[2][N]);
}