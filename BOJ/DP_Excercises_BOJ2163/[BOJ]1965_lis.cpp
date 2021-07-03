#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int n;
    vector<int> arr;
    vector<int> dp;
    cin>>n;
    int v;
    for(int i = 0 ; i < n ;  i++)
        {
            cin>>v;
            arr.push_back(v);
        }
    
    dp.push_back(arr[0]);
    for(int i = 1 ; i < n ; i ++)
    {
        int target = arr[i];
        vector<int>::iterator iter = lower_bound(dp.begin(), dp.end(), target);
        if(iter == dp.end())
        
            dp.push_back(target);
        else
        {
            dp.erase(iter);
            dp.insert(iter, target);
        }   
    }
    cout<<dp.size();
}   