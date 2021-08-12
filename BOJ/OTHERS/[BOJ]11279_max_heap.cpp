#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N;

int main()
{
    cin>>N;
    priority_queue<int,vector<int>, less<int>> pq;

    while(N--)
    {
        int in;
        scanf("%d",&in);
        if(in==0)
        {
            if(pq.empty()) printf("%d\n",0);
            else {
                int out = pq.top();
                printf("%d\n",out);
                pq.pop();
            }
        }
        else pq.push(in);
    }
}