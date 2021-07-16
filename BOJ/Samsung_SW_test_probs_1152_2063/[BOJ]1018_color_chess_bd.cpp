#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>


using namespace std;

int N,M;
bool board[50][50];

bool WBWB_arr[8][8];
bool BWBW_arr[8][8];

void init_arrs()
{
    for(int r= 0 ; r < 8 ; r ++)
        for(int c= 0 ;c < 8 ; c++)
            {
                if(r%2 ==  c%2)
                    WBWB_arr[r][c] = true;
                BWBW_arr[r][c] =!WBWB_arr[r][c];
            }
}

int WBWB(int r, int c)
{
    int out = 0;
    for(int row = 0; row < 8 ; row++)
        for(int col = 0 ; col < 8 ;col++)
            if(WBWB_arr[row][col] != board[r+row][c+col])
                out++;
    return out;
}

int BWBW(int r, int c)
{
    int out = 0;
    for(int row = 0; row < 8 ; row++)
        for(int col = 0 ; col < 8 ;col++)
            if(BWBW_arr[row][col] != board[r+row][c+col])
                out++;
    return out;
}

int main()
{
    unordered_map<char,bool> w0b1={{'W',false}, {'B',true}};
    init_arrs();

    cin>>N>>M;
    for(int r = 0 ; r < N ; r++)
    {
        string line;
        cin>>line;
        for(int c= 0 ;c < M ;c++)
            board[r][c] = w0b1[line[c]];
    }

    int ans = 1e9;

    for(int r = 0 ; r <=N-8 ; r++)
        for(int c= 0; c <= M-8 ;c++)
        {
            int diff_wb = WBWB(r,c);
            int diff_bw = BWBW(r,c);
            ans = min(diff_wb,ans);
            ans = min(diff_bw,ans);
        }
    cout<<ans;
}