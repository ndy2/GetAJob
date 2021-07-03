#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

int nCr(int n, int r)
{
    r = min(r,n-r);
    int ret = 1;
    for(int i = 1; i <=r ; i++)
    {
        ret *= n+1-i;
        ret /= i;
    }
    return ret;
}



int main()
{
    int n;
    int map[101][101];
    cin>>n;
    for(int r = 1; r <=n ; r++)
        for(int c= 1; c <=n ; c++)
            cin>>map[r][c];
    
    long path[101][101];
    memset(path, 0, sizeof(path));
    path[1][1] = 1;

    for(int r = 1 ; r<=n ; r++)
    {
        for(int c = 1; c<=n ; c++)
        {
            if(path[r][c]==0) 
                continue;
            if(map[r][c] ==0)
                continue;

            int ty = r + map[r][c];
            int tx = c + map[r][c];

            if(tx<=n)
                path[r][tx] += path[r][c] ;

            if(ty<=n)
                path[ty][c] +=path[r][c] ; 
        }
    }
    cout<<path[n][n];
    return 0;
}   d