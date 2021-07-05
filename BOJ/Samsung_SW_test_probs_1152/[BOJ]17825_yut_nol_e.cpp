#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define STT 0
#define END 20

using namespace std;

int debug = 1;
vector<int> num(10,0);

bool is_blue[33];


vector<vector<int>> blue_move =
{{0,22,23,24,30,31},
 {0,25,26,30,31,32},
 {0,27,28,29,30,31}};

vector<int> idx2score = 
{0,2,4,6,8,10,12,14,16,18,
20,22,24,26,28,30,32,34,36,38,
40,0,13,16,19,22,24,28,27,26,
25,30,35};

typedef struct info{
    int score,step;
    vector<int> state;
}info;

void input()
{
    for(int i = 0 ; i < 10 ; i++)
        cin>>num[i];
}

int move_piece(int from, int l)
{
    int ret;
    if(from>=22 && from<=24)
    {
        if(from + l <=24)
            ret = from+l;
        else
            ret = 5 + l + from;
        
        if(ret == 33) ret = 20;
        else if(ret == 34) ret = 21;
    }
    else if(from == 25 && l ==1)
        ret = 26;
    else if (from==25 || from ==26)
    {
        ret = 3 + l + from;
        if(ret == 33) ret = 20;
        else if(ret == 34) ret = 21;
    }
    else if(from>=27 && from<=32)
    {
        ret = from + l;
        if(ret == 33) ret = 20;
        else if(ret >=34) ret = 21;
    }
    else if(from>=17)
    {
        ret = from+l;
        if(ret >21) ret = 21;
    }
    else if(is_blue[from])
        ret = blue_move[from/5 -1][l];
    else
        ret = from+l;

    return ret;
}

void init_is_blue()
{
    is_blue[5] = 1;
    is_blue[10] = 1;
    is_blue[15] = 1;    
}

info init_info()
{
    vector<int> state (33,0);
    state[0] = 4;
    return {0,0,state};
}

void solve()
{
    int ans = -1;
    init_is_blue();
    info stt = init_info();
    queue<info> q;
    q.push(stt);
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();

        if(pos.step == 10)
        {
            ans = max(ans, pos.score);
            continue;
        }

        vector<int> movable_idx;
        vector<int> moved_idx;
        for(int i = 0 ; i <=32 ; i++)
        {
            int moved = move_piece(i,num[pos.step]);
            if(i!=21 && pos.state[i]!= 0 && (moved==21|| pos.state[moved] ==0))
            {
                movable_idx.push_back(i);
                moved_idx.push_back(moved);
            }
        }

        for(int i = 0 ; i < movable_idx.size() ; i++)
        {
            vector<int> moved_state = pos.state;
            int step =pos.step+1;
            int score = pos.score + idx2score[moved_idx[i]];

            moved_state[movable_idx[i]]--;
            moved_state[moved_idx[i]]++;
            q.push({score, step, moved_state});
        }
    }
    cout<<ans;
}

int main()
{
    input();
    solve();
}