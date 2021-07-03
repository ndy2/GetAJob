#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <utility>


#define LEFT 10
#define UP 11
#define RIGHT 12
#define DOWN 13


using namespace std;

int N,M;
bool debug = false;
bool red_ball_sink, blue_ball_sink;

typedef struct cor{
    int Y;
    int X;
}cor;

typedef struct info{
    int dir;
    int cnt;
    cor blue;
    cor red;
}info;

queue<pair<info,vector<vector<char>>>> work;

void print_board( vector<vector<char>> A, vector<vector<char>> B)
{
 for(int r = 0 ; r < N ; r++)
        {for(int c =0; c <M ; c++)
            cout<<A[r][c]<<" ";
        cout<<"    ";
        for(int c =0; c <M ; c++)
            cout<<B[r][c]<<" ";
        cout<<endl;
        }
cout<<endl;
}

//info : Blue, Red, Hole 
pair<vector<cor>, vector<vector<char>>> shift(int toward, int cnt, vector<cor> info, vector<vector<char>> board){
    cor blue = info[0];
    cor red = info[1];
    cor hole = info[2];
    cor blue_moved = blue;
    cor red_moved = red;
    vector<vector<char>> board_save = board;
    board[blue.Y][blue.X] = '.';
    board[red.Y][red.X] = '.';
    if(debug) printf("cnt : %d , dir : %d\n",cnt, toward);
    switch(toward){
        case LEFT :{
            while(board[blue_moved.Y][blue_moved.X-1] == '.')
                blue_moved.X --;
            while(board[red_moved.Y][red_moved.X-1] == '.')
                red_moved.X --;
            if(blue_moved.X == red_moved.X && blue_moved.Y == red_moved.Y)
                {
                    if(blue.X<red.X) red_moved.X++;
                    else blue_moved.X++;
                }
            board[blue_moved.Y][blue_moved.X] = 'B';
            board[red_moved.Y][red_moved.X] = 'R';
            if(board[blue_moved.Y][blue_moved.X-1] == 'O')
                blue_ball_sink = true;
            else if(board[red_moved.Y][red_moved.X-1] == 'O')
                red_ball_sink = true;
            break;
        }
        case UP :{
            while(board[blue_moved.Y-1][blue_moved.X] == '.')
                blue_moved.Y --;
            while(board[red_moved.Y-1][red_moved.X] == '.')
                red_moved.Y --;
            if(blue_moved.X == red_moved.X && blue_moved.Y == red_moved.Y)
                {
                    if(blue.Y<red.Y) red_moved.Y++;
                    else blue_moved.Y++;
                 }
            board[blue_moved.Y][blue_moved.X] = 'B';
            board[red_moved.Y][red_moved.X] = 'R';

            if(board[blue_moved.Y-1][blue_moved.X] == 'O')
                blue_ball_sink = true;
            else if(board[red_moved.Y-1][red_moved.X] == 'O')
                red_ball_sink = true;
            break;
        }
        case RIGHT :{
            while(board[blue_moved.Y][blue_moved.X+1] == '.')
                blue_moved.X ++;
            while(board[red_moved.Y][red_moved.X+1] == '.')
                red_moved.X ++;
            if(blue_moved.X == red_moved.X && blue_moved.Y == red_moved.Y)
                {
                    if(blue.X<red.X) blue_moved.X--;
                    else red_moved.X--;    
                }
            board[blue_moved.Y][blue_moved.X] = 'B';
            board[red_moved.Y][red_moved.X] = 'R';

            if(board[blue_moved.Y][blue_moved.X+1] == 'O')
                blue_ball_sink = true;
            else if(board[red_moved.Y][red_moved.X+1] == 'O')
                red_ball_sink = true;
            break;
        }
        case DOWN :{
            while(board[blue_moved.Y+1][blue_moved.X] == '.')
                blue_moved.Y ++;
            while(board[red_moved.Y+1][red_moved.X] == '.')
                red_moved.Y ++;
            if(blue_moved.X == red_moved.X && blue_moved.Y == red_moved.Y)
                {
                    if(blue.Y<red.Y) blue_moved.Y--;
                    else red_moved.Y--;
                }
            board[blue_moved.Y][blue_moved.X] = 'B';
            board[red_moved.Y][red_moved.X] = 'R';
            
            if(board[blue_moved.Y+1][blue_moved.X] == 'O')
                blue_ball_sink = true;
            else if(board[red_moved.Y+1][red_moved.X] == 'O')
                red_ball_sink = true;
            break;
        }
    }
  
    

    if(debug) print_board(board_save,board);
    vector<cor> br = {blue_moved,red_moved};
    return make_pair(br,board);
}


