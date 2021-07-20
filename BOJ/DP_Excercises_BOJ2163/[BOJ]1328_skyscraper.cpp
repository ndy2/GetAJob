#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

long long dp[101][101][101];

void init_dp(int N, int L, int R)
{
    dp[1][1][1] = 1;
    for(int n = 2 ; n <=N ; n++)
        for(int l = 1 ; l <= n ; l++)
            for(int r = 1; r <= n ; r++)
                dp[n][l][r] = (dp[n-1][l-1][r] + dp[n-1][l][r-1] + (n-2)*dp[n-1][l][r]) % 1000000007;
}

int main()
{
    int N,L,R;
    cin>>N>>L>>R;
    init_dp(N,L,R);
    cout<<dp[N][L][R];
}