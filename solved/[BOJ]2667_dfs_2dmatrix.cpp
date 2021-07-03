#include <vector>
#include <iostream>
#include <string.h>
#include <map>
#include <algorithm>

using namespace std;

int mmap[26][26];
int visited[26][26];
map<int,int> cnt_house;

int count_house = 1;
int dy[4] = {0,-1,0,1};
int dx[4] = {-1,0,1,0};

void dfs(int y, int x , int parsing)
{
    if(visited[y][x] != -1)
        return;
    else
    {
        if(mmap[y][x] == 1)
            {
                visited[y][x] = parsing;
                for(int i = 0 ; i < 4 ; i ++)
                {
                    dfs(y+dy[i], x+dx[i], parsing);
                }
            }
        
        else
        {
            return;
        }
    }
}

int main()
{
    int N;
    scanf("%d",&N);
    string row;

    memset(visited, -1 , sizeof(visited));

    for(int i = 0 ; i < N ; i++)
        {
            cin>>row;
            for(int j = 0 ; j < N ; j ++)
                mmap[i][j] = row[j]-'0';
        }

    
    
    int house_idx = 1;
    for(int i = 0 ; i < N ; i++)
        for(int j = 0 ; j < N ; j ++)

        {
            house_idx++;
            dfs(i,j,house_idx);
        }

    for(int i = 0 ; i < N ; i++)
        for(int j = 0 ; j < N ; j ++)
            if(visited[i][j] != -1)
            {
                if(cnt_house.find(visited[i][j]) == cnt_house.end())
                    cnt_house[visited[i][j]] = 1;
                else
                    cnt_house[visited[i][j]]++;
            }
    
    printf("%d\n", cnt_house.size());
    vector<int> cnt;
    for(auto s: cnt_house)
    {
        cnt.push_back(s.second);
    }
    sort(cnt.begin(),cnt.end());
    if(cnt.size()==0)
        printf("0\n");
    else{
        for(auto c : cnt)
            printf("%d\n", c);
    }
   

}
