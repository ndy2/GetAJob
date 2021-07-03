#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

void print_bd(vector<vector<int>> board, int N)
{
    for(int i = 0 ; i < N ; i ++)
    {
        for(int j = 0 ; j < N ; j ++)
            cout<<board[i][j]<<" ";
        cout<<endl;
    }

    cout<<endl;
}

int max_bd(vector<vector<int>> board, int N)
{
    int max = 0;
    for(int i = 0 ; i < N ; i ++)
        for(int j = 0 ; j < N ; j ++)
            max = max < board[i][j] ? board[i][j] : max;

    return max;
}

vector<vector<int>>  rotate_bd_clw(vector<vector<int>> board, int rotate, int N)
{
    if(rotate == 0 )
        return board;
    else
    {
        vector<vector<int>> r_board (N, vector<int>(N));
        switch (rotate)
        {
        case 90:
            for(int i = 0 ; i < N ; i ++)
                for(int j = 0 ; j < N ; j ++)
                    r_board[j][N-i-1] = board[i][j];
            break;
        
        case 180 :
            for(int i = 0 ; i < N ; i ++)
                for(int j = 0 ; j < N ; j ++)
                    r_board[N-i-1][N-j-1] = board[i][j];
            break;
        case 270 :
            for(int i = 0 ; i < N ; i ++)
                for(int j = 0 ; j < N ; j ++)
                    r_board[N-j-1][i] = board[i][j];
        default:
            break;
        }
       return r_board;
    }
}

vector<vector<int>> stack_bd_left(vector<vector<int>> board, int N)
{
    vector<vector<int>> s_board (N, vector<int>(N));
    vector<int> s_bd_row ;
    for(int i = 0 ; i < N  ;i ++)
    {
        int hist = 0,cur;
        for(int j = 0 ; j < N ; j ++)
        {
            if(board[i][j] == 0)
            {

            }
            else
            {
                cur = board[i][j];
                if(cur == hist)
                {
                    s_bd_row.push_back(cur+cur);
                    hist = 0;
                }
                    
                else if (cur != hist && hist != 0)
                    {
                        s_bd_row.push_back(hist);
                        hist = cur;
                    }
                else
                {
                    hist = cur;
                }
                    
            }
            
        }
        if (hist != 0 )
                s_bd_row.push_back(hist);
            int l = s_bd_row.size();
            for(int i = 0 ; i < N-l ; i ++)
                s_bd_row.push_back(0);

            s_board[i] = s_bd_row;
            s_bd_row.clear();
    }

    return s_board;
}

int main()
{
    int N;
    cin >>N;
    int rotate[4] = {0,90,180,270};
    vector<vector<int>> board(N, vector<int>(N));
    vector<vector<int>> save_bd_i (N, vector<int>(N));
    vector<vector<int>> save_bd_j (N, vector<int>(N));
    vector<vector<int>> save_bd_k (N, vector<int>(N));
    vector<vector<int>> save_bd_l (N, vector<int>(N));
    vector<vector<int>> save_bd_m (N, vector<int>(N));

    for(int i = 0 ; i < N ; i ++)
        for(int j = 0 ; j < N ; j ++)
            cin >> board[i][j];
    
    int maxi = 0;
    int c;
    bool debug = false;
    save_bd_i = rotate_bd_clw(board,0,N);
    for(int i = 0 ; i < 4 ; i ++)
    {
        board = rotate_bd_clw(board, rotate[i], N);
        board = stack_bd_left(board,N);
        if(debug) print_bd(board,N);
        save_bd_j = rotate_bd_clw(board,0,N);
        for(int j = 0 ; j < 4 ; j ++)
        {
            board = rotate_bd_clw(board, rotate[j], N);
            board = stack_bd_left(board,N);
             if(debug) print_bd(board,N);
            save_bd_k = rotate_bd_clw(board,0,N);
            for(int k = 0 ; k < 4 ; k ++)
            {
                board = rotate_bd_clw(board, rotate[k], N);
                board = stack_bd_left(board,N);
        if(debug) print_bd(board,N);
                save_bd_l = rotate_bd_clw(board,0,N);
                for(int l = 0 ; l < 4 ; l ++)
                {
                    board = rotate_bd_clw(board, rotate[l], N);
                    board = stack_bd_left(board,N);
        if(debug) print_bd(board,N);
                    save_bd_m = rotate_bd_clw(board,0,N);
                            for(int m = 0 ; m < 4 ; m ++)
                            {
                                board = rotate_bd_clw(board, rotate[m], N);
                                board = stack_bd_left(board,N);
        if(debug) print_bd(board,N);

                                c= max_bd(board,N);
                                if(debug) printf("c :  %d\n", c);
                                maxi = max(maxi,c);
                                if(debug) printf("m : %d\n", m);
                                 board = rotate_bd_clw(save_bd_m,0,N);
                            }
                    board = rotate_bd_clw(save_bd_l,0,N);
                }
                board = rotate_bd_clw(save_bd_k,0,N);
            }
            board = rotate_bd_clw(save_bd_j,0,N);
        }
        board = rotate_bd_clw(save_bd_i,0,N);
    }
    printf("%d\n",maxi);
}