#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#define K 1
#define D 2

using namespace std;

int board[8][8];
map<string,vector<int>> move_type = {{"R",{0,1}},
                                     {"L",{0,-1}},
                                     {"B",{1,0}},
                                     {"T",{-1,0}},
                                     {"RT",{-1,1}},
                                     {"LT",{-1,-1}},
                                     {"RB",{1,1}},
                                     {"LB",{1,-1}},
                                     };

vector<int> king(2,0);
vector<int> doll(2,0);
vector<vector<int>> moves;

void input()
{
    string king_str,doll_str;
    int N;
    cin>>king_str>>doll_str>>N;
    king[0] = '8'-king_str[1] ;
    king[1] = king_str[0] - 'A';
    
    doll[0] = '8'-doll_str[1] ;
    doll[1] = doll_str[0] - 'A';
    
    board[king[0]][king[1]] = K;
    board[doll[0]][doll[1]] = D;

    string s;
    for(int i = 0 ; i < N ; i++)
    {
        cin>>s;
        moves.push_back(move_type[s]);
    }
}

void solve()
{
    for(auto m : moves)
    {
        int king_ty = king[0] + m[0];
        int king_tx = king[1] + m[1];

        if(king_ty<0 || king_ty>=8 || king_tx <0 || king_tx >=8)
            continue;

        if(king_ty == doll[0] && king_tx == doll[1] && board[king_ty][king_tx]==D)
            {
                int doll_ty = doll[0] + m[0];
                int doll_tx = doll[1] + m[1];
                if(doll_ty<0 || doll_ty>=8 || doll_tx <0 || doll_tx >=8)
                    continue;
                board[doll[0]][doll[1]] = 0;
                board[doll_ty][doll_tx] = D;
                doll[0] = doll_ty;
                doll[1] = doll_tx;
            }
        board[king[0]][king[1]] = 0;
        board[king_ty][king_tx] = K;
        king[0] = king_ty;
        king[1] = king_tx;
       
      }
    cout<<(char)(king[1]+'A')<<8-king[0]<<endl;
    cout<<(char)(doll[1]+'A')<<8-doll[0]<<endl;
}

int main()
{
    input();
    solve();
}