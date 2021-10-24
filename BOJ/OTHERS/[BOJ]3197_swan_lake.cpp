#include <iostream>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

int R,C;
bool map[1500][1500];
bool visited[1500][1500];
bool next_map[1500][1500];

vector<vector<int>> swanCor;

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

typedef struct _info{
    int r,c;
}info;

bool isDone(){
    vector<int> from = swanCor[0];
    vector<int> to = swanCor[1];

    queue<info> q;
    q.push({from[0],from[1]});
    visited[from[0]][from[1]] = true;
    while(!q.empty()
    ){
        info pos = q.front();
        q.pop();
        if(pos.r == to[0] && pos.c == to[1])
            return true;
        
        for(int d= 0 ;d < 4 ; d++){
            int ty = pos.r+dy[d];
            int tx = pos.c+dx[d];
            if(ty>=0 && ty<R && tx >=0 && tx<C && !visited[ty][tx] && !map[ty][tx]){
                visited[ty][tx] = true;
                q.push({ty,tx});
            }
        }
    }
    return false;
}

void iceMelting(){
    for(int r = 0 ;r < R ; r ++){
        for(int c= 0 ; c < C ; c++){
            bool remain;
            if(!map[r][c]) 
                remain = false;
            else{
                remain = true;
                for(int d= 0 ;d < 4 ; d++){
                    int ty = r+dy[d];
                    int tx = c+dx[d];
                    if(ty>=0 && ty<R && tx >=0 && tx<C && !map[ty][tx]){
                        remain=false;
                        break;
                    }
                }
            }
            next_map[r][c] = remain;
        }
    }
    
    memcpy(map,next_map,sizeof(map));
    memset(next_map,false,sizeof(next_map));
}

int main(){
    cin>>R>>C;
    for(int r = 0; r < R ; r++){
        string line;
        cin>>line;
        for(int c= 0 ; c < C ; c++){
            if(line[c] == 'L') swanCor.push_back({r,c});
            map[r][c] = (line[c]=='X');
        }
    }

    int days =0;
    while(!isDone()){
        memset(visited,false,sizeof(visited));
        iceMelting();    
        days+=1;
    }   
    cout<<days;
}