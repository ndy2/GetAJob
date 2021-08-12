#include <iostream>
#include <vector>
using namespace std;

int N,M;
vector<int> keep;

void dfs(int idx)
{
    // printf("%d \n", idx);
    if(keep.size() ==M)
        {
            for(auto i : keep)
                printf("%d ",i);
            printf("\n");
            return;
        }
    for(int i = 1; i <=N ; i++)
        {
            keep.push_back(i);
            dfs(i);
            keep.pop_back();
        }
}

int main()
{
    cin>>N>>M;
    dfs(1);
}