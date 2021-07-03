#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>


using namespace std;

int N;

// 17x17 : grid , 3 : garo, sero, daegak
int map[17][17][3];
int wall[17][17];

void input()
{
   cin>>N;
   for(int r= 1; r <=N ; r++)
      for(int c = 1; c <=N ; c++)
         cin>>wall[r][c];
}

void solve()
{
   map[1][2][0] = 1;
   for(int r = 1 ; r <= N ; r ++)
      for(int c = 1; c <= N ; c++)
      {
         vector<vector<int>> t;
         t={ {r,c+1}, {r+1,c}, {r+1,c+1}};
         
         bool garo_valid   = t[0][0] >=1 && t[0][0]<=N && t[0][1] >=1 && t[0][1]<=N && (wall[t[0][0]][t[0][1]] != 1);
         bool sero_valid   = t[1][0] >=1 && t[1][0]<=N && t[1][1] >=1 && t[1][1]<=N && (wall[t[1][0]][t[1][1]] != 1);
         bool daegak_valid = garo_valid && sero_valid && 
                            (t[2][0] >=1 && t[2][0]<=N && t[2][1] >=1 && t[2][1]<=N && (wall[t[2][0]][t[2][1]] != 1));

         if(garo_valid) map[t[0][0]][t[0][1]][0] += map[r][c][0] + map[r][c][2];
         if(sero_valid) map[t[1][0]][t[1][1]][1] += map[r][c][1] + map[r][c][2];
         if(daegak_valid) map[t[2][0]][t[2][1]][2] += map[r][c][0] + map[r][c][1] + map[r][c][2];
      
      }

   int ans = map[N][N][0] + map[N][N][1] + map[N][N][2];
   cout<<ans;
}

int main()
{
   input();
   solve();
}