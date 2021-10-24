#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

int map[5][5];
bool visited[5][5];

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};
vector<int> path;
set<vector<int>> svi;

void input(){
    for(int r= 0 ; r< 5 ; r ++){
        string line;
        cin>>line;
        for(int c= 0 ; c < 5; c++){
            map[r][c] = line[c]=='S';
        }
    }
}

typedef struct _info{
    int r, c;
    int len;
    int numS;
    int numY;
}info;

bool is_prospect(info in){
    return in.numY<=3;
}

bool is_valid_cor(int r, int c){
    return r>=0&&r<5&&c>=0&&c<5;
}

void dfs(info pos){
    if(visited[pos.r][pos.c])
        return;
    
    visited[pos.r][pos.c] = true;
    path.push_back(5*pos.r+pos.c);

    if(pos.len==7){
        vector<int> inPath = path;
        sort(inPath.begin(),inPath.end());
        svi.insert(inPath);
    }
    else{
        for(int d= 0 ;d < 4; d++){
            
            info next;
            int ty = pos.r+dy[d];
            int tx = pos.c+dx[d];
            if(map[ty][tx]){
                next = {ty,tx, pos.len+1, pos.numS+1, pos.numY};
            }
            else {
                next = {ty,tx, pos.len+1, pos.numS, pos.numY+1};
            }
            if(is_valid_cor(ty,tx)&& is_prospect(next) && !visited[next.r][next.c]){
                dfs(next);
            }
        }
    }
    path.pop_back();
    visited[pos.r][pos.c] = false;
}

void solve(){
    svi.clear();
    for(int r= 0 ; r < 5; r++){
        for(int c= 0 ; c<5 ; c++){
            if(map[r][c])
                {
                    info init = {r,c, 1,1,0};
                    dfs(init);
                }
        }
    }
    cout<<svi.size();
}

int main(){
    input();
    solve();
}
