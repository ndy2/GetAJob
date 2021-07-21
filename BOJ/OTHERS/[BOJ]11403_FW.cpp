#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
bool visitable[101][101];

void input()
{
    cin>>N;
    for(int i = 1; i <= N ; i++)
        for(int j = 1 ; j <=N ; j++)
            cin>>visitable[i][j];
}

void solve()
{

    for(int j = 1; j <= N ; j++)
        for(int i = 1 ; i <=N ; i++)
            for(int k = 1 ; k <=N ; k++)
                visitable[i][k] |= visitable[i][j] && visitable[j][k];
    for(int i = 1 ; i <=N ; i++)
        {
            for(int j = 1 ; j <=N ; j++)
                printf("%d ",visitable[i][j]);
            printf("\n");
        }
}

int main()
{
    input();
    solve();
}