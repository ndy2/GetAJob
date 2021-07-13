#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <set>

#define NOTHING -1
#define NOTHING_COPY 0
#define OVERLAP 1
#define CONTACT 2
using namespace std;

int N;
int map[100][100];
bool visited[100][100];
int map_expand[100][100];
int map_save[100][100];

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

void input()
{
    cin>>N;
    for(int r = 0 ; r < N ; r ++)
        for(int c =0 ; c < N ; c++)
            cin>>map[r][c];
}


bool dfs(int y, int x, int idx)
{
    if(visited[y][x] || map[y][x] == 0)
        return false;
    visited[y][x] = 1;
    map[y][x] = idx;
    for(int d = 0 ;d < 4; d++)
    {
        int ty = y + dy[d];
        int tx = x + dx[d];
        if(ty>=0 && ty <N && tx >=0 && tx <N && map[ty][tx] ==1 && !visited[ty][tx])
            dfs(ty,tx,idx);
    }
    return true;
}

int island_indexing()
{
    int idx = 1;
    for(int r = 0 ; r < N ; r++)
        for(int c= 0 ; c < N ; c++)
            if(dfs(r,c,idx))
                idx++;
    return idx-1;
}

set<int> expanded_idx;

bool found = false;
bool is_overlap;

int expand(int r, int c, int idx)
{
    if(visited[r][c] || map_save[r][c] ==0)
        return NOTHING;
    visited[r][c] = true;
    map_expand[r][c] = idx;
    for(int d = 0 ; d < 4 ; d++)
        {
            int ty = r+dy[d];
            int tx = c+dx[d];
            if(ty>=0 && ty <N && tx >=0 && tx <N&& !visited[ty][tx])
                if(map[ty][tx] ==idx )
                    expand(ty,tx,idx);
                else if(map[ty][tx] == 0)
                    map_expand[ty][tx] = idx;
                else 
                {
                    found = true;
                    is_overlap = find(expanded_idx.begin(), expanded_idx.end(), map[ty][tx]) !=expanded_idx.end();
                } 
        }
    
    if(!found)
        return NOTHING_COPY;
    else if(is_overlap)
        return OVERLAP;
    else
        return CONTACT;
}

void solve()
{
    int cnt = 1;
    int num_island = island_indexing();
    memset(visited,0,sizeof(visited));
    int ans = 0;
    while(1)
    {
        int idx = 1;
        copy(&map[0][0], &map[0][0] + 100*100, &map_save[0][0]);
        copy(&map[0][0], &map[0][0] + 100*100, &map_expand[0][0]);
        for(int r= 0 ; r < N ; r++)
            for(int c = 0 ; c < N ; c++)
                {
                int out = expand(r,c,idx);
                
                if(out == NOTHING_COPY)
                    copy(&map_expand[0][0], &map_expand[0][0] + 100*100, &map[0][0]);
                else if(out == OVERLAP)
                    {
                        ans = 2*cnt-1;
                        r = N; c = N;   
                    }
                else if(out == CONTACT)
                    {
                        ans = 2*(cnt-1);
                        r = N; c = N;
                    }
                if(out>=0){
                    expanded_idx.insert(idx);
                    idx++;
                    }
                }
        cnt++;
        copy(&map_expand[0][0], &map_expand[0][0] + 100*100, &map[0][0]);
        expanded_idx.clear();
        memset(visited,0,sizeof(visited));
        found = false;
        if(ans != 0 )
            break;
    }
    cout<<ans;
}

int main()
{
    input();
    solve();

    return 0;
}