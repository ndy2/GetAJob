#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

typedef struct odd{
int idx,r;
}odd;

typedef struct shark{
    int idx, dir, y,x;
}shark;

int N,M,K;
int map[21][21];
odd odd_map[21][21];

int map_move[21][21];


vector<vector<vector<int>>> dir_pref;
vector<int> first_dirs;
vector<shark> glb_shark_set;
vector<shark> glb_shark_set_update;

int dy[5] = {0,-1,1,0,0};
int dx[5] = {0,0,0,-1,1};

void print_map()
{
    for(int r =1 ; r <=N ; r++)
    {
        for(int c= 1 ; c <= N ; c++)
            printf("%2d", map[r][c]);
        printf("\n");
    }
    printf("\n");
}

void print_odd_map()
{
    for(int r =1 ; r <=N ; r++)
    {
        for(int c= 1 ; c <= N ; c++)
            printf("%2d%2d   ", odd_map[r][c].idx, odd_map[r][c].r);
        printf("\n");
    }
    printf("\n");
}

void input()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(nullptr);
    cin>>N>>M>>K;
    for(int r= 1 ;r <= N; r++)
        for(int c = 1 ; c <= N ; c++)
            cin>>map[r][c];

    int fd;
    first_dirs.push_back(0);
    for(int i = 1; i <=M; i++)
        {
            cin>>fd;
            first_dirs.push_back(fd);
        }

    int d1,d2,d3,d4;
    dir_pref.push_back({{{}}});
    for(int i = 1 ; i <= M ; i++)
    {
        vector<vector<int>> i_th_shark_dir_pref(5,vector<int>());
        for(int j = 1 ; j<=4; j++)
        {
            cin>>d1>>d2>>d3>>d4;
            i_th_shark_dir_pref[j] = {d1,d2,d3,d4};
        }
        dir_pref.push_back(i_th_shark_dir_pref);
    }
}

void odd_proc()
{
    for(int r = 1; r<=N ; r++)
        for(int c= 1; c<=N; c++)
        {
            if(odd_map[r][c].r>0)
            {
                odd_map[r][c].r--;
                if(odd_map[r][c].r == 0)
                    odd_map[r][c].idx = 0;
            }   
        }
            
}

void stamp_odd()
{
    for(int r = 1; r<=N ; r++)
        for(int c= 1; c<=N; c++)
            if(map[r][c]>0)
                odd_map[r][c] ={map[r][c], K};
}

void init_glb_sk_set()
{
    vector<shark> vs_dummy(M+1,{0,0,0,0});
    glb_shark_set = vs_dummy;
    glb_shark_set_update = vs_dummy;
    for(int r = 1; r<=N ; r++)
        for(int c= 1; c<=N; c++)
        {
            if(map[r][c]>0)
                glb_shark_set[map[r][c]] = {map[r][c] , first_dirs[map[r][c]], r,c};
        }
}

void init_odd_map()
{
    for(int r = 1; r<=N ; r++)
        for(int c= 1; c<=N; c++)
            odd_map[r][c] = {0,0};     
}

void conflict_clarify(vector<vector<int>> move_set, vector<shark> shark_set)
{
    
    for(int idx = 1; idx <=M ; idx++)
        {
            if(move_set[idx].empty())
                continue;
            shark s = shark_set[idx];
            int chosed_dir = move_set[idx][0];
            int ty = s.y + dy[chosed_dir];
            int tx = s.x + dx[chosed_dir];
            
            if(map_move[ty][tx] == 0)
            {
                map_move[ty][tx] =s.idx;
                glb_shark_set_update[s.idx] = {s.idx, chosed_dir, ty,tx};
            }
            else{
                shark win_shark;
                if(s.idx< map[ty][tx])
                {
                            win_shark = {s.idx, chosed_dir, ty,tx};
                            glb_shark_set_update[map[ty][tx]] = {0,0,0,0};
                            map_move[ty][tx] = win_shark.idx;
                }
                else
                    glb_shark_set_update[s.idx] = {0,0,0,0};
                
            }
        }
}

void move_sharks()
{
    //shark set clarify
    vector<shark> shark_set = glb_shark_set;
    
    //move_1 set clarify
    //move vector : only one direction
    vector<vector<int>> move_1_set(M+1, vector<int>());
    for(auto s : shark_set)
    {
        int y = s.y;
        int x = s.x;
        vector<int> pref_dir_vec = dir_pref[s.idx][s.dir];
        vector<int> move_1_vec;
        //check no odd region based on preference of shark s
        for(auto pd : pref_dir_vec)
        {
            int ty = y+dy[pd];
            int tx = x+dx[pd];
            if(ty>=1 && ty<=N && tx>=1 && tx<=N && odd_map[ty][tx].idx==0 )
                move_1_vec.push_back(pd);
        }

        move_1_set[s.idx] = move_1_vec;
    }
    
    //move_2 set clarify
    //move vector : only one direction
    vector<vector<int>> move_2_set(M+1, vector<int>());
    for(auto s : shark_set)
    {
        //for shark who has no move_1 set
        if(move_1_set[s.idx].empty())
        {
            int y = s.y;
            int x = s.x;
            vector<int> pref_dir_vec = dir_pref[s.idx][s.dir];
            vector<int> move_2_vec;
            //check its own odd
             for(auto pd : pref_dir_vec)
             {
                int ty = y+dy[pd];
                int tx = x+dx[pd];
                if(ty>=1 && ty<=N && tx>=1 && tx<=N && odd_map[ty][tx].idx==s.idx )
                    move_2_vec.push_back(pd);
            }
            move_2_set[s.idx] = move_2_vec;
        }
    }
  
    conflict_clarify(move_1_set, shark_set);
    
    conflict_clarify(move_2_set, shark_set);

    //actual move (include conflict)
    glb_shark_set = glb_shark_set_update;
    copy(&map_move[0][0], &map_move[0][0]+21*21, &map[0][0]);

    memset(map_move, 0, sizeof(map_move));
}

bool is_done()
{
    int idx = 0;
    for(auto s : glb_shark_set)
        {
            idx+=s.idx;
            if(idx>1)
                return false;
        }
    if(idx == 1)
        return true;
    return false;
}

void solve()
{
    init_odd_map();
    init_glb_sk_set();
    stamp_odd();

    int t = 0 ;
    while(1)
    {
        t++;
        // cout<<t<<endl;
        if(t>1000)
          {
              t=-1;
              break;
          }
        // print_map();
        // print_odd_map();

        move_sharks();
        odd_proc();
        stamp_odd();
    
        if(is_done())
            break;
        
    }
    cout<<t;
}


int main() {
    input();
    solve();
    return 0;
}       