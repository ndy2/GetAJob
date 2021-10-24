#include <iostream>
#include <queue>

using namespace std;

int K;
int W,H;
bool map[200][200];
bool visited[31][200][200];

void input(){
    cin>>K;
    cin>>W>>H;
    for(int r=0; r <H ; r++)
        for(int c= 0 ;c < W ; c++)
            cin>>map[r][c];
}

typedef struct _info{

    int r,c;
    int monkeyMove;
    int horseMove;

}info;

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

int dy_knight[8] = {-1,-2,-2,-1,1,2,2,1};
int dx_knight[8] = {-2,-1,1,2,2,1,-1,-2};

void solve(){
    queue<info> q;
    q.push({0,0,0,0});
    int ans = -1;
    while(!q.empty()){
        info pos = q.front();
        q.pop();

        if(pos.r==H-1 && pos.c==W-1){
            ans = pos.horseMove+pos.monkeyMove;
            break;
        }

        //monkey move!
        for(int d= 0 ;d < 4; d++){
            int ty = pos.r+dy[d];
            int tx = pos.c+dx[d];
            if(ty>=0 && ty<H && tx >=0 && tx <W && !visited[pos.horseMove][ty][tx] && !map[ty][tx]){
                visited[pos.horseMove][ty][tx] = true;
                q.push({ty,tx,pos.monkeyMove+1,pos.horseMove});
            }
        }

        //horse move!
        if(pos.horseMove <K){
            for(int d= 0 ; d < 8; d++){
                int ty = pos.r+dy_knight[d];
                int tx = pos.c+dx_knight[d];    
                if(ty>=0 && ty<H && tx >=0 && tx <W && !visited[pos.horseMove+1][ty][tx] && !map[ty][tx]){
                    visited[pos.horseMove+1][ty][tx] = true;
                    q.push({ty,tx,pos.monkeyMove,pos.horseMove+1});
                }
            }
        }
    }

    printf("%d",ans);
}

int main(){
    input();
    solve();
}