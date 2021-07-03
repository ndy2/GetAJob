#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int R,C,K;
vector<vector<int>> matrix(3,vector<int>(3,0));

bool mysort(pair<int,int> a, pair<int,int> b)
{
    return a.second<b.second?true:
            a.second>b.second?false:
            a.first<b.first?true:false;
}

vector<vector<int>> transpose(vector<vector<int>> mat)
{
    int M = mat.size();
    int N = mat[0].size();
    vector<vector<int>> t_mat(N,vector<int>(M,0));
    for(int r= 0 ; r < N ; r++)
        for(int c = 0 ; c < M ; c++)
            t_mat[r][c] = mat[c][r];
    return t_mat;
}

vector<int> R_OP_one (vector<int> row)
{
    map<int,int> h;
    vector<int> ret;
    for(int i = 0 ; i <row.size() ; i++)
    {
        if(row[i] == 0)
            continue;
        else if(h.find(row[i])!= h.end())
            h[row[i]]+=1;
        else
            h[row[i]]=1; 
    }
    vector<pair<int,int>> hv(h.begin(),h.end());

    sort(hv.begin(), hv.end(), mysort);
    for(auto p : hv)
    {
        ret.push_back(p.first);
        ret.push_back(p.second);
        if(ret.size() >100)
            break;
    }
    return ret;
}

vector<vector<int>> R_OP(vector<vector<int>> mat)
{
    vector<vector<int>> ret;
    int max_col = 0;
    for(auto row : mat)
    {
        vector<int> row_out = R_OP_one(row);
        ret.push_back(row_out);
        max_col = max(max_col, (int)row_out.size());
    }
    for(int r = 0 ; r < ret.size() ;r++)
        while(ret[r].size() < max_col)
            ret[r].push_back(0);
    
    return ret;    
}

void input()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(nullptr);

    cin>>R>>C>>K;
    for(int r= 0 ;r < 3; r++)
        for(int c = 0 ; c < 3 ; c++)
            cin>>matrix[r][c];
            
}


void solve()
{
    int time = 0;
    while(1)
    {
        if(R-1 < matrix.size() && C-1<matrix[0].size())
            if(matrix[R-1][C-1] ==K)
                break;
        if(time>100)
            {
                time = -1;
                break;
            }
 
        time++;
        int r_num = matrix.size();
        int c_num = matrix[0].size();
        bool tp = r_num<c_num;
        if(tp)
            matrix = transpose(matrix);
        matrix = R_OP(matrix);
        if(tp)
            matrix = transpose(matrix);
        
    }
    cout<<time;
}


int main() {
    input();
    solve();

    return 0;
}       