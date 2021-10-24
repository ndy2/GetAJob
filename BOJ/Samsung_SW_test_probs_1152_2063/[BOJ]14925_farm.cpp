#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N,M;
bool map[1001][1001];
int dp[1001][1001];

int ans = 0;

void input(){
    cin>>N>>M;
    for(int r= 1 ; r<=N ; r++)
        for(int c = 1; c<=M ; c++){
            int i;
            cin>>i;
            map[r][c] = i;
        }
            
}

int getMin(int a, int b, int c){
    return min(min(a,b),c);
}

void solve(){
    for(int r= 1 ; r<=N ; r++)
        for(int c= 1 ; c<=M ; c++){
            if(!map[r][c]){
                int cur = 1+getMin(dp[r][c-1], dp[r-1][c], dp[r-1][r-1]);
                dp[r][c] = cur;
                
                ans = max(cur, ans);
                }
        }

    cout<<ans;
}

int main(){
    input();
    solve();
}