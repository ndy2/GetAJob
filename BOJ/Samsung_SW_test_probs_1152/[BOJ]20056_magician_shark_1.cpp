#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N,M,K;

//vector<int> : firball idx map
vector<int> map[51][51];

//vector<int> fireball : r,c,m,s,d idx;
vector<vector<int>> fireballs;

//dy,dx
int dy[8] = {-1,-1,0,1,1,1,0,-1};
int dx[8] = {0,1,1,1,0,-1,-1,-1};

void input()
{
    cin>>N>>M>>K;

    int r,c,m,s,d;
    for(int idx = 0 ; idx<M; idx++)
    {
        cin>>r>>c>>m>>s>>d;
        fireballs.push_back({r,c,m,s,d,idx});
    }
}

void init_fb_map()
{
    for(auto fb : fireballs)
    {
        map[fb[0]][fb[1]].push_back(fb[4]);
    }
}

// void print_fb(int i,vector<vector<int>>fbv)
// {
//     printf("call i : %d\n",i);
//     printf("  r  c  m  s  d  idx\n");
//     for(auto fb : fbv)
//     {
//         int nr = fb[0] + fb[3] * dy[fb[4]];
//         int nc = fb[1] + fb[3] * dx[fb[4]];
        
//         if(nr > N)   nr = nr%N;
//         if(nr < 1)   nr = N - abs(nr) % N;
//         if(nc > N)   nc = nc%N;
//         if(nc < 1)   nc = N - abs(nc) % N;
//         printf("%3d%3d%3d%3d%3d%3d    -> %3d%3d\n",fb[0],fb[1],fb[2],fb[3],fb[4],fb[5], nr,nc);
    
//     }
        
//     printf("\n\n\n\n\n");
// }

//                       0 1 2 3 4 5 
//vector<int> fireball : r,c,m,s,d idx;
void move_fireball(int call)
{    
    vector<int> map_update[51][51];
    vector<vector<int>> fireballs_update;
    //step 1;
    for(auto &fb : fireballs)
    {   
        int nr = fb[0] + fb[3] * dy[fb[4]];
        int nc = fb[1] + fb[3] * dx[fb[4]];
        
        if(nr > N)   nr = nr%N;
        if(nr < 1)   nr = N - abs(nr) % N;
        if(nc > N)   nc = nc%N;
        if(nc < 1)   nc = N - abs(nc) % N;

        map_update[nr][nc].push_back(fb[5]);
    }

    //step 2;
    //                       0 1 2 3 4 5 
    //vector<int> fireball : r,c,m,s,d idx;
    int fb_idx = 0;
    vector<int> map_update_move[51][51];
    for(int row = 1 ; row<=N ; row++)
        for(int col =1 ; col<=N; col++)
        {
            if(map_update[row][col].empty())
                continue;
            else if(map_update[row][col].size() ==1)
            {
                vector<int> orig_fb = fireballs[map_update[row][col][0]];
                orig_fb[0] = row;
                orig_fb[1] = col;
                orig_fb[5] = fb_idx;
                vector<int> fb = orig_fb;
                map_update_move[fb[0]][fb[1]].push_back(fb_idx);
                fireballs_update.push_back(fb);
                fb_idx++;
            }
            else{
                vector<int> combine_fb_idx = map_update[row][col];
                vector<int> combined_fb;
                int cn = combine_fb_idx.size();
                int mass = 0;
                int speed = 0;
                int dir_cal_is_odd =1, dir_cal_is_even =1;
                bool is_all_odd = true, is_all_even = true;
                vector<int> combined_dir;
                int dir;
                for(int ci = 0 ; ci<cn; ci++)
                {
                    mass +=fireballs[combine_fb_idx[ci]][2];
                    speed +=fireballs[combine_fb_idx[ci]][3];
                    is_all_odd *= fireballs[combine_fb_idx[ci]][4]%2==1;
                    is_all_even*=fireballs[combine_fb_idx[ci]][4]%2==0;
                }
                //                       0 1 2 3 4 5 
                //vector<int> fireball : r,c,m,s,d idx;
                mass /=5;
                if(mass == 0) continue;
                speed /=cn;
                if(is_all_odd||is_all_even) combined_dir = {0,2,4,6};
                else combined_dir = {1,3,5,7};

                for(int i = 0 ; i <4; i++)
                {
                    vector<int> new_fb = {row,col,mass,speed,combined_dir[i],fb_idx};
                    map_update_move[row][col].push_back(fb_idx);

                    fb_idx++;

                    fireballs_update.push_back(new_fb);
                }

            }
        }
        // print_fb(call,fireballs);
        fireballs = fireballs_update;

        copy(&map_update_move[0][0], &map_update_move[0][0]+ 51*51 , &map[0][0]);
        // map = map_update_move;
}

int fb_mass_sum()
{
    int mass = 0;
    for(auto fb : fireballs)
        mass+=fb[2];
    return mass;
}

void solve()
{
    int move_idx;
    for(move_idx = 0 ; move_idx<K; move_idx++)
    {
        move_fireball(move_idx);
    }
    int ans = fb_mass_sum();
    // print_fb(move_idx,fireballs);

    cout<<ans;
}

int main()
{
    input();
    solve();
    
    return 0;
}