#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int N;
int board[1001];
int dp[1001];

void input()
{
    cin>>N;
    for(int i= 1 ;i <=N ; i++)
        cin>>board[i];
}
void solve()
{
    memset(dp,-1,sizeof(dp));
    dp[1] = 0;
    for(int i = 1 ; i <= N ; i++)
        for(int j = i ; j <= i+board[i]; j++)
            if(dp[i] == -1)
                continue;
            else if(dp[j] == -1)
                dp[j] = dp[i]+1;
            else
                dp[j] = min(dp[i]+1,dp[j]);
    cout<<dp[N];
}

int main()
{
    input();
    solve();

    return 0;
}