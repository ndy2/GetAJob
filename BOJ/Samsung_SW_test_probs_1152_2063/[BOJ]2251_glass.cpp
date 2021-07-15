#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
vector<int> portion(3,0);

typedef struct info{
    vector<int> amount;
}info;


info move_water(info pos,int from, int to)
{
    int to_receivable = portion[to] - pos.amount[to];
    info ret = pos;
    if(pos.amount[from]==0)
        ret.amount[0] = -1;
    else if(pos.amount[from] > to_receivable)
    {
        ret.amount[to] = portion[to];
        ret.amount[from] -=to_receivable;
    }
    else
    {
        ret.amount[to] +=ret.amount[from];
        ret.amount[from] =0;
    }

    if(ret.amount[0]+ret.amount[1]+ret.amount[2]!=portion[2])
        ret.amount[0]=-1;

    return ret;
}

int main()
{
    cin>>portion[0]>>portion[1]>>portion[2];
    int N = (portion[2]+1)*(portion[2]+2)/2;
    vector<vector<vector<bool>>> visited(201,vector<vector<bool>>(201,vector<bool>(201,false)));
    queue<info> q;
    q.push({{0,0,portion[2]}});
    visited[0][0][portion[2]] = true;
    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        visited[pos.amount[0]][pos.amount[1]][pos.amount[2]] = true;
        // cout<<pos.amount[0]<<" "<<pos.amount[1]<<" "<<pos.amount[2]<<endl;
        vector<info> vi;
        vi.push_back(move_water(pos,0,1));
        vi.push_back(move_water(pos,1,0));
        vi.push_back(move_water(pos,0,2));
        vi.push_back(move_water(pos,2,0));
        vi.push_back(move_water(pos,1,2));
        vi.push_back(move_water(pos,2,1));

        for(auto v : vi)
            if(v.amount[0]!=-1)
            {
                if(!visited[v.amount[0]][v.amount[1]][v.amount[2]])
                {
                    visited[v.amount[0]][v.amount[1]][v.amount[2]] = true;
                    q.push(v);
                }
            }
    }
    vector<int> ans;
    for(int i = 0 ; i <=portion[2] ; i++)
        if(visited[0][portion[2]-i][i])
            ans.push_back(i);
    
    for(auto a : ans)
        cout<<a<<" ";

    return 0;
}