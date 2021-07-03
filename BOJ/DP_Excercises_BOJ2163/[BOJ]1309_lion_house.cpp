#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

int main()
{
    int N;
    cin>>N;
    vector<vector<int>> dp(3, vector<int> (N+1,0));
    dp[0][1] = 1;
    dp[1][1] = 1;
    dp[2][1] = 1;

    for(int i = 2 ; i <= N ; i++)
    {
        dp[0][i] = (dp[1][i-1] + dp[2][i-1]) % 9901;
        dp[1][i] = (dp[0][i-1] + dp[2][i-1]) % 9901;
        dp[2][i] = (dp[0][i-1] + dp[1][i-1] + dp[2][i-1]) % 9901;
    }
    cout<<(dp[0][N] + dp[1][N] + dp[2][N]) % 9901;

}