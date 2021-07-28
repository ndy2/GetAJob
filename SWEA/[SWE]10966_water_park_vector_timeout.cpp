#include <queue>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int deltaY[] = {-1, 0, 1, 0};
    int deltaX[] = {0, -1, 0, 1};
    int TC;
    cin>>TC;
    for(int tc =1 ; tc<=TC; tc++)
    {
        int N,M;
        int ans = 0;
        cin>>N>>M;
        vector<vector<int>> map(N,vector<int>(M,0));
        queue<vector<int>> q;
        for(int r= 0 ; r < N ; r++)
            {   
                string line;
                cin>>line;
                for(int c= 0 ; c < M ; c++)
                    if(line[c] == 'W')
                    {
                        map[r][c] = -1;
                        q.push({r,c});
                    }
            }
        while(!q.empty())
        {
            int nowY = q.front()[0];
            int nowX = q.front()[1];
            
            q.pop();
            if(map[nowY][nowX] != -1)
                ans+=map[nowY][nowX];

            for(int d= 0 ;d < 4 ; d++)
            {
                int ty = nowY + deltaY[d];
                int tx = nowX + deltaX[d];
                if(ty<0||ty>=N||tx<0||tx>=M)
                    continue;
                if(map[ty][tx]!=0)
                    continue;

                if(map[nowY][nowX] == -1)
                    map[ty][tx] = 1;
                else
                    map[ty][tx] = map[nowY][nowX]+1;
                q.push({ty,tx});    
            }
        }
        printf("#%d %d\n",tc,ans);
    }    
}