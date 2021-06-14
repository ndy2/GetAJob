#include <iostream>
#include <vector>
#include <algorithm>

#define HEAD 200
#define APPLE 300
#define RIGHT 10
#define BELOW 11
#define LEFT 12
#define UP 13

using namespace std;

int board[101][101];
int dir_info[101][101];
int N;

typedef struct cor{
    int Y;
    int X;
}cor;

cor move_1(cor h, int head_to){
    switch(head_to){
        case RIGHT : {
            h.X+=1;
            break;
        }
        case BELOW :{
            h.Y +=1;
            break;
        }
        case LEFT :{
            h.X -=1;
            break;
        }
        case UP :{
            h.Y -=1;
            break;
        }
    }
    return h;
}

//cor valid test
bool is_valid(cor h){
    if(h.X<1 || h.Y<1 || h.X >N || h.Y >N)
        return false;
    return true;
}

//snake crashed test
bool is_crashed(cor h){
    if(board[h.Y][h.X] == HEAD) return true;
    return false;
}

//apple test
bool is_apple(cor h){
    if(board[h.Y][h.X] ==APPLE) return true;
    return false;
}

//rotate direction
int rotate_dir(int head_to, char C){
    if(C == 'D') return head_to==UP?RIGHT:head_to+1;
    else if(C =='L') return head_to==RIGHT?UP:head_to-1;
    return -1;
}

//For Debugging
void print_board(int glb_time){
    for(int row = 1; row <=N ; row ++){
        for(int col = 1; col <=N ; col ++){
            printf("%4d ",board[row][col]);
        }
        printf("\n");
    }
    printf("time: %d\n\n",glb_time);
}

int main()
{
    int K;
    cin>>N>>K;
    int r,k;
    //Set Apples
    for(int i = 0 ; i < K ; i ++)
        {cin>>r>>k; board[r][k] = APPLE;}

    
    board[0][0] = HEAD;
    //Init
    cor head = {1,1};
    cor tail = {1,1};
    board[head.Y][head.X] = HEAD;
    dir_info[head.Y][head.X] = RIGHT;
    int head_to = RIGHT;
    int glb_time = 0;
    int L;
    cin>>L;
    int prev_X = 0,X;
    char C;
    //마지막에 무조건 직진을 해야 하므로 L+1번 반복을 한다
    //마지막엔 이전에 Rotate한 방향을 유지한체 앞으로 100칸 간다. ->무조건 박는다.
    for(int i = 0 ; i < L+1 ; i ++)
    {
        //기본적으로 입력을 받고 마지막에는 직진
        if(i<L) cin>>X>>C;
        else X = 100;
        int t;

        //매 초 이동
        for(t = 1 ; t <= X-prev_X ; t ++)
        {
            //move하고 겜 터졌는지 test
            cor moved = move_1(head, head_to);
            if(!is_valid(moved)) {t++; i = L; break; }
            else if(is_crashed(moved)){t++; i = L; break;}

            //아니라면 head를 이동하고
            else {
                head = moved;
                //사과 확인
                if(!is_apple(head)) 
                    {
                        board[tail.Y][tail.X] = 0;
                        cor next_tail = move_1(tail, dir_info[tail.Y][tail.X]);
                        dir_info[tail.Y][tail.X] = 0;
                        tail = next_tail;
                    }
                //보드 그리기
                board[head.Y][head.X] = HEAD;
                dir_info[head.Y][head.X] = head_to;
            }
            // print_board(glb_time+t);
        }
        //도착했으면 시간 더하고 머리 돌림
        glb_time += t-1;
        head_to = rotate_dir(head_to, C);
        dir_info[head.Y][head.X] = head_to;
        prev_X = X;
    }
    cout<<glb_time<<endl;
}
