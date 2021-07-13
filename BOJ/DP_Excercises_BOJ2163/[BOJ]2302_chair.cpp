#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

int dp[41];

void init_dp()
{
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    for(int i = 3; i <=40 ; i++)
        dp[i] = dp[i-1] + dp[i-2];
}


int main()
{
    init_dp();
    int N,M;
    cin>>N>>M;
    vector<int> pos(M+2,0);
    int prod = 1;
    pos[0] = 0;
    pos[M+1] = N+1;
    for(int i = 1 ; i <= M ; i++)
            cin>>pos[i];
    for(int i = 0 ; i<=M ; i++)
        prod*=dp[pos[i+1] - pos[i]-1];
    
    cout<<prod;

}