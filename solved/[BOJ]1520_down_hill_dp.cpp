#include <string>
#include <vector>
#include <iostream>
#define ROW_MAX  501
#define COL_MAX  501

using namespace std;

int dp[ROW_MAX][COL_MAX];
bool determined[ROW_MAX][COL_MAX];
int H[ROW_MAX][COL_MAX];


typedef struct cor{
    int y;
    int x;
}cor;


vector<cor> d = {{0,-1}, {-1,0}, {0,1}, {1,0}}; // direction in (y,x) , left, above, right, below

void set_dp(int r, int c, int M, int N)
{
    if(determined[r][c])
        return;
    else
    {
        vector<cor> determined_valid_neighborhood;
        vector<cor> undetermined_valid_neighborhood;
        for(int i = 0 ; i < 4 ; i ++)
        {
            cor candidate = {r+ d[i].y,  c + d[i].x};
            //valid cor test
            if(candidate.y > 0 && candidate.y <= M && 
                candidate.x > 0 && candidate.x <= N )
                {
                    // compare test
                    if(H[candidate.y][candidate.x] > H[r][c] )
                    {
                        //determined test
                        if(determined[candidate.y][candidate.x])
                            determined_valid_neighborhood.push_back(candidate);
                        else
                            undetermined_valid_neighborhood.push_back(candidate);
                    }
                }
        }

        //dp_r_c : dp[r][c] temp val
        int dp_r_c = 0;

        //if undetermined set dp for cordinates
        for(auto u : undetermined_valid_neighborhood)
                set_dp(u.y,u.x,M,N);
        
        //add up all dp[r][c] of determined valid neighborhood
        //undetermined_valid_neighborhood contains determined neighborhood now
        for(auto u : undetermined_valid_neighborhood)
            dp_r_c += dp[u.y][u.x];
        
        for(auto d : determined_valid_neighborhood)
            dp_r_c += dp[d.y][d.x];
        
        //set dp[r][c] and determined[r][c]
        dp[r][c] = dp_r_c;
        determined[r][c] = 1;

    }
}

int solution(int M, int N ) 
{   
    dp[1][1] = 1;
    determined[1][1] = 1;
    for(int r = 1 ; r <= M ; r ++)
        for(int c = 1 ; c <= N ; c ++)
            set_dp(r,c,M,N);
    return dp[M][N];
}

int main()
{
    int M, N, c;
    scanf("%d %d", &M,&N); 
    for(int i = 1 ; i <= M ; i ++ )
    {
        for(int j = 1 ; j <= N ; j ++)
        {
            scanf("%d", &c );
            H[i][j] = c;
        }   
    }

    cout<<solution(M,N);    
    return 0;      
}