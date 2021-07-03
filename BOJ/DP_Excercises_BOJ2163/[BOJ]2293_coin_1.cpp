#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;



int main()
{
    int n,k;
    cin>>n>>k;
    vector<int> pre(k+1,0); 
    vector<int> cur(k+1,0);

    vector<int> vals(n,0);
    for(int i = 0 ; i < n ; i++)
        cin>>vals[i];
    sort(vals.begin(), vals.end());

    int cost = vals[0];
    for(int c = 0 ; c <=k; c++)
        if(c%cost == 0 )
            pre[c] = 1;
    for(int r = 1; r < n ; r++)
    {
        int cur_cost = vals[r];
        for(int c = 0; c <=k ; c++)
            cur[c]=c<cur_cost?pre[c] : pre[c] + cur[c-cur_cost];
        pre = cur;
    }

    cout<<pre[k];   
}