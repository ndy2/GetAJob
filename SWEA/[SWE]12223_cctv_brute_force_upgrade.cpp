#include<string>
#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;


int N;

typedef struct cctv{
    int x1,y1,x2,y2;
}cctv;

cctv dummy ={0,0,0,0};
vector<cctv> vc(100000,dummy);
void input()
{
    cin>>N;
    for(int i = 0 ; i < N ; i++)
        scanf("%d %d %d %d",&vc[i].x1,&vc[i].y1,&vc[i].x2,&vc[i].y2);
}

void solve(int tc)
{
    int ans = 0;
    vector<int> ind(N,0);
    fill_n(ind.end()-2,2,1);
    do{
        int minX = 0;
        int minY = 0;
        int maxX = 1001;
        int maxY = 1001;
        
        int min_idx=-1;
        for(int i = 0 ; i < N ; i++)
            if(ind[i]==1)
            {   
                if(min_idx==-1) min_idx = i;
                minX = max(minX,vc[i].x1);
                minY = max(minY,vc[i].y1);
                maxX = min(maxX,vc[i].x2);
                maxY = min(maxY,vc[i].y2);
            }
        if(minX<=maxX && minY<=maxY)
        {
            for(int i = 0 ; i < min_idx ; i++)
            {
                int minX_ = max(minX,vc[i].x1);
                int minY_ = max(minY,vc[i].y1);
                int maxX_ = min(maxX,vc[i].x2);
                int maxY_ = min(maxY,vc[i].y2);
                if(minX_<=maxX_ && minY_<=maxY_)
                    ans++;
            }
        }
    }while(next_permutation(ind.begin(), ind.end()));
    printf("#%d %d\n",tc, ans);
}

void clear()
{
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