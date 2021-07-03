#include <iostream>
#include <string.h>

using namespace std;

int T,N;
int map[2][100005];
int dp[2][100005];

void input();
void solve();
void reset();


int main()
{
    cin>>T;
    for(int tc = 1 ; tc <=T ; tc++)
    {
        input();
        solve();
        reset();
    }
}

void input()
{
    
    cin>>N;
    for(int r = 0 ; r <2 ; r++)
    {
        for(int c = 0 ; c < N ; c++)
            cin>>map[r][c];
    }
 
}


void solve()
{

    dp[0][0] = map[0][0];
    dp[1][0] = map[1][0];
    dp[0][1] = dp[1][0] + map[0][1];
    dp[1][1] = dp[0][0] + map[1][1];

    for(int c = 2 ; c <N ; c++)
    {
        dp[0][c] = max(dp[1][c-1]  + map[0][c], dp[1][c-2] + map[0][c]);
        dp[1][c] = max(dp[0][c-1]  + map[1][c], dp[0][c-2] + map[1][c]);
    }

    cout<<max(dp[0][N-1], dp[1][N-1])<<endl;
}

void reset()
{
    memset(map,0,sizeof(map));
    memset(dp, 0, sizeof(dp));
}