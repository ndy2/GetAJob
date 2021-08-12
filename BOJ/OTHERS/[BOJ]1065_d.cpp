#include <iostream>
#include <vector>
using namespace std;

bool is_hansoo[1001];

void init(int N)
{
    for(int i =1; i<=N; i++)
    {
        string s = to_string(i);
        if(s.size()<=2)
            is_hansoo[i] = true;
        else{
            if(s[1]-s[0] == s[2]-s[1])
                is_hansoo[i] = true;
        }
    }
}

int get_ans(int N)
{
    int ans = 0;
    for(int i = 1; i<=N; i++)
        if(is_hansoo[i]) ans++;
    return ans;
}

int main()
{
    int N;
    cin>>N;
    init(N);
    printf("%d",get_ans(N));
}