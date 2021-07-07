#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int N,M;
vector<vector<int>> map;
vector<vector<int>> move_info;
vector<vector<int>> rain_cor;

bool cloud_map[51][51];

void input()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(nullptr);
    cin>>N>>M;
    vector<vector<int>> map_save (N+1,vector<int>(N+1,0));
    for(int r = 1 ; r <=N ; r++)
        for(int c = 1; c <=N ; c++)
            cin>>map_save[r][c];
    map=map_save;
    int d,s;
    for(int i = 0 ; i < M ; i++)
        {
            cin>>d>>s;
            move_info.push_back({d,s});
        }
}

int dy[9] = {0,0,-1,-1,-1,0,1,1,1};
int dx[9] = {0,-1,-1,0,1,1,1,0,-1};

int modulo(int n)
{
    if(n>=0)
        n %=N;
    else
        {
            n = -n;
            n %=N;
            n = N-n;
        }
    return n;
}

vector<vector<int>> move_cor(vector<vector<int>> cors, int r, int c)
{
    vector<vector<int>> cors_moved;
    int stirde_r = modulo(r);
    int stride_c = modulo(c);

    for(auto cor : cors)
    {   
        
        int t_r = cor[0] + stirde_r;
        int t_c = cor[1] + stride_c;

        if(t_r >N)
           t_r -=N;
        
        if(t_c > N)
            t_c -=N;

        cors_moved.push_back({t_r, t_c});
    }
    return cors_moved;
}

void water_copy_bug(vector<int> cor)
{
    int cnt_adj_diag_water = 0;
    for(int d= 2 ; d <=8 ; d +=2)
        {
            int ty = cor[0] + dy[d];
            int tx = cor[1] + dx[d];

            if(ty>=1 && ty<=N && tx >=1 && tx<=N && map[ty][tx]>=1)
                cnt_adj_diag_water++;
        }
    map[cor[0]][cor[1]] += cnt_adj_diag_water;
}


void rain_circle(vector<int> m)
{
    vector<vector<int>> moved_map (N+1,vector<int>(N+1,0));
    int d = m[0];
    int s = m[1];

    int stride_row = dy[d] * s;
    int stride_col = dx[d] * s;

    vector<vector<int>> rain_cor_moved = move_cor(rain_cor, stride_row, stride_col); 
    for(auto cor : rain_cor_moved)
        cloud_map[cor[0]][cor[1]] = true;

    for(auto cor : rain_cor_moved)
        map[cor[0]][cor[1]]++;

    for(auto cor : rain_cor_moved)
        water_copy_bug(cor);

    rain_cor_moved.clear();

    for(int r = 1 ; r <=N ; r ++)
        for(int c= 1; c<=N; c++)
            if(!cloud_map[r][c] && map[r][c]>=2)
            {
                map[r][c]-=2;
                rain_cor_moved.push_back({r,c});
            }
                
    rain_cor = rain_cor_moved;
    memset(cloud_map,0,sizeof(cloud_map));
}

int get_ans()
{
    int ans = 0;
    for(int r= 1 ; r<=N; r++)
        for(int c = 1 ; c <=N ; c++)
                ans +=map[r][c];
    return ans;
}

void solve()
{
    rain_cor = {{N-1,1},{N-1,2}, {N,1}, {N,2}};
    for(auto m : move_info)
        rain_circle(m);
    cout<<get_ans();
}
        

int main() {
    input();
    solve();

    return 0;
}       