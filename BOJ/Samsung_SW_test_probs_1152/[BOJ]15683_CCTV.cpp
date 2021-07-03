#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int dy[6] = {0,1,0,-1,0,1};
int dx[6] = {1,0,-1,0,1,0};

typedef struct cctv{
    int y,x,type;
}cctv;

typedef struct info{
    queue<cctv> cctvs;
    vector<vector<int>> map;
}info;

void print_map(vector<vector<int>> map, int N, int M){
for(int r = 0 ; r < N ; r++)
    {    for(int c = 0 ; c <M ; c++)
            cout<<map[r][c]<<" ";
        cout<<endl;
     }       
     cout<<endl;
}


int count_0(vector<vector<int>> map, int N, int M)
{
    int cnt = 0;
    for(int r = 0 ; r < N ; r++)
        for(int c = 0 ; c <M ; c++)
            if(map[r][c] ==0)
                cnt++;
    return cnt;        
}

vector<vector<int>> proc_one_way(vector<vector<int>> map, int y, int x, int dir)
{
    while( y+dy[dir]<map.size() && x+dx[dir] <map[0].size() && map[y+dy[dir]][x+dx[dir]]!= 6)
    {
        y = y+dy[dir];
        x = x+dx[dir];
        map[y][x] = 7;
    }
    return map;
}

vector<info> proc(info i, int N, int M)
{
    vector<info> out;
    queue<cctv> cctvs = i.cctvs;
    vector<vector<int>> map = i.map;
    cctv proc_cctv = cctvs.front();
    cctvs.pop();
    switch (proc_cctv.type)
    {
            case 1:{
                    for(int d = 0 ; d < 4 ; d++)
                    {
                        vector<vector<int>> new_map = proc_one_way(map, proc_cctv.y, proc_cctv.x, d);
                        out.push_back({cctvs,new_map});
                    }
                    break;
                    }
            case 2:{
                    for(int d = 0 ; d < 2 ; d++)
                    {
                        vector<vector<int>> new_map = proc_one_way(map, proc_cctv.y, proc_cctv.x, d);
                        new_map = proc_one_way(new_map, proc_cctv.y, proc_cctv.x, d+2);
                        out.push_back({cctvs,new_map});
                    }
                    break;
                    }
            case 3:{
                    for(int d = 0 ; d < 4 ; d++)
                    {
                        vector<vector<int>> new_map = proc_one_way(map, proc_cctv.y, proc_cctv.x, d);
                        new_map = proc_one_way(new_map, proc_cctv.y, proc_cctv.x, d+1);
                        out.push_back({cctvs,new_map});
                    }
                    break;
                    }
            case 4:{
                    for(int d = 0 ; d < 4 ; d++)
                    {
                        vector<vector<int>> new_map = proc_one_way(map, proc_cctv.y, proc_cctv.x, d);
                        new_map = proc_one_way(new_map, proc_cctv.y, proc_cctv.x, d+1);
                        new_map = proc_one_way(new_map, proc_cctv.y, proc_cctv.x, d+2);
                        out.push_back({cctvs,new_map});
                    }
                    break;
                    }
            case 5:{
                    vector<vector<int>> new_map = proc_one_way(map, proc_cctv.y, proc_cctv.x, 0);
                    new_map = proc_one_way(new_map, proc_cctv.y, proc_cctv.x, 1);
                    new_map = proc_one_way(new_map, proc_cctv.y, proc_cctv.x, 2);
                    new_map = proc_one_way(new_map, proc_cctv.y, proc_cctv.x, 3);
                    out.push_back({cctvs,new_map});
                    break;
                    }
    }
    return out;

}


int main() {
    int t,N,M;
    int answer = 1e9;
    cin>>N>>M;
    vector<vector<int>> map(N,vector<int>(M,0));
    vector<vector<int>> map_save(N,vector<int>(M,0));
    
    queue<cctv> cctvs; 
    for(int r = 0 ; r < N ; r++)
        for(int c = 0 ; c <M ; c++)
    {        
        cin>>t;
        map_save[r][c] = t;
        if(t>0 && t<6)
            cctvs.push({r,c,t});
    }
    queue<info> qi;
    qi.push({cctvs, map_save});
    while(!qi.empty())
    {
        info front = qi.front();
        qi.pop();

        if(front.cctvs.empty())
            answer = min(answer, count_0(front.map,N,M));
        else{
            vector<info> out = proc(front,N,M);
            for(auto i : out)
                qi.push(i);
        }
        
    }
    cout<<answer;
}       