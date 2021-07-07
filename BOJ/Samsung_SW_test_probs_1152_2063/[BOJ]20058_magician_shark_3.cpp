#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>


using namespace std;

int N,Q;
vector<vector<int>> map;
int M;
vector<int> arrL;
void input()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(nullptr);
    cin>>N>>Q;
    M = pow(2,N);
    vector<vector<int>> map_save (M, vector<int>(M,0));
    map = map_save;
    for(int r= 0 ; r <M; r++)
        for(int c = 0; c <M; c++)
            cin>>map[r][c];
    
    int l;
    for(int i = 0 ; i < Q ; i++)
        {
            cin>>l;
            arrL.push_back(l);
        }
}

int dy[4] = {1,0,-1,0};
int dx[4] = {0,1,0,-1};

void print_vvi(vector<vector<int>> vvi)
{
    for(auto row : vvi)
    {
        for(auto col : row)
        {
            cout<<col<<" ";

        }
        cout<<endl;
    }
    cout<<endl;
}

vector<vector<int>> transpose(vector<vector<int>> mat)
{
    int M = mat.size();
    int N = mat[0].size();

    vector<vector<int>> mat_T (N, vector<int>(M,0));
    for(int r= 0 ; r < N ; r++)
        for(int c = 0 ; c < M ; c++)
            mat_T[r][c] = mat[c][r];

    return mat_T;
}

//good
void rotate_square(vector<vector<int>> &slice)
{
    int size = slice.size();
    int t= size/2;

    for(int s = 0 ; s < t ; s++)
    {
        bool done = false;
        queue<int> q;
        int y = s, x = s;
        q.push(slice[y][x]);
        int d = 0;
        int move_cnt = 0;
        int move_max ;
        while(1)
        {
            int p = q.front();
            q.pop();

            int move_max = size - 2*s -1;
            int ty = y+ dy[d];
            int tx = x+ dx[d];
            q.push(slice[ty][tx] );
            slice[ty][tx] = p;
            move_cnt +=1;
            y = ty;
            x = tx;
            if(move_cnt == move_max)
                {
                    move_cnt = 0;
                    d+=1;
                    if(d==4)
                        break;
                }
        }
    }
}



void  rotate_grid_rowwise(vector<vector<int>> &map_in, int L)
{
    int grid_len = pow(2,L);
    int grid_num = M/grid_len;

    vector<vector<int>> map_in_transpose = transpose(map_in);
    for(int r = 0 ; r <grid_num ; r++)
    {
        vector<vector<int>> slice (map_in_transpose.begin() + r*grid_len, map_in_transpose.begin() + (r+1)*grid_len);
        rotate_square(slice);
        // vector<vector<int>> slice_T = transpose(slice);
        for(int c = 0 ; c < grid_len; c++)
            map_in_transpose[r*grid_len+c] = slice[c];
    }
    map_in = transpose(map_in_transpose);
}

void rotate_grid(vector<vector<int>> &map_in, int L)
{
    int grid_len = pow(2,L);
    int grid_num = M/grid_len;

    for(int r = 0 ; r <grid_num ; r++)
    {
        vector<vector<int>> map_in_row (map_in.begin()+ r*grid_len, map_in.begin() + (r+1)*grid_len);
        rotate_grid_rowwise(map_in_row, L);

        for(int grid_r = 0 ; grid_r < grid_len ; grid_r++)
            for(int c = 0 ; c < M ; c ++)
                map_in[grid_len * r + grid_r][c] = map_in_row[grid_r][c];
    }
    
}

void test_func1()
{
    for(int i = 2 ; i <=6 ; i+=2)
    {
        vector<vector<int>> t (i,vector<int>(i,0));
        int val = 1;
        for(int r = 0 ; r < i ; r++)
            for(int c = 0 ; c < i ; c++)
                    t[r][c] = val++;

        rotate_square(t);
        print_vvi(t);
    }  
}

void test_func2()
{
    M = 8;
    vector<vector<int>> test ={{1,2,3,4,5,6,7,8},
                                {9,10,11,12,13,14,15,16}};

    rotate_grid_rowwise(test,1);
    print_vvi(test);

}

void test_func3()
{
    int L =1;
    for(int i = 4 ; i <=8 ; i+=4)
    {
        vector<vector<int>> t (i,vector<int>(i,0));
        int val = 1;
        for(int r = 0 ; r < i ; r++)
            for(int c = 0 ; c < i ; c++)
                    t[r][c] = val++;

        rotate_grid(t,L);
        print_vvi(t);
    }  
}

void solve()
{
    for(int i = 0 ; i < Q ; i ++)
        rotate_grid(map, arrL[i]);

    print_vvi(map);
}

int main() {
    input();
    // test_func1();
    // test_func2();
    // test_func3();
    solve();
    
    return 0;
}       