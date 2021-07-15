#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int N;
int map[100][100];
bool h_[101];

int num;

vector<int> heights;

void input()
{
    cin>>N;
    int max_ = 0;
    for(int r= 0 ; r < N  ;r++)
        for(int c= 0 ;c  < N ; c++)
        {
            cin>>map[r][c];
            h_[map[r][c]] =1;
            max_ = max(max_,map[r][c]);
        }
    for(int i = 1 ; i <=max_; i++)
        if(h_[i])
            heights.push_back(i);
    num = heights.size();
}

bool visited[100][100];

int h;
int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

bool dfs(int r, int c){
    if(visited[r][c] || map[r][c]<=h)
        return false;
    visited[r][c] = true;
    for(int d= 0 ; d< 4; d++)
    {
        int ty = r+dy[d]; 
        int tx = c+dx[d];
        if(ty>=0 && ty<N && tx>=0 && tx<N && !visited[ty][tx] && map[r][c]>h)
            dfs(ty,tx);
    }
    return true;
}

//return count of safe region of region taller than h
int num_safe()
{
    int ret = 0;
    for(int r= 0 ; r <N ; r++)
        for(int c= 0 ; c < N ; c++){
                bool out =dfs(r,c);
                if(out)
                    ret++;
             }
    return ret;
}
void solve()
{
    int ans = 1;
    for(auto he : heights)
    {
        h = he;
        int out = num_safe();
        // cout<<"height : " <<he<<" out : "<<out<<endl;
        ans = max(out,ans);
        memset(visited,0,sizeof(visited));
    }
    cout<<ans;
}

int main()
{
    input();
    solve();
}