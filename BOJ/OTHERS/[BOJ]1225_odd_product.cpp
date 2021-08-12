#include <iostream>

using namespace std;

int main()
{
    unsigned long long ans =0;
    string A,B;
    cin>>A>>B;

    for(int i = 0 ; i < A.size(); i++)
        for(int j = 0 ; j <B.size();j++)
            ans +=(A[i]-'0') *(B[j]-'0');
    cout<<ans;
}