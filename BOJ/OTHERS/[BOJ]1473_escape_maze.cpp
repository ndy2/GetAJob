#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;


int N,M;
unordered_map<char,char> rotate = {{'A','A'},{'B','B'},{'C','D'},{'D','C'}};

void doRotate(int y, int x){
    for(int c = 0 ; c < M ; c++)
        map[y][c] = rotate[map[y][c]];
        
    for(int r = 0 ; r < N ; r++)
        map[r][x] = rotate[map[r][x]];
}

//map
char map[7][7];

void input(){
    cin>>N>>M;
    for(int r= 0 ;r < N ; r++){
        string line;
        cin>>line;
        for(int c= 0 ;c < M ; c++){
            map[r][c] = line[c];
        }
    }
}

typedef struct _info{
    int r,c;
    int cnt;
    vector<vector<bool>> visited;
}info;

info getInit(){
    info init = {0,0,0};
    init.visited = vector<vector<bool>>(N,vector<bool>(M,false));
    return init;
}

void solve(){
    info init = getInit();
    queue<info> q;
    q.push(init);

    while(!q.empty()){
        info pos = q.front();
        q.pop();

        // 1. if()

    }
}

int main(){
    input();
    solve();
}