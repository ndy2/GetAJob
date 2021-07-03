#include<iostream>
#include<vector>
#include <string.h>
#include <algorithm>
#define ull unsigned long long int

using namespace std;

ull candy[101];
ull bag[101];

int main()
{
    int T;
    cin>>T;
    
    for(int tc = 1 ; tc <= T ; tc++)
    {
        memset(candy,0,sizeof(candy));
        memset(bag,0,sizeof(candy));

        int N;
        ull M;
        cin>>N>>M;
        for(int i = 0 ; i < N ; i ++)
            cin>>candy[i];
        sort(candy, candy+N , greater<ull>());

        ull used = 1;
        bag[0] = 1;
        int idx = 0;
        while(used < M)
            {
                if(idx == N-1)
                    idx = 0;
                else if(candy[0]/(bag[0]+1) <candy[idx+1]/(bag[idx+1]+1))
                    idx= idx+1;
                else
                    idx= 0;

                bag[idx]+=1;
            }
        
        
        for(int i = 0 ; i < N ; i ++)
            if(bag[i]!=0) candy[i]/=bag[i];
        
        ull ans = *min_element(candy,candy+N);
        

        cout<<"#"<<tc<<" "<<ans<<endl;

    }

}