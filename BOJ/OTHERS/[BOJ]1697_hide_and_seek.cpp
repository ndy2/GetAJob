#include <iostream>
#include <queue>

using namespace std;

bool visited[100001];

typedef struct info{
    int cor,time;
}info;

int main()
{
    int N,K;
    cin>>N>>K;
    
    queue<info> q;
    visited[N] = true;
    q.push({N,0});
    int ans;
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        if(pos.cor == K)
        {
            ans = pos.time;
            break;
        }
        int t_cor[3] = {pos.cor-1, pos.cor+1, 2*pos.cor};
        for(int i = 0 ; i < 3; i++)
        {
            if(t_cor[i] <0 || t_cor[i] >100000)
                continue;
            if(!visited[t_cor[i]])
                {
                    visited[t_cor[i]] = true;
                    q.push({t_cor[i], pos.time+1});
                }
        }
    }
    cout<<ans;
}