#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<vector<vector<int>>> pans(5, vector<vector<int>>(5, vector<int>(5,0)));

void input()
{
    for(int p = 0 ; p < 5 ; p++)
        for(int row = 0 ; row < 5; row++)
            for(int col = 0 ; col <5 ; col++)
                cin>>pans[p][row][col];
}

vector<vector<int>> rotate_pan(vector<vector<int>> pan, int d)
{
    if(d ==0) return pan;
    else 
    {
        vector<vector<int>> r_pan(5,vector<int>(5,0));
        if(d==1)
        {
            for(int r = 0 ; r < 5 ;r++)
                for(int c= 0 ; c < 5 ; c++)
                    r_pan[c][5-r-1] = pan[r][c];
        }
        else if(d==2)
        {
            for(int r = 0 ; r < 5 ;r++)
                for(int c= 0 ; c < 5 ; c++)
                    r_pan[5-r-1][5-c-1] = pan[r][c];
        }
        else if(d==3)
        {
            for(int r = 0 ; r < 5 ;r++)
                for(int c= 0 ; c < 5 ; c++)
                    r_pan[5-c-1][r] = pan[r][c];
        }

        return r_pan;
    }
}

typedef struct info{
    int p,r,c,len;
}info;

int dp[6] = {1,0,0,0,0,-1};
int dy[6] = {0,0,0,1,-1,0};
int dx[6] = {0,1,-1,0,0,0};

int bfs(vector<vector<vector<int>>> cube)
{
    int ret = 1e9;
    vector<vector<vector<bool>>> visited(5, vector<vector<bool>>(5, vector<bool>(5,false)));
    queue<info> q;
    q.push({0,0,0,0});

    while(!q.empty())
    {
        info pos = q.front();
        q.pop();
        if(visited[pos.p][pos.r][pos.c] || cube[pos.p][pos.r][pos.c] == 1)
            continue;
        visited[pos.p][pos.r][pos.c] = true;

        if(pos.p == 4 && pos.r == 4 && pos.c == 4)
            {
                ret = pos.len;
                break;
            }

        for(int d = 0 ; d < 6; d++)
        {
            int tp = pos.p + dp[d];
            int ty = pos.r + dy[d];
            int tx = pos.c + dx[d];
            if(tp>=0 && tp<5 &&ty>=0 && ty<5 &&tx>=0 && tx<5 && !visited[tp][ty][tx] && cube[tp][ty][tx] == 0)
                q.push({tp,ty,tx,pos.len+1});
        }
    }
    return ret;
}

void solve()
{
    vector<int> order = {0,1,2,3,4};
    int ans = 1e9;
    do{
        printf("hi\n");

        vector<vector<vector<int>>> cube(5, vector<vector<int>>(5, vector<int>(5,0)));;
        for(int a= 0 ; a < 4; a++)
        {
            printf("a\n");

            vector<vector<int>> pan_a = rotate_pan(pans[order[0]],a);
            copy(&pan_a[0][0],&pan_a[0][0]+25,&cube[0][0][0]);

            for(int b= 0 ; b< 4; b++)
            {
                printf("b\n");

                vector<vector<int>> pan_b = rotate_pan(pans[order[1]],b);
                copy(&pan_b[0][0],&pan_b[0][0]+25,&cube[1][0][0]);

                for(int c= 0 ; c < 4; c++)
                {                printf("c\n");

                    vector<vector<int>> pan_c = rotate_pan(pans[order[2]],c);
                    copy(&pan_c[0][0],&pan_c[0][0]+25,&cube[2][0][0]);

                    for(int d= 0 ; d < 4; d++)
                    {                printf("d\n");

                        vector<vector<int>> pan_d = rotate_pan(pans[order[3]],d);
                        copy(&pan_d[0][0],&pan_d[0][0]+25,&cube[3][0][0]);

                        for(int e = 0 ; e < 4; e++)
                            {                printf("e\n");

                                vector<vector<int>> pan_e = rotate_pan(pans[order[4]],e);
                                copy(&pan_e[0][0],&pan_e[0][0]+25,&cube[4][0][0]);
                                ans = min(ans, bfs(cube)); 
                            }  
                    }
                }
            }
        }
    }
    while(next_permutation(order.begin(), order.end()));

    if(ans == 1e9) ans = -1;
    cout<<ans;
}  

int main()
{
    input();
    solve();
}