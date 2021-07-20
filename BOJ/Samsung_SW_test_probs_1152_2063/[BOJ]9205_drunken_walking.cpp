#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#include <cmath>


using namespace std;

int N;
vector<vector<int>> cors;

void input()
{
    cin>>N;
    N+=2;
    vector<vector<int>> cors_copy(N,{0,0});
    for(int i = 0 ; i <N ; i++)
        cin>>cors_copy[i][0]>>cors_copy[i][1];
    cors = cors_copy;
}

int dist(vector<int> a, vector<int> b)
{
    return abs(a[0] -b[0]) +abs(a[1]-b[1]);
}

void solve()
{
    string ans = "sad";

    vector<bool> visited(N,false);
    vector<vector<bool>> edges(N,vector<bool>(N,false));

    for(int r = 0 ; r <N ; r++)
        for(int c=r+1 ; c<N ; c++)
            if(dist(cors[r],cors[c])<=1000)
            {
                edges[r][c] = true;
                edges[c][r] = true;
            }
    queue<int> q;
    q.push(0);
    visited[0] = true;

    while(!q.empty())
    {
        int pos = q.front();
        q.pop();
        if(pos == N-1)
            {
                ans = "happy";
                break;
            }
        for(int i = 0 ; i <N ; i++)
        {
            if(edges[pos][i] && !visited[i])
            {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout<<ans<<endl;
}

void clean()
{
    N = 0;
    cors.clear();
}

int main()
{
    int TC;
    cin>>TC;
    for(int tc=1; tc<=TC; tc++)
    {
        input();
        solve();
        clean();
    }
}