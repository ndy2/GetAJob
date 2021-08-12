#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin>>n;
    vector<int> d(n,0);
    for(int i = 0 ; i < n ; i++)
        cin>>d[i];
    sort(d.begin(), d.end());
    cout<<d[0]*d[n-1];
}