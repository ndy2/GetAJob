#include <iostream>

using namespace std;

int R,C;
char map[20][20];

void input(){    
    cin>>R>>C;
    for(int r= 0 ; r < R ; r++){
        string line;
        cin>>line;
        for(int c= 0 ;c  < C ;c ++){
            map[r][c] = line[c];
        }
    }
}

typedef struct _info{
    int r,c,cnt;
}info;

bool visited[20][20];
bool alphaLog[26];
int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

int ans = 1;

void dfs(info pos){
    if(visited[pos.r][pos.c])
        return;
    ans = max(ans, pos.cnt);

    visited[pos.r][pos.c] = true;
    alphaLog[map[pos.r][pos.c] - 'A'] = true;

    for(int d= 0 ; d < 4; d++){
        int ty = pos.r + dy[d];
        int tx = pos.c + dx[d];
        if(ty>=0 && ty<R && tx >= 0 && tx < C && !visited[ty][tx] && !alphaLog[map[ty][tx]-'A']){
            dfs({ty,tx,pos.cnt+1});
        }
    }

    visited[pos.r][pos.c] = false;
    alphaLog[map[pos.r][pos.c] - 'A'] = false;
}

void solve(){
    dfs({0,0,1});
    printf("%d", ans);
}

int main(){
    input();
    solve();
}