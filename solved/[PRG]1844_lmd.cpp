//https://programmers.co.kr/learn/courses/30/lessons/1844
//bfs !

#include<vector>
#include<iostream>
#include<queue>


int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0};
bool is_done = false;
int visited[101][101];

typedef struct cor {
    int y;
    int x;
    int l;
}cor;

using namespace std;

int solution(vector<vector<int> > maps)
{

    int ROW = maps.size();
    int COL = maps[0].size();
    queue<cor> q;
    q.push({0,0,0});
    visited[0][0] = true;
    while(!q.empty())
    {
        cor pop = q.front();
        int x = pop.x;
        int y = pop.y;
        int l = pop.l;
        q.pop();
        
     
        
        for(int i = 0 ; i <4 ; i ++)
        {   
            int ty = y+dy[i];
            int tx = x+dx[i];
            
            if(ty==ROW-1 && tx == COL-1)
                return l+2;
            
            if(ty>=0&& ty < ROW && tx >=0&& tx <COL && !visited[ty][tx] && maps[ty][tx]==1  )
            {
                visited[ty][tx] = true;
                q.push({y+dy[i], x+dx[i], l+1});
            }
        }
    }
    return -1;
}
