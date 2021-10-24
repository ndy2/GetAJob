#include <iostream>
#include <string.h>
#define MOD 998244354
using namespace std;

int N, M;

char map[50][50];


void input(){
    cin>>N>>M;
    for(int r= 0 ; r < N ; r++){
        string line ;
        cin>>line;
        for(int c= 0 ; c < M ; c++){
            map[r][c] = line[c];
        }
    }
}

bool is_fail(int r, int c){
    if(r+1==N || c+1 == M)
        return true;
    return !(map[r+1][c]=='#'&&
           map[r][c+1]=='#'&&
           map[r+1][c+1]=='#');
}

void set_tile(int r, int c){
    map[r][c] = map[r+1][c] = map[r][c+1] = map[r+1][c+1] = '.';
}

void solve(int tc){
    string ans = "YES";

    for(int r=  0 ;r  < N ; r++){
        for (int c = 0 ; c < M ; c++){
            if(map[r][c] == '#'){
                bool fail = is_fail(r,c);
                if(fail){
                    ans = "NO";
                    r= N; c = M;
                }
                else{
                    set_tile(r,c);
                }
            }
        }
    }

    cout<<"#"<<tc<<" "<<ans<<endl;
}

int main(){
    int T;
    cin>>T;
    for(int tc = 1; tc<=T; tc++){
        input();
        solve(tc);
        memset(map,0,sizeof(map));        
    }
}