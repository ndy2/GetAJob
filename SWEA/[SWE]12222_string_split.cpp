#include <iostream>
#include <vector>
#include <string>

using namespace std;

string S;

void input()
{
    cin>>S;
}

void solve(int tc)
{
    int cnt = 0;
    int idx = 0;
    char prev_last_char = '0';
    bool is_prev_two = false;
    while(1)
    {
        cnt++;
        char cur_front = S[idx];
        // cout<<"prev_last : "<<prev_last_char<<" cur_front : "<<cur_front<<endl;
        if(idx == S.size()-1 && cur_front == prev_last_char && !is_prev_two)
        {
            idx++;
            cnt--;
        }
        if(prev_last_char == cur_front && !is_prev_two)
        {
            is_prev_two = true;
            idx+=2;
        }
        else
        {
            is_prev_two = false;
            idx+=1;
        }
        prev_last_char = S[idx-1];
        if(idx >= S.size())
            break;
    }    
    cout<<"#"<<tc<<" "<<cnt<<endl;
}

int main()
{
    int TC;
    cin>>TC;
    for(int tc =1 ; tc<=TC; tc++)
    {
        input();
        solve(tc);
    }    
}