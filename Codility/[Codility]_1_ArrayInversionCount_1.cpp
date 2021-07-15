#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int solution(vector<int> &A)
{
    vector<int> list;
    int ans = 0;
    for(auto a : A)
    {
        vector<int>::iterator iter = upper_bound(list.begin(),list.end(),a);
        int pos = iter - list.begin();
        ans +=list.size()-pos;
        list.insert(iter, a);
        for(auto l : list)
            cout<<l<<" ";
        cout<<endl;
    }
    return ans;
}  

int main()
{
    vector<int> A ={-1,6,3,4,7,4};
    cout<<solution(A);
}