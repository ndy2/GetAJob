#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <queue>

using namespace std;

int N,M;
int map[50][50];
int visited[50][50];
int blank_cnt;
vector<vector<int>> virus_pos;

int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

void input()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(nullptr);
    int p;
    blank_cnt = 0;
    cin>>N>>M;
    for(int r= 0 ;r < N; r++)
        for(int c = 0 ; c < N ; c++)
           
           {
               cin>>p;
               map[r][c] =p;
               if(p==0)
                    blank_cnt++;
               else if(p == 2)
                    virus_pos.push_back({r,c});

           } 
}


void solve()
{
    int num_virus = virus_pos.size();
    vector<int> idx(num_virus,0);
    for(int i = num_virus-M; i<num_virus; i++)
        idx[i] =1;
    int ans = 1e9;
    do{
        //init
        queue<vector<int>> qvp;
        memset(visited, 0, sizeof(visited));
        
        //set virus using idx
        for(int i = 0 ; i < num_virus; i++)
            if(idx[i] == 1)
                {
                    vector<int> pos = virus_pos[i];
                    pos.push_back(0);
                    qvp.push(pos);
                }
        int time_stamp = 0;
        int infection = 0;
        while(!qvp.empty())
        {
            vector<int> vp = qvp.front();
            qvp.pop();
            if(visited[vp[0]][vp[1]]) continue;
            visited[vp[0]][vp[1]] = true;
            int time = vp[2];
            if(time_stamp != time && infection == blank_cnt)
                break;
            
            if(map[vp[0]][vp[1]] == 0) infection++;
            for(int d = 0 ; d< 4 ; d++)
            {
                int ty = vp[0]+dy[d];
                int tx = vp[1]+dx[d];
                if(ty>=0 && ty<N && tx>=0 && tx<N && !visited[ty][tx] && map[ty][tx]!=1)
                    qvp.push({ty,tx,time+1});
            }

            time_stamp = time;
        }
        time_stamp = infection == blank_cnt?time_stamp:1e9;
        ans =min(ans, time_stamp);
    }while(next_permutation(idx.begin(),idx.end()));
    if(ans ==1e9) ans = -1;
    cout<<ans;
}


int main() {
    input();
    solve();

    return 0;
}       