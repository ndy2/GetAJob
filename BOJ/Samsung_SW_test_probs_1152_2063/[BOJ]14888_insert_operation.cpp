#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef struct info{
    vector<int> nop;
    deque<int> A;
}info;

deque<int> op(deque<int> A, int oper)
{
    int a = A.front();
    A.pop_front();
    int b = A.front();
    A.pop_front();
    int c;
    switch(oper)
    {
        case 0 : {
            c = a+b;
            break;
        }
        case 1 : {
            c = a-b;
            break;
        }
        case 2 :{
            c = a*b;
            break;
        }
        case 3 : {
            c = a/b;
            break;
        }
    }
    A.push_front(c);
    return A;
}

int main() {
    int N,a;
    int min_ans = 1e9;
    int max_ans = -1e9;
    
    vector<int> nop(4);
    deque<int> A;

    cin>>N;
    for(int i = 0 ; i < N ; i++)
        {
            cin>>a;
            A.push_back(a);
        }
    for(int i = 0 ; i < 4 ; i++)
        cin>>nop[i];

    queue<info> q;
    q.push({nop,A});
    while(!q.empty())
    {
        info f = q.front();
        q.pop();
        vector<int>p_op, r_op = f.nop;
        deque<int> p_A, r_A = f.A;
        if(r_A.size() == 1)
        {
            max_ans = max(max_ans, r_A.front());
            min_ans = min(min_ans,r_A.front());        
        }
        else{
            for(int i = 0 ; i < 4 ; i ++)
            {
                if(r_op[i]>0)
                {
                    p_A = op(r_A, i);
                    p_op = r_op;
                    p_op[i]-=1;
                    info p = {p_op, p_A};
                    q.push(p);
                }
            }
        }
    }
    cout<<max_ans<<"\n"<<min_ans;
}       