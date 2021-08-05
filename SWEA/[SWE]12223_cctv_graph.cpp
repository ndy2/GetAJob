#include<string.h>
#include<iostream>
#include<vector>
#include <algorithm>
#define MAX 100000
using namespace std;


int N;

typedef struct cctv{
    int x1,y1,x2,y2;
}cctv;

cctv dummy ={0,0,0,0};
vector<cctv> vc(100000,dummy);
vector<int> idx2neighbor[100000];
void input()
{
    cin>>N;
    for(int i = 0 ; i < N ; i++)
        scanf("%d %d %d %d",&vc[i].x1,&vc[i].y1,&vc[i].x2,&vc[i].y2);
}

void init_idx2neighbor()
{
    for(int i = 0 ; i <N-1 ; i++)
        for(int j = i+1; j < N ; j++)
        {
            int minX = max(vc[i].x1,vc[j].x1);
            int minY = max(vc[i].y1,vc[j].y1);
            int maxX = min(vc[i].x2,vc[j].x2);
            int maxY = min(vc[i].y2,vc[j].y2);
            if(minX<=maxX && minY<=maxY)
                idx2neighbor[i].push_back(j);
        }
}

void solve(int tc)
{
    int ans = 0;
    init_idx2neighbor();

    for(int i = 0 ; i < N ; i++)
    {
        int num_neighbor = idx2neighbor[i].size();
        if(num_neighbor<2)
            continue;
        vector<int> ind (num_neighbor, 0);
        fill_n(ind.end()-2,2,1);
        
        do{
            vector<int> idx;
            for(int j = 0 ; j < num_neighbor; j++)
                if(ind[j]==1)
                    idx.push_back(idx2neighbor[i][j]);
            if(find(idx2neighbor[idx[0]].begin(), idx2neighbor[idx[0]].end(), idx[1]) != idx2neighbor[idx[0]].end())
                ans++;
            }
        while(next_permutation(ind.begin(), ind.end()));
    }

    printf("#%d %d\n",tc, ans);
}

void clear()
{
    for(int i = 0 ; i < N ; i++) idx2neighbor[i].clear();
    N = 0;
    vc = vector<cctv>(100000,dummy);
}

int main()
{
    int TC;
    cin>>TC;
    for(int tc = 1; tc<=TC; tc++)
    {
        input();
        solve(tc);
        clear();
    }
}