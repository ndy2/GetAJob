#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
   int ans = 0;
   int N,K;
   cin>>N>>K;

   int cnt = 0;
   int cur = 1;
   while(1)
   {
       if(N%cur==0)
            cnt++;
        // printf("cur , cnt : %d %d\n",cur,cnt);
       if(cnt == K){
            ans = cur;
            break;
       }
       if(cur > N)
            break;
       cur++;
   }
   cout<<ans;
}