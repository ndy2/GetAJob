#include <iostream>
#include <algorithm>

using namespace std;

int N,M;
int board[1001][1001];
int dp[1001][1001];

void input()
{
    cin>>N>>M;
    for(int r= 1 ;r <=N ; r++)
        for(int c= 1; c<=M ;c++)
            cin>>board[r][c];
}

void solve()
{
    dp[1][1] = board[1][1];
    for(int r = 1; r <=N ; r++)
        for(int c = 1; c<=M ; c++)
            dp[r][c] = max(max(dp[r-1][c-1], dp[r-1][c]), dp[r][c-1]) + board[r][c];
    cout<<dp[N][M];
}

int main()
{
    input();
    solve();

    return 0;
}