void push_q(vector<pair<info, vector<vector<char>>>>dir)
{
    for(auto d : dir){
        work.push(d);
    }
}

bool is_equal(vector<vector<char>> A, vector<vector<char>> B)
{
    for(int r = 0 ; r < A.size() ; r++)
        for(int c = 0 ; c < A[0].size() ; c++)
            if(A[r][c]!=B[r][c])
                return false;
    return true;
}

int main()
{
    cor blue, red, hole;
    int ans;
    char p;   
    cin>>N>>M;
    vector<vector<char>> board(10, vector<char>(10,'A'));
    vector<vector<char>> new_board;

    for(int r = 0 ; r < N ; r++)
        for(int c =0; c <M ; c++)
                {
                    cin>>p;
                    board[r][c] = p;
                    if(p == 'B') blue = {r,c};
                    else if(p == 'R') red = {r,c};
                    else if(p == 'O') hole = {r,c};
                }
    pair<info,vector<vector<char>>> w;
    pair<vector<cor>, vector<vector<char>>> br_board;
    vector<cor> br;
    vector<info> init{{LEFT,1,blue,red},{UP,1,blue,red},{RIGHT,1,blue,red},{DOWN,1,blue,red}};
    push_q({make_pair(init[0],board),
            make_pair(init[1],board),
            make_pair(init[2],board),
            make_pair(init[3],board)});
        
    vector<info> next_work;
    while(!work.empty() ){
        w = work.front();
        work.pop();
        info work_info = w.first;
        int dir = work_info.dir;
        int cnt = work_info.cnt;
        blue = work_info.blue;
        red = work_info.red;
        
        if(cnt == 11){
            ans = -1;
            break;
        }
        board = w.second;
        br_board = shift(dir, cnt, {blue,red,hole},board);
        br = br_board.first;
        blue =br[0];
        red = br[1];
        if(red_ball_sink)
            {
                ans = cnt;
                switch(dir){
                    case LEFT : {
                        if(blue.X == red.X+1&& blue.Y == red.Y)
                            ans = -1;
                        break;
                    }
                    case UP : {
                        if(blue.Y == red.Y+1&& blue.X == red.X)
                            ans = -1;
                        break;
                    }
                    case RIGHT : {
                        if(blue.X == red.X-1&& blue.Y == red.Y)
                            ans = -1;
                        break;
                    }
                    case DOWN : {
                        if(blue.Y == red.Y-1 && blue.X == red.X)
                            ans = -1;
                        break;
                    }
                    
                }
                if(ans == cnt)
                    break;
            }
        
        new_board = br_board.second;
        if(!is_equal(board, new_board) && !blue_ball_sink)
        {
            board = new_board;
            switch(dir){
                case LEFT : {
                    next_work = {{UP,cnt+1,blue,red}, {DOWN,cnt+1,blue,red}};
                    push_q({make_pair(next_work[0],board),
                            make_pair(next_work[1],board)});
                    break;
                }
                case UP : {
                    next_work = {{RIGHT,cnt+1,blue,red}, {LEFT,cnt+1,blue,red}};
                    push_q({make_pair(next_work[0],board),
                            make_pair(next_work[1],board)});
                    break;
                }
                case RIGHT : {
                    next_work = {{DOWN,cnt+1,blue,red}, {UP,cnt+1,blue,red}};
                    push_q({make_pair(next_work[0],board),
                            make_pair(next_work[1],board)});
                    break;
                }
                case DOWN : {
                    next_work = {{LEFT,cnt+1,blue,red}, {RIGHT,cnt+1,blue,red}};
                    push_q({make_pair(next_work[0],board),
                            make_pair(next_work[1],board)});
                    break;
                }

            }
        }
        red_ball_sink = false;
        blue_ball_sink = false;
    }

    cout<<ans;

}