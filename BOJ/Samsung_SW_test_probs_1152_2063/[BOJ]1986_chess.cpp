#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N,M;
vector<vector<int>> Q;
vector<vector<int>> K;
vector<vector<int>> P;

//0 : safe, 1 : pawn, 2 : kight, 3 : queen
//9 : under attack
int board[1001][1001] ;

int dy[] = {0,-1,-1,-1,0,1,1,1};
int dx[] = {-1,-1,0,1,1,1,0,-1};

int dy_kight[] = {-1,-2,-2,-1,1,2,2,1};
int dx_kight[] = {-2,-1,1,2,2,1,-1,-2};

void print_board()
{
    for(int r = 1 ; r <=N ; r++)
    {
        for(int c= 1; c<=M; c++)
            printf("%d ", board[r][c]);
        printf("\n");
    }
    printf("\n");
}

int get_ans()
{
    int ans = 0;
    for(int r = 1 ; r <=N ; r++)
        for(int c= 1; c<=M; c++)
            if(board[r][c] ==0)
                ans++;
    return ans;
}

int main()
{
    cin>>N>>M;
    int q,k,p;
    int r,c;
    cin>>q;
    for(int i = 0 ; i < q ; i++)
        {
            cin>>r>>c;
            Q.push_back({r,c});
            board[r][c] = 3;
        }
    cin>>k;
    for(int i = 0 ; i < k ; i++)
        {
            cin>>r>>c;
            K.push_back({r,c});
            board[r][c] = 2;
        }
    cin>>p;
    for(int i = 0 ; i < p ; i++)
        {
            cin>>r>>c;
            board[r][c] = 1;
        }

    for(auto cor : Q)
    {
        for(int d = 0 ; d < 8 ; d++)
        {
            int len = 1;
            while(1)
            {
                int ty = cor[0] + len * dy[d];
                int tx = cor[1] + len * dx[d];
                if(ty<1 || ty >N || tx <1 || tx >M || board[ty][tx] >=1 &&  board[ty][tx] <=3)
                    break;
                else
                {
                    board[ty][tx] = 9;
                    len++;
                }
            }
        }
    }
    for(auto cor : K)
    {
        for(int d = 0 ; d < 8 ; d++)
        {
            int ty = cor[0] + dy_kight[d];
            int tx = cor[1] + dx_kight[d];
            if(ty<1 || ty >N || tx <1 || tx >M || board[ty][tx] >=1 &&  board[ty][tx] <=3)
                continue;
            else
                board[ty][tx] = 9;
        }
    }
    // print_board();

    cout<<get_ans();   
}