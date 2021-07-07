#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

int N;
int map[2][3];
int dp[2][3];

void solve()
{
    cin>>N;
    int a,b,c;
    int aa,bb,cc;
    int e,f,g;
    cin>>a>>b>>c;
    aa = a ; bb= b; cc = c;
    int dp_max[3];
    int dp_min[3];
    for(int r= 1 ; r < N ; r++)
        {
            cin>>e>>f>>g;
            dp_max[0] = max(a, b) + e;
            dp_max[1] = max(max(a, b),c) + f;
            dp_max[2] = max(b,c) +g;

            dp_min[0] = min(aa, bb) + e;
            dp_min[1] = min(min(aa, bb),cc) + f;
            dp_min[2] = min(bb,cc) +g;


            a = dp_max[0];
            b = dp_max[1];
            c = dp_max[2];

            aa = dp_min[0];
            bb = dp_min[1];
            cc = dp_min[2];
        }
    cout<<max(max(a, b),c)<<" ";
    cout<<min(min(aa, bb),cc);
}


int main()
{
    solve();
}