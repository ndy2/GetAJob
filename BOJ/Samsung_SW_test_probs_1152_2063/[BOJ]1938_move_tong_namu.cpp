#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>


using namespace std;

int N;
bool board[50][50];

//visited[0] : horizontal visited
//visited[1] : vertical visited
bool visited[2][50][50];

vector<vector<int>> init;
vector<vector<int>> dest;

void input()
{
    cin>>N;
    for(int r= 0 ;r < N ; r++)
        {
            string line;
            cin>>line;
            for(int c= 0 ;c < N ;c ++)
                {
                    if(line[c] == 'B')
                        {
                            init.push_back({r,c});
                            line[c] = '0';
                        }
                    else if(line[c] =='E')
                        {
                            dest.push_back({r,c});
                            line[c] = '0';
                        }
                    board[r][c] = line[c]-'0';
                }                
        }
}

typedef struct info{
    int y,x,cnt;
    bool is_vertical;
}info;

bool is_vertical(vector<vector<int>> cors)
{
    if(cors[0][1] == cors[1][1])
        return true;
    else
        return false;
}

bool is_valid_and_if_so_visit_one(int ty, int tx, bool is_vertical)
{
    if(ty>=0 && ty<N && tx>=0 && tx<N && !visited[is_vertical][ty][tx] && !board[ty][tx])
        {
            visited[is_vertical][ty][tx] = true;
            return true;
        }
    return false;
}

bool is_valid_and_if_so_visit_three_vert(int ty, int tx, bool is_vertical)
{
    if(ty>=1 && ty<N-1 && tx>=0 && tx<N && !visited[is_vertical][ty][tx] && !board[ty-1][tx] &&!board[ty][tx] &&!board[ty+1][tx])
        {   
            visited[is_vertical][ty][tx] = true;
            return true;
        }
    return false;
}

bool is_valid_and_if_so_visit_three_hor(int ty, int tx, bool is_vertical)
{
    if(ty>=0 && ty<N && tx>=1 && tx<N-1 && !visited[is_vertical][ty][tx] && !board[ty][tx-1] &&!board[ty][tx] &&!board[ty][tx+1])
        {   
            visited[is_vertical][ty][tx] = true;
            return true;
        }
    return false;
}

bool is_valid_and_if_so_visit_turn(int ty,int tx, bool is_vertical)
{
    if(ty>=1 && ty<N-1 && tx>=1 && tx<N-1 && !visited[!is_vertical][ty][tx])
        {   
            for(int r = -1 ; r <=1 ; r++)
                for(int c= -1; c<=1; c++)
                    if(board[ty+r][tx+c])
                        return false;
            visited[!is_vertical][ty][tx] = true;
            return true;
        }
    return false;
}

void solve()
{
    int ans = 0;

    bool init_is_vertical = is_vertical(init);
    bool dest_is_vertical = is_vertical(dest);
    visited[init_is_vertical][init[1][0]][init[1][1]] = true;

    queue<info> q;
    q.push({init[1][0],init[1][1],0,init_is_vertical});
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        if(pos.y == dest[1][0] && pos.x == dest[1][1] && pos.is_vertical == dest_is_vertical)
        {
            ans = pos.cnt;
            break;
        }
        //vertical
        if(pos.is_vertical)
        {
            //U
            int ty_u = pos.y-2;
            int tx_u = pos.x;
            if(is_valid_and_if_so_visit_one(ty_u,tx_u,true))
                q.push({ty_u+1,tx_u,pos.cnt+1,true});
            //D
            int ty_d = pos.y+2;
            int tx_d = pos.x;
            if(is_valid_and_if_so_visit_one(ty_d,tx_d,true))
                q.push({ty_d-1,tx_d,pos.cnt+1,true});
            
            //L
            int ty_l = pos.y;
            int tx_l = pos.x-1;
            if(is_valid_and_if_so_visit_three_vert(ty_l,tx_l,true))
                q.push({ty_l,tx_l,pos.cnt+1,true});

            //R
            int ty_r = pos.y;
            int tx_r = pos.x+1;
            if(is_valid_and_if_so_visit_three_vert(ty_r,tx_r,true))
                q.push({ty_r,tx_r,pos.cnt+1,true});

            //T
            int ty_t = pos.y;
            int tx_t = pos.x;
            if(is_valid_and_if_so_visit_turn(ty_t,tx_t,true))
                q.push({ty_t,tx_t,pos.cnt+1,false});
        }
        else
        {
            //U
            int ty_u = pos.y-1;
            int tx_u = pos.x;
            if(is_valid_and_if_so_visit_three_hor(ty_u,tx_u,false))
                q.push({ty_u,tx_u,pos.cnt+1,false});
            //D
            int ty_d = pos.y+1;
            int tx_d = pos.x;
            if(is_valid_and_if_so_visit_three_hor(ty_d,tx_d,false))
                q.push({ty_d,tx_d,pos.cnt+1,false});
            
            //L
            int ty_l = pos.y;
            int tx_l = pos.x-2;
            if(is_valid_and_if_so_visit_one(ty_l,tx_l,false))
                q.push({ty_l,tx_l+1,pos.cnt+1,false});

            //R
            int ty_r = pos.y;
            int tx_r = pos.x+2;
            if(is_valid_and_if_so_visit_one(ty_r,tx_r,false))
                q.push({ty_r,tx_r-1,pos.cnt+1,false});

            //T
            int ty_t = pos.y;
            int tx_t = pos.x;
            if(is_valid_and_if_so_visit_turn(ty_t,tx_t,false))
                q.push({ty_t,tx_t,pos.cnt+1,true});
        }
    }

    cout<<ans;
}

int main()
{
    input();
    solve();

    return 0;
}