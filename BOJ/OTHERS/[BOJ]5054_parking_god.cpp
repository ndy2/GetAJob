#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int TC;
    cin>>TC;
    for(int tc = 1 ; tc <=TC; tc++)
    {
        int N;
        cin>>N;
        vector<int> arr(N,0);
        int sum = 0;
        int avg;
        for(int i = 0 ; i < N ; i++)
            cin>>arr[i];
        cout<<2 * (*max_element(arr.begin(), arr.end())- (*min_element(arr.begin(), arr.end())) )<<endl;
    }
}
