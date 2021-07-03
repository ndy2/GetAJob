#include <string.h>
#include <vector>
#include <iostream>

using namespace std;

int dp[201][201];

int soln(int N, int K)
{
    if(K==1)
    {
        dp[N][K] = 1;
        return 1;    
    }
    if(K==2)
    {
        dp[N][K] = 1;
        return N+1;
    }
    if(K==3)
    {
        dp[N][K] = 1;
        return (N+1)*(N+2)/2;
    }
    else
        {
            if(dp[N][K] != -1)
                return dp[N][K];

            int ans = 0;
            for(int i = 0 ; i <= N ; i ++)
                {
                    ans+=soln(i,K-1);
                    ans = ans>= 1000000000 ? ans - 1000000000: ans;
                }
            dp[N][K] = ans;
            return ans;        
        }
    
}

int main()
{
    memset(dp,-1,sizeof(dp));

    int N,K;
    cin >>N>>K;
    
    cout<<soln(N,K);

    return 0;
}
