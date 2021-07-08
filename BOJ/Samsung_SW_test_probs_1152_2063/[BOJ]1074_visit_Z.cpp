#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int ans = 0;

void rec(int N, int r ,int c)
{
    if(N==1)
    {
        ans += 2*r+c;
        return;
    }
    else
    {
        //사분면 판정
        int quadrant = 0;
        int criteria = pow(2, N-1);
        int amount = pow(pow(2,N-1),2);
        int new_r = r, new_c =c ;
        if(r >= criteria)
            { quadrant +=2; new_r -=criteria;}
        if(c>=criteria)
            {quadrant +=1;new_c -=criteria;}
        ans += quadrant * amount;
        
        rec(N-1, new_r, new_c);
    }
}

int main()
{
    int N,r,c;
    cin>>N>>r>>c;
    rec(N,r,c);

    cout<<ans;
}