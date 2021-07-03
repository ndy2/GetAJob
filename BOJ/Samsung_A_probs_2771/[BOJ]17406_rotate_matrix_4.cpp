#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int N,M,K;
vector<vector<int>> map;
int visited[6];
vector<int> idx;
vector<vector<int>> rotates(7,vector<int>(3,0));

void input()
{
    cin>>N>>M>>K;
    vector<vector<int>> map_in(N+1, vector<int>(M+1,0));
    for(int r= 1; r <=N ; r++)
        for(int k =1; k <=M; k++)
            cin>>map_in[r][k];
    map =map_in;
    int r,c,s;
    for(int i = 0 ; i < K ; i++)
        {
            cin>>r>>c>>s;
            rotates[i] = {r,c,s};
            idx.push_back(i);
        }
}


vector<vector<int>> rotate_mat (vector<vector<int>> mat, vector<int> rt)
{
    int r= rt[0];
    int c = rt[1];
    int stride = rt[2];

    for(int s = 1; s <=stride ; s++)
    {
        int l = 2*s;
        vector<int> top(l,0), right(l,0), below(l,0), left(l,0);

        //init
        for(int i = 0 ; i < l ; i++)
        {
            top[i] = mat[r-s][c-s+i];
            right[i] = mat[r-s+i][c+s];
            below[i] = mat[r+s][c+s-i];
            left[i] = mat[r+s-i][c-s];
        }

        //put
        for(int i = 0 ; i < l ; i++)
        {
            mat[r-s][c-s+i+1] = top[i];
            mat[r-s+i+1][c+s] =right[i];
            mat[r+s][c+s-i-1] = below[i];
            mat[r+s-i-1][c-s] = left[i];
        }
    }
    return mat;
}

int cnt = 0;
int ans = 1e9;

int min_row(vector<vector<int>> mat)
{
    int ret = 1e9;
    for(int r = 1; r < mat.size() ; r++)
    {
        int sum =0;
        for(auto col : mat[r])
            sum+=col;
        ret = min(sum,ret);
    }
    return ret;
}


void solve()
{

    do{
        vector<vector<int>> mat = map;
        for(auto s : idx)
            mat = rotate_mat(mat,rotates[s]);

        ans = min(ans,min_row(mat));
    }       
    while(next_permutation(idx.begin(), idx.end())); 

    cout<<ans;
}

int main() {
    input();
    solve();

    return 0;
}       