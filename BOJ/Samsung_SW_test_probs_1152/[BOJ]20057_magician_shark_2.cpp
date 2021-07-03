#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int N;
int map[500][500];

void input()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(nullptr);
    cin>>N;
    for(int r= 1 ; r <=N; r++)
        for(int c = 1 ; c <=N; c++)
            cin>>map[r][c];
    
}

int dy[4] = {0,1,0,-1};
int dx[4] = {-1,0,1,0};

//vector<int> wind : y, x, amount, 
vector<vector<vector<int>>> wind_map = 
{{{-2,0,2},
{-1,-1,10},{-1,0,7},{-1,1,1},
{0,-2,5},
{1,-1,10}, {1,0,7},{1,1,1},
{2,0,2}}};

void init_wind_map()
{
    for(int d = 1; d <4 ; d++)
    {
        vector<vector<int>> to_prev;
        vector<vector<int>> to_dir;
        
        to_prev = wind_map[d-1];
        for(auto w : to_prev)
        {
            vector<int> r_wind = w;
            r_wind[0] = -w[1];
            r_wind[1] = w[0];
            to_dir.push_back(r_wind);
        }
        wind_map.push_back(to_dir);
    }
}

void print_wind_map()
{
    for(int d = 0 ; d <4; d++)
    {
        cout<<"d : "<<d<<endl;
        for(auto w : wind_map[d])
        {
            for(auto row : w)
                    cout<<row<<" ";
            cout<<endl;
        }
            cout<<endl<<endl;

    }
}

void print_map()
{
    for(int r = 1 ; r <=N ;r++)
        {
            for(int c = 1 ; c<=N; c++)
                printf("%3d", map[r][c]);
            printf("\n");
        }
    printf("\n\n");
}

void solve()
{
    init_wind_map();
    // print_wind_map();

    int h = N/2;
    int m = h+1;
    int t_stride = 1;
    int row = m ,col = m;
    int t_row,t_col;
    int cur_stride = 0;
    int d = 0;
    bool rotate_even = true;
    bool debug = false;
    int out_map_sum = 0;
    while(1)
    {
        if(debug) printf("\n\n\n");
        if(debug) cout<<row<<" "<<col<<" "<<map[row][col]<<endl;
        t_row = row + dy[d];
        t_col = col + dx[d];
        
        int sum = map[row][col] + map[t_row][t_col];
        map[t_row][t_col] = 0;
        int percent_sum = 0;
        for(auto w : wind_map[d])
        {
            int t_wind_row = t_row + w[0];
            int t_wind_col = t_col + w[1];
            int ratio = w[2];
            int cur_amount = sum*ratio/100;
            percent_sum += cur_amount;
            
            if(t_wind_row>=1 && t_wind_row<=N && t_wind_col>=1 && t_wind_col <=N)
                map[t_wind_row][t_wind_col] += cur_amount;
            else
                out_map_sum +=cur_amount;
        }

        int alpha = sum-percent_sum;
        int alpha_row = t_row +dy[d];
        int alpha_col = t_col +dx[d];
        if(alpha_row>=1 && alpha_row<=N && alpha_col>=1 && alpha_col <=N)
                map[alpha_row][alpha_col] += alpha;
        else
                out_map_sum +=alpha;

        if(debug) printf("out sum : %d\n", out_map_sum);
        if(debug) print_map();
        cur_stride +=1;
        if(cur_stride == t_stride)
            {
                d = (d+1)%4;
                cur_stride = 0;
                rotate_even = !rotate_even;
                if(rotate_even)
                    t_stride ++;
            }
        
        row = t_row;
        col = t_col;
        if(row == 1 && col ==0)
            break;
    }

    if(debug) cout<<"final"<<endl;
    if(debug) print_map();

    cout<<out_map_sum;
}


int main() {
    input();
    solve();
    return 0;
}       