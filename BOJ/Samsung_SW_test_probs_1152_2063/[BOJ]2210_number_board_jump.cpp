#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

char map[100][100];

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

set<string> made;

void input()
{
    for(int r = 0 ; r < 5 ; r ++)
        for(int c =0 ; c < 5 ; c++)
            cin>>map[r][c];
}

string keep;
void dfs(int y, int x, int len)
{
    if(len == 6)
        {
            made.insert(keep);
            return;
        }
    for(int d = 0 ; d < 4 ;d++)
    {
        int ty = y+dy[d];
        int tx = x+dx[d];
        if(ty>=0 && ty<5 && tx>=0 && tx<5)
            {
                keep.push_back(map[ty][tx]);
                dfs(ty,tx,len+1);
                keep.pop_back();
            }
    }        
}

void solve()
{
    for(int r= 0 ; r < 5 ; r++)
        for(int c= 0 ; c < 5; c++)
                dfs(r,c,0);
    cout<<made.size();
}


int main()
{
    input();
    solve();

    return 0;
}