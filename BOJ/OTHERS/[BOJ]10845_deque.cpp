#include <queue>
#include <iostream>

using namespace std;

int main()
{
    int N;
    cin>>N;
    deque<int> dq;
    while(N--)
    {
        string op;
        cin>>op;
        if(op=="push")
        {
            int val;
            cin>>val;
            dq.push_back(val);
        }
        else if(op=="front")
            if(dq.empty())
                printf("-1\n");
            else
                printf("%d\n",dq.front());
        
        else if(op=="back")
            if(dq.empty())
                printf("-1\n");
            else
                printf("%d\n",dq.back());
        
        else if(op=="size")
            printf("%d\n", dq.size());
        else if(op=="empty")
            printf("%d\n", dq.empty());
        else if(op=="pop")
            if(dq.empty()) 
                printf("-1\n");
            else
            {
                printf("%d\n", dq.front());
                dq.pop_front();
            }
    }
}