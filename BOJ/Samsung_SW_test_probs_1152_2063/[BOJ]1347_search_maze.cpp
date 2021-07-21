#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <queue>

using namespace std;

int N;
string moves;
int dir = 0;
vector<int> y_range = {50,50};
vector<int> x_range = {50,50};
vector<int> hongjun = {50,50};

char map[100][100];

void input()
{
    cin>>N>>moves;
}


int dy[4] = {1,0,-1,0};
int dx[4] = {0,-1,0,1};

void update_range()
{
    y_range[0] = min(y_range[0], hongjun[0]);
    y_range[1] = max(y_range[1], hongjun[0]);
    x_range[0] = min(x_range[0], hongjun[1]);
    x_range[1] = max(x_range[1], hongjun[1]);
}

void solve()
{
    map[hongjun[0]][hongjun[1]] = '.';
    for(auto m : moves)
    {
        if(m =='R')
            dir = (dir+1)%4;
        else if(m=='L')
            dir = (dir+3)%4;
        else
        {
            hongjun[0] += dy[dir];
            hongjun[1] += dx[dir];
            map[hongjun[0]][hongjun[1]] = '.';
            update_range();
        }
    }

    for(int r = y_range[0] ; r <= y_range[1] ;r ++)
        {
            for(int c =  x_range[0] ; c<=x_range[1] ; c++)
                if(map[r][c] == '.')
                    cout<<'.';
                else
                    cout<<"#";
            cout<<endl;
        }
}

int main()
{
    input();
    solve();

    return 0;
}