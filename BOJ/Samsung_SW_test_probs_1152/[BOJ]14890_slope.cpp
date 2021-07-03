#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> rotate_90(vector<vector<int>> board, int N)
{
    vector<vector<int>> rotated(N, vector<int>(N,0));

    for(int r = 0 ; r < N ; r++)
        for(int c = 0 ; c < N ; c++)
            rotated[r][c] = board[N-c-1][r];
    return rotated;
}

bool is_road(vector<int> way, int L)
{
    int cur_height = way[0];
    int gap;
    vector<bool> set_slope(way.size(),0);
    for(int i = 0 ; i < way.size() ; i++)
    {
        if(cur_height != way[i])
        {
            gap = way[i] - cur_height;
            if(!(gap==1 || gap==-1))
                return false;
            if(gap==1)
            {
                if(i-L <0)
                    return false;
                for(int idx = 0 ; idx<L ; idx++)
                {
                    if(set_slope[i-idx-1])
                        return false;
                    if(way[i-idx-1]!=cur_height)
                        return false;
                }
            }
            else
            {
                if(i+L > way.size())
                    return false;
                for(int idx = 0 ; idx < L ; idx++)
                    {
                        set_slope[i+idx] = true;
                        if(way[i+idx]!=way[i])
                            return false;
                    }
            }
            cur_height = way[i];
        }   
    }

    return true;
}

int main() {
    int N,L;
    cin>>N>>L;
    vector<vector<int>> board(N, vector<int>(N,0));

    for(int r = 0 ; r < N ; r++)
        for(int c = 0 ; c < N ; c++)
            cin>>board[r][c];
    
    vector<vector<int>> r_board = rotate_90(board, N);

    int ans = 0;
    for(auto r : board)
        if(is_road(r,L))
            ans+=1;

    for(auto r : r_board)
        if(is_road(r,L))
            ans+=1;

    cout<<ans;
}       