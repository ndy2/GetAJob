#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int N;
int ans;
bool visited[1001];
vector<int> permutation;

void init(){
    ans = 0;
    memset(visited, false, sizeof(visited));
    permutation = {0};
}

void input(){
    cin>>N;
    for(int i = 0 ; i < N ; i ++){
        int pi;
        cin>>pi;
        permutation.push_back(pi);
    }
}

void dfs(int i){
    if(visited[i]){
        ans +=1;
        return;
    }
    visited[i] = true;
    dfs(permutation[i]);
    
}

void solve(){
    for(int i = 1 ; i <= N ; i++){
        if(!visited[i]) dfs(i);
    }
    printf("%d\n",ans);
    
}

int main()
{
    int tc;
    cin>>tc;
    for(int t = 0 ; t < tc; t++){
        init();
        input();
        solve();
    }

}