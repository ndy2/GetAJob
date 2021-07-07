#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <queue>

using namespace std;

int N;

int dy[9] = {0,-1,-1,0,1,1,1,0,-1};
int dx[9] = {0,0,-1,-1,-1,0,1,1,1};

typedef struct fish{
    int a,b;
    int r,c;
}fish;
vector<vector<fish>> s_map(4,vector<fish>(4,{0,0}));

vector<int> shark_pos = {0,0};
vector<fish> fish_vec;

typedef struct info{
    vector<vector<fish>> map;
    vector<fish> fish_vec;
    vector<int> shark_state;
    int score;
}info;

bool mysort(fish a, fish b)
{
    return a.a<b.a;
}

void swap_fish(fish *a, fish* b)
{
    fish temp;
    temp.a = a->a;
    temp.b = a->b;

    a->a = b->a;
    a->b = b->b;

    b->a = temp.a;
    b->b = temp.b;
}

void input()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(nullptr);
    int a,b;
    for(int r= 0 ;r < 4; r++)
        for(int c = 0 ; c < 4 ; c++)
           {
               cin>>a>>b;
               s_map[r][c] = {a,b,r,c};
               fish_vec.push_back({a,b,r,c});
           }
            
}

vector<fish> erase_fish_by_idx(vector<fish> vvf,int idx)
{
    vector<fish> vf;
    for(auto f : vvf)
        if(f.a != idx)
            vf.push_back(f);
    return vf;
}


void solve()
{
    int ans = 0;
    sort(fish_vec.begin(), fish_vec.end(), mysort);
    queue<info> q;
    info init;
    fish first = s_map[0][0];

    init.shark_state = {0,0,first.b};
    fish_vec.erase(fish_vec.begin() + first.a-1);
    init.fish_vec = fish_vec;
    init.score = first.a;
    s_map[0][0] = {100,100,0,0};
    init.map = s_map;

    q.push(init);
    while(!q.empty())
    {
        
        info cur_info = q.front();
        q.pop();
        vector<fish> vf = cur_info.fish_vec;
        vector<vector<fish>> vvf = cur_info.map;
        vector<int> ss = cur_info.shark_state;
         int sy = ss[0];
        int sx = ss[1];
        int ty = sy+dy[ss[2]];
        int tx = sx+dx[ss[2]];

        int cur_score = cur_info.score;
        if(!(ty>=0 && ty<4 && tx >=0 && tx<4))
            {
                ans = max(ans,cur_score);
                continue;
            }
        //fish moves
        for(int i = 0 ; i < vf.size() ; i++)
        {
            for(int r= 0 ; r < 4 ;r++)
                for(int c= 0; c < 4 ; c++)
                    if(vvf[r][c].a == vf[i].a)
                        {
                            vf[i].r = r;
                            vf[i].c = c;
                        }
            fish mf = vf[i];
            int ty = mf.r+dy[mf.b];
            int tx = mf.c+dx[mf.b];
            while((ty<0 || ty>=4 || tx <0 || tx>=4 || (ss[0]==ty&& ss[1]==tx) ))
            {
                mf.b = mf.b==8?1:(mf.b+1);
                ty = mf.r+dy[mf.b];
                tx = mf.c+dx[mf.b];
            }
            vf[i].b = mf.b;
            //물고기가 있다면
            if(vvf[ty][tx].a != 100)
            {
                vvf[mf.r][mf.c] = mf;
                swap_fish( &vvf[mf.r][mf.c], &vvf[ty][tx]);
            }//빈공간 이라면
            else
            {
                fish empty_fish = {100,100,0,0};
                vvf[mf.r][mf.c] = empty_fish;
                mf.r = ty; mf.c = tx;
                vvf[ty][tx] = mf;
            }

        }

        //create info based on possible shark moves
       

        int push_q_cnt = 0;
        while(ty>=0 && ty<4 && tx >=0 && tx<4)
        {
            //fish exists
            if(vvf[ty][tx].a != 100)
            {
                //shark state re_new
                vector<int> new_shark_state = {ty,tx,vvf[ty][tx].b};
                //score renew
                int new_score =vvf[ty][tx].a + cur_score;
                //fish vec renew
                vector<fish> new_fish_vec = erase_fish_by_idx(vf,vvf[ty][tx].a);
                //new vvf
                vector<vector<fish>> new_vvf = vvf;

                //kill ty tx fish
                new_vvf[ty][tx] = {100, 100, 0,0};
                

                info new_info = {new_vvf, new_fish_vec, new_shark_state, new_score};
                q.push(new_info);
                push_q_cnt ++;
            }
            ty +=dy[ss[2]];
            tx +=dx[ss[2]];
        }
        
        //shark dead
        if(push_q_cnt ==0)
            ans = max(ans,cur_score);
        
    }
    cout<<ans;
}


int main() {
    input();
    solve();
    return 0;
}       