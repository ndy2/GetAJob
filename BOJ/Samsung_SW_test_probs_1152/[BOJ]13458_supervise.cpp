#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    long N, B,C;
    cin>>N;
    vector<long> Ai(N,0);

    for(int i = 0 ; i < N ; i ++)
        cin>>Ai[i];
    cin>>B>>C;

    long ans=0;
    for(auto a : Ai)
    {
        ans +=1;
        a-=B;
        if(a>0)
            ans+=ceill((float)a/C);
    }
    cout<<ans;
}       