#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string.h>

using namespace std;

int N,M;
int map[101][101];

void input()
{
    fill_n(&map[0][0],101*101,500);

    cin>>N>>M;
    int A,B;
    for(int i = 0 ; i < M ; i++)
    {
        cin>>A>>B;
        map[A][B] = 1;
        map[B][A] = 1;
    }
}

void FW_logic()
{
    for(int j = 1 ; j <= N ; j ++)
        for(int i = 1 ; i <= N ; i++)
            for(int k = 1 ; k <= N ; k++)
                if(i!=j && j!=k && k!=i )
                    map[i][k] = min(map[i][j]+map[j][k],map[i][k]);
}

void solve()
{
    FW_logic();
    vector<int> KB_number(N,0);
    for(int i = 1 ; i <=N ; i++)
        for(int j = 1 ; j <= N ; j++)
            if(i!=j)
                KB_number[i-1]+=map[i][j];
    int ans = min_element(KB_number.begin(), KB_number.end()) - KB_number.begin() +1;
    cout<<ans;
}



int main()
{
    input();
    solve();
}