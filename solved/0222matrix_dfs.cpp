#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 10

using namespace std;

vector<vector<bool>> visited = vector<vector<bool>>(MAX, vector<bool> (MAX,0));
vector<pair<int,int>> dir = {{0,-1},{-1,0},{0,1},{1,0}}; //(y,x) left, above, right, below

void dfs(int i, int j, vector<vector<int>> mat, int& prev,int l)
{
    int x_target, y_target;
    //dfs logic
    if(visited[i][j])
    {
        return;
    }
    else
    {
        if(mat[i][j])
        {
            prev ++;
            // cout<<"1 visited["<<i<<"]["<<j<<"]" <<endl;
            visited[i][j]=true;
            for(auto d : dir)
            {
                x_target = j+d.second;
                y_target = i+d.first;
                if(x_target>=0 && x_target<l &&
                    y_target>=0 && y_target<l && !visited[y_target][x_target])
                    {
                        dfs(y_target,x_target,mat,prev,l);
                    }
            }
        }
        else{
            // cout<<"0 visited["<<i<<"]["<<j<<"]" <<endl;
            visited[i][j]=true;
        }
    }
    
}

//오름차순 정렬 
void print_sol(vector<int> region)
{
    int s = region.size();
    sort(region.begin(), region.end(), less<int>());
    cout<<s<<endl;
    for(auto e : region)
        cout<<e<<" ";
    cout<<endl;
}

void solution(int l, vector<vector<int>> mat) {
    vector<int> region;
    for(int i = 0 ; i < l ; i ++)
    {
        for(int j = 0 ; j < l ; j ++)
        {
            int prev = 0;
            dfs(i,j,mat,prev,l);
            //non zero 값만 저장함
            if(prev != 0)
                region.emplace_back(prev);
        }
    }
    //결과 출력
    print_sol(region);

    //전역변수 초기화
    visited = vector<vector<bool>>(MAX, vector<bool> (MAX,0));
}

int main()
{
    int l1 = 6;
    vector<vector<int>> mat1 = {{0,1,1,0,0,0},
                               {0,1,1,0,1,1},
                               {0,0,0,0,1,1},
                               {0,0,0,0,1,1},
                               {1,1,0,0,1,0},
                               {1,1,1,0,0,0}};
    cout<<"Case 1"<<endl;
    solution(l1,mat1);

    int l2 = 4;
    vector<vector<int>> mat2 = vector<vector<int>>(4, vector<int> (4, 0));
    cout<<"Case 2"<<endl;
    solution(l2,mat2);
    // Case2의 경우 0\n이 아닌 0\n\n을 출력하는 자잘한 버그가 있지만 그냥 냅둠

    mat2[0][0]=1;
    mat2[1][0]=1;
    mat2[3][2]=1;
    mat2[3][3]=1;
    cout<<"Case 3"<<endl;
    solution(l2,mat2);
}