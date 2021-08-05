#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int num_zero[1000001];

void init()
{
    int pow10[6] = {10, 100,1000,10000,100000,1000000};
    int num_mul[6] = {100000,10000,1000,100,10,1};
    num_zero[0] = 1;
    num_zero[1000000] = 6;
    for(int i = 0 ; i < 6 ; i++)
        {
            for(int j = 1 ; j < num_mul[i]; j++)
                num_zero[pow10[i] * j ] ++;

            if(i>=1)
                for(int j = 1 ; j < num_mul[i]; j++)
                    for(int k = 1 ; k < pow10[i-1] ; k++)
                        num_zero[pow10[i]*j +k] ++;
        }


}

int main()
{
    int TC;
    cin>>TC;
    init();
   
    int N,M;
    for(int tc = 1 ; tc<=TC ; tc++)
    {
        int ans = 0;
        cin>>N>>M;
        for(int i = N ; i <=M ; i++)
            ans+=num_zero[i];
        cout<<ans<<endl;
    }
}