#include <iostream>
#include <vector>

using namespace std;

//0 : Empty, 10 : Wall, 11 : cleaned
int board[50][50];

int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};


void print_board(int N, int M,int r, int c, int d)
{
    printf("\n");
    cout<<r<<" "<<c<<" "<<d<<endl;
    for(int i = 0 ; i < N ; i ++ )
    {
        for(int j = 0 ; j < M ; j ++)
                printf("%3d ", board[i][j]);
        printf("\n");
    }
    printf("\n");
        
}


int rotate(int d)
{
    return (d+3)%4;
}

int sum4(int r, int c)
{
    return board[r+dy[0]][c+dx[0]] + board[r+dy[1]][c+dx[1]] + board[r+dy[2]][c+dx[2]] +board[r+dy[3]][c+dx[3]];
}

int main() {
    int val;
    int ans = 0;
    int N,M,r,c,d;
    cin>>N>>M>>r>>c>>d;
    for(int i = 0 ; i < N ; i ++)
        for(int j = 0 ; j < M ; j ++)
        {
            cin>>val;
            board[i][j] = val * 10;
        }
            
    while(1)
    {
        print_board(N,M,r,c,d);
        if(board[r][c] == 0)
        {
            board[r][c] = 11;
            ans +=1;
        }
        else
        {
            if(board[r+dy[rotate(d)]][c+dx[rotate(d)]] == 0)
                {
                    d = rotate(d);
                    r +=dy[d]; c +=dx[d];
                }
            else if(sum4(r,c) >=40)
                {
                    if(board[r-dy[d]][c-dx[d]]!=10)
                        {r-=dy[d]; c-=dx[d];}
                    else
                        break;
                }
            else if(board[r+dy[rotate(d)]][c+dx[rotate(d)]] >=10)
                d = rotate(d);
        }
    }

    cout<<ans<<endl;
}       