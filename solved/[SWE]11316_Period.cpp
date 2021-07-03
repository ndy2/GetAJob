#include<string>
#include<iostream>
#include<vector>
#include <string.h>

using namespace std;

int map[1000001];

int main()
{
    int T;
    cin>>T;
    
    

    for(int tc = 1 ; tc <= T ; tc++)
    {
        memset(map, 0, sizeof(map));
        int s,p,q,m;
        int cur,next;
        int i=1;
        cin>>s>>p>>q>>m;
        cur = s;

        if(p == 0 )
            cout<<"#"<<tc<<" "<<1<<endl;
        else{
            bool done = false;
            int ans;
            while(!done)
            {
                if(map[cur]==0) map[cur] = i;
                else{
                    ans = i-map[cur];
                    done =true;
                } 
                i++;
                next = (p*cur+q)%m;
                cur = next;
            }
            
            cout<<"#"<<tc<<" "<<ans<<endl;
        }
        
    }

}