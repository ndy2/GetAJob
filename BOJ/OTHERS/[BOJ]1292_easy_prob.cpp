#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int arr[1001];

void init_arr()
{
    int num = 1;
    int idx = 1;
    int cnt = 0;
    while(idx<=1000)
    {
        arr[idx]=num;
        cnt++;
        idx++;
        if(cnt==num)
            {
                cnt = 0;
                num++;
            }
    }
}

int main()
{
    init_arr();

    int A,B;
    cin>>A>>B;
    int ans = 0;
    for(int i = A ; i <=B ; i++)
        ans+=arr[i];
    cout<<ans;
}
