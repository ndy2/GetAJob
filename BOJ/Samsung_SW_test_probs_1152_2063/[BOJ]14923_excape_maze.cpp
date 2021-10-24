#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N,M;
int Hx,Hy;
int Ex,Ey;

bool map[1001][1001];
bool visited[2][1001][1001];

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

typedef struct _info{
    int r,c;
    int cnt;
    bool wand;
}info;

void input(){
    cin>>N>>M;
    cin>>Hx>>Hy;
    cin>>Ex>>Ey;
    for(int r = 1 ; r<=N ; r++)
        for(int c= 1 ; c <=M ; c++)
            cin>>map[r][c];
}

void solve(){
    int ans = -1;
    queue<info> q;
    info init = {Hx,Hy,0,false};
    visited[0][Hx][Hy]= true;
    q.push(init);

    while(!q.empty()){
        info pos = q.front();
        q.pop();
        
        if(pos.wand&& visited[0][pos.r][pos.c])
            continue;
        if(pos.r==Ex && pos.c==Ey){
            ans = pos.cnt;
            break;
        }
        
        // printf("From %d %d %d %d\n",pos.r,pos.c,pos.cnt,pos.wand);

        for(int d= 0 ;d < 4;  d++){
            int ty = pos.r+dy[d];
            int tx = pos.c+dx[d];
            if(ty>=1 && ty<=N && tx >=1 && tx <=M){
                if(pos.wand) // 완드 사용
                {
                    if(!map[ty][tx]&& !visited[0][ty][tx] && !visited[1][ty][tx]){
                        visited[1][ty][tx] = true;
                        q.push({ty,tx,pos.cnt+1,true});
                        // printf("c1 visit %d %d %d %d\n",ty,tx,pos.cnt+1,true);
                    }
                }
                else{       //안씀
                    if(map[ty][tx]) // 벽
                    {
                        if(!visited[1][ty][tx]){
                            visited[1][ty][tx] = true;
                            q.push({ty,tx,pos.cnt+1,true});                       
                            // printf("c2 visit %d %d %d %d\n",ty,tx,pos.cnt+1,true);
                        }
                    }
                    else{
                        if(!visited[0][ty][tx]){
                            visited[0][ty][tx] = true;
                            visited[1][ty][tx] = true;
                            q.push({ty,tx,pos.cnt+1,false});                       
                            // printf("c3 visit %d %d %d %d\n",ty,tx,pos.cnt+1,true);
                        }
                    }
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