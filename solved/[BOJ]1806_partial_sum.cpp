#include <vector>
#include <iostream>
#define MIN(x,y) ((x)<(y)?(x):(y))
using namespace std;


int main()
{
    int N, S;
    cin >>N>>S;

    vector<int> arr = vector<int>(N,0);
    for(int i = 0 ; i < N ; i++)
        scanf("%d",&arr[i]);
        
    int l = 0;
    int r = 0;
    int psum = 0;
    int min_len = N+1;
    while(l<=r)
    {
        if(psum >= S)
            {
                min_len = MIN(min_len, r-l);
                psum-=arr[l];
                l++;
            }
        else if(r == N) break;
        else{
                psum+=arr[r];
                r++;
            } 
        
    }

    if(min_len == N+1)
        min_len = 0;

    printf("%d",min_len);
   
    return 0;
}
