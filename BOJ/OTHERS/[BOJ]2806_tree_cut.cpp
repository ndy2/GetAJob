#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> tree;

int N,H;

long long cutted_len(int t)
{
    long long len =0;
    int i = 0;
    while(tree[i] > t)
    {
        len += tree[i] - t;
        if(len > H)
            break;
        
        i++;
        if(i==N)
            break;
    }
    return len;
}

int main()
{
    cin>>N>>H;
    for(int i = 0 ; i < N ; i++)
    {
        int h;
        cin>>h;
        tree.push_back(h);
    }
    sort(tree.begin(), tree.end(),greater<int>());
    //이분 탐색
    int l,r,m;
    l = 1; r = tree[0];
    while(l<=r)
    {
        m = (l+r)/2;
        long long height = cutted_len(m);
        if(height >=H)
            l = m+1;
        else
            r = m-1;
    }
    cout<<r;
}