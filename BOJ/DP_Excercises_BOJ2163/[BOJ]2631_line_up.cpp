#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

//~ N- len(LIS)

void solve()
{
    int N;
    int arr[201];
    cin>>N;
    for(int i = 0; i < N ; i++)
        cin>>arr[i];
    
    vector<int> dp(N,0);
    int max = arr[0];
    dp[0] = arr[0];
    int idx = 0;

    for(int i = 1 ; i < N ; i++)
    {
        if(arr[i] > max)
            {
                idx++;
                dp[idx] = arr[i];
                max = arr[i];
            }
        else
            {
                int target_idx = 0;
                while(arr[i]> dp[target_idx])
                    target_idx++;
                dp[target_idx] = arr[i];

                if(target_idx == idx) 
                    max = arr[i];
            }
    }
    
    cout<<N-idx-1;
}


int main()
{
    solve();
}