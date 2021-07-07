#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>

using namespace std;

int N,M;
vector<vector<int>> map;
vector<vector<int>> shark_beam_info;

int ans = 0;

int dy[4] = {0,1,0,-1};
int dx[4] = {-1,0,1,0};

int dy_prob[5] = {0,-1,1,0,0};
int dx_prob[5] = {0,0,0,-1,1};

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
            shark_beam_info.push_back({d,s});
        }
}

void drop()
{
        int r = (N+1)/2;
        int c = r;
        int d = 0;
        int move_cnt = 0;
        int max_move_cnt = 1;
        bool twice = true;
        
        int drop_row = r;
        int drop_col = c;
        int drop_d = 0;
        int drop_move_cnt = 0;
        int drop_max_move_cnt = 1;
        bool drop_twice = true;

        for(int idx = 0 ; idx < pow(N,2) ; idx++)
        {
            //pioneer pointers move unconditionally
            r += dy[d];
            c += dx[d];
            move_cnt ++;
            if(move_cnt == max_move_cnt)
            {
                d=(d+1)%4;
                move_cnt = 0;
                twice =!twice;
                if(twice) max_move_cnt++;
            }

            //drop pointer moves if pioneer pointer meet non zero value
            if(map[r][c]!=0)
            {
                drop_row += dy[drop_d];
                drop_col += dx[drop_d];
                drop_move_cnt ++;
                if(drop_move_cnt == drop_max_move_cnt)
                {
                    drop_d=(drop_d+1)%4;
                    drop_move_cnt = 0;
                    drop_twice =!drop_twice;
                    if(drop_twice) drop_max_move_cnt++;
                }

                //and actual drop occurs in swap method
                swap(map[drop_row][drop_col], map[r][c]);
            }
        }
}

bool is_explode()
{
        int r = (N+1)/2;
        int c = r;
        int move_cnt = 0;
        int max_move_cnt = 1;
        int twice = true;
        int d = 0;
        //explode 

        vector<vector<int>> cors;
        int cur_val = 0;
        bool is_boombed = false;
        for(int idx = 0 ; idx < pow(N,2) ; idx++)
        {
            //pointer moves
            r += dy[d];
            c += dx[d];
            move_cnt ++;

            //since all balls are droped we can break if pointer met zero
            if(map[r][c] == 0)
                break;
            if(map[r][c] == cur_val)
                cors.push_back({r,c});
            else
            {
                if(cors.size()>=4)
                {
                    is_boombed = true;
                    ans += cur_val * cors.size();
                    for(auto cor : cors)
                        map[cor[0]][cor[1]] = 0;
                }
                cors = {{r,c}};
                cur_val = map[r][c];
            }

            if(move_cnt == max_move_cnt)
            {
                d=(d+1)%4;
                move_cnt = 0;
                twice =!twice;
                if(twice) max_move_cnt++;
            }
        }
        if(is_boombed)
            return true;
        return false;
}

void transform()
{
        int r = (N+1)/2;
        int c = r;
        int d = 0;
        int move_cnt = 0;
        int max_move_cnt = 1;
        bool twice = true;
        
        int drop_row = r;
        int drop_col = c;
        int drop_d = 0;
        int drop_move_cnt = 0;
        int drop_max_move_cnt = 1;
        bool drop_twice = true;

        int cur_val = map[r][c-1];
        int cur_val_cnt = 0;
        vector<vector<int>> transformed_map(N+1, vector<int>(N+1,0));

        for(int idx = 0 ; idx < pow(N,2) ; idx++)
        {
            //pioneer pointers move unconditionally
            r += dy[d];
            c += dx[d];
            move_cnt ++;
            if(move_cnt == max_move_cnt)
            {
                d=(d+1)%4;
                move_cnt = 0;
                twice =!twice;
                if(twice) max_move_cnt++;
            }

            
            if (map[r][c] == cur_val)
                cur_val_cnt++;
            //drop pointer moves if pioneer pointer meet non-consecutive value
            else
            {
                drop_row += dy[drop_d];
                drop_col += dx[drop_d];

                //break if out of board
                if(drop_row == 1 && drop_col == 0)
                    break;

                drop_move_cnt ++;
                if(drop_move_cnt == drop_max_move_cnt)
                {
                    drop_d=(drop_d+1)%4;
                    drop_move_cnt = 0;
                    drop_twice =!drop_twice;
                    if(drop_twice) drop_max_move_cnt++;
                }

                //and actual transform occurs in transformed_map
                transformed_map[drop_row][drop_col] = cur_val_cnt;

                // one more drop pointer move
                drop_row += dy[drop_d];
                drop_col += dx[drop_d];

                //break if out of board
                if(drop_row == 1 && drop_col == 0)
                    break;

                drop_move_cnt ++;
                if(drop_move_cnt == drop_max_move_cnt)
                {
                    drop_d=(drop_d+1)%4;
                    drop_move_cnt = 0;
                    drop_twice =!drop_twice;
                    if(drop_twice) drop_max_move_cnt++;
                }
                transformed_map[drop_row][drop_col] = cur_val;

                cur_val = map[r][c];
                cur_val_cnt = 1;
            }
            if (map[r][c] == 0)
                break;
        }
        map = transformed_map;
}

void solve()
{
    vector<int> vi;
    for(int i = 0 ; i < pow(N,2)-10; i++)
        vi.push_back(i+1);
    
    int shark_row = (N+1)/2;
    int shark_col = shark_row;

    for(auto sb : shark_beam_info)
    {
        //shark beam
        for(int dist = 1 ; dist<= sb[1]; dist++)
            map[shark_row + dist*dy_prob[sb[0]]][shark_col + dist*dx_prob[sb[0]]] = 0;
        drop();

        while(1)
        {
            if(!is_explode())
                break;
            drop();
        }
        //transform
        transform();
    }
    cout<<ans;
}


int main() {
    input();
    solve();

    return 0;
}       