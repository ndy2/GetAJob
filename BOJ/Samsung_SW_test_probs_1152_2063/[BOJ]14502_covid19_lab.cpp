#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

#define WALL 1
#define EMPTY 0

using namespace std;

int map[8][8];
int map_save[8][8];
int visited[8][8];

typedef struct cor{
    int Y;
    int X;
}cor;

void set_3(vector<int> idx, vector<cor> zeros,int type){
    for(int i = 0 ; i <idx.size() ; i++)
        if(idx[i]==1) 
            map[zeros[i].Y][zeros[i].X] = type;
}

vector<cor> dir = {{0,-1},{-1,0},{0,1},{1,0}};

int ans =0;
int cnt =0;
int N,M;

bool is_valid(cor c){
    if(c.X <0 || c.X>=M || c.Y<0 || c.Y>=N)
        return false;
    return true;
}

void dfs(cor c, bool contagious)
{
    if(visited[c.Y][c.X] == 1)
        return;
    else{
        visited[c.Y][c.X] = 1;
        if(map[c.Y][c.X] == 0 && contagious)
            map[c.Y][c.X] = 2;
        if(map[c.Y][c.X] == 1)
            return;
        for(int i = 0 ; i < 4 ; i ++)
        {
            cor target = {c.Y+dir[i].Y, c.X +dir[i].X};
            if(is_valid(target))
                dfs(target,true);
        }
    }
}

void print_map(){
    for(int r = 0 ; r < N ; r ++)
    {
            for(int c = 0 ; c < M ; c ++)
                cout<<map[r][c]<<" ";
            cout<<endl;
    }
    cout<<endl;
}

int count_zeros(){
    int ans = 0;
    for(int r = 0 ; r < N ; r ++)
            for(int c = 0 ; c < M ; c ++)
                if(map[r][c]==0) ans++;
    return ans;
}

int main()
{
   vector<cor> zeros;
   cin>>N>>M;
   int p;
   for(int r = 0 ; r < N ; r ++)
        for(int c = 0 ; c < M ; c ++)
            {
                scanf("%d",&p);
                map_save[r][c] = p;
                if(p == EMPTY) zeros.push_back({r,c});
            }
    vector<int> idx;
    for(int i = 0 ; i < zeros.size()-3; i++)
        idx.push_back(0);
    for(int i = zeros.size()-3; i <zeros.size() ; i++)
        idx.push_back(1);
    do{
        copy(&map_save[0][0], &map_save[0][0]+64, &map[0][0]);
        memset(visited, 0 , sizeof(visited));
        set_3(idx,zeros,WALL);
        // print_map();        

        for(int r = 0 ; r < N ; r ++)
             for(int c = 0 ; c < M ; c ++)
                 {
                 if(map[r][c]==2) 
                    dfs({r,c},false);
                 }
        ans = max(count_zeros(), ans);
        // print_map();        
    }
    while(next_permutation(idx.begin(),idx.end()));
    cout<<ans<<endl;
}