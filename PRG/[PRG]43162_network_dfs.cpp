#include <string>
#include <vector>
#include <iostream>

using namespace std;

int visited[200];

bool dfs(int n, vector<vector<int>> computers)
{
    if(visited[n])
        return false;
    else{
        visited[n] = true;
        for(int i = 0 ; i <computers[n].size(); i++)
        {
            if(computers[n][i]==1)
            {
                dfs(i,computers);
            }
        }
        return true;

    }
}

int solution(int n, vector<vector<int>> computers) {
    int count = 0;
    for(int i = 0 ; i < computers.size(); i++)
    {
        if(dfs(i,computers))
            count++;
    }
    return count;
}

int main()
{
    int n = 3;
    vector<vector<int>> computers = {{1,1,0},
                                     {1,1,0},
                                     {0,0,1}};
    vector<vector<int>> computers2 = {{1,1,0},
                                     {1,1,1},
                                     {0,1,1}};
    
    cout<<solution(n,computers)<<endl;
    cout<<solution(n,computers2)<<endl;
}