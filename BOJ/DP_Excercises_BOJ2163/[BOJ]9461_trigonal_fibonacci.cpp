#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

vector<long long> P(102,0);

void init_P()
{
    vector<long long> p10 = {1,1,1,2,2,3,4,5,7,9};
    for(int i = 0 ; i < 10 ; i++)
        P[i] = p10[i];
}

void activate_P()
{
    for(int i = 10; i<101; i++)
        P[i] = P[i-1] + P[i-5];
}

int main()
{
    int T,N ;
    cin>>T;

    init_P();
    activate_P();

    for(int tc = 0 ; tc<T ; tc++)
    {
        cin>>N;
        cout<<P[N-1]<<endl;
    }
}