#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int F,S,G,U,D;
void input()
{
    cin>>F>>S>>G>>U>>D;
}

typedef struct info{
    int pos,cnt;
}info;

void solve()
{
    int ans = 0;
    if(S==G)
        {
            cout<<0;
            return;
        }
    vector<bool> visited(F+1,false);
    queue<info> q;
    q.push({S,0});
    visited[S] = true;
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        if(pos.pos == G)
            {
                ans = pos.cnt;
                break;
            }
        int tu = pos.pos + U;
        if(tu<=F && !visited[tu])
            {
                visited[tu] = true;
                q.push({tu,pos.cnt+1});
            }
        int td = pos.pos - D;
        if(td>=1 && !visited[td])
            {
                visited[td] = true;
                q.push({td,pos.cnt+1});
            }
    }
    if(ans == 0)
        cout<<"use the stairs";
    else
        cout<<ans;
}

int main()
{
    input();
    solve();
}