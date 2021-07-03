#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool glb_fail;

vector<string> split_string(string s)
{
    vector<string> vs;
    string cur;
    for(auto c : s)
    {
        cur +=c;
        if(c =='0')
        {
            if(cur.size() == 1)
                {
                    glb_fail = true;
                    break;
                }
            else if(cur[cur.size()-2] !='1' && cur[cur.size()-2] !='2')
                {
                    glb_fail = true;
                    break;
                }
            else{
                    char last_int =  cur[cur.size()-2];
                    cur.pop_back();
                    cur.pop_back();
                    if(!cur.empty())
                        vs.push_back(cur);

                    string ten_or_twenty;
                    ten_or_twenty +=last_int;
                    ten_or_twenty +='0';
                    vs.push_back(ten_or_twenty);
                    cur.clear();  
                }
        }
        else if(c>='3' && c <='9')
            {
                vs.push_back(cur);
                cur.clear();
            }
    }
    if(!cur.empty())
        vs.push_back(cur);
    return vs;
}

int split_case(string s)
{
    int l = s.size();
    s.push_back('e');
    s.push_back('e');
    int bar=l;

    for(int i = 0 ; i <= l ; i++)
    {
        bool check_one = s[i]=='1' && (s[i+1]>='0'&&s[i+1]<='9');
        bool check_two = s[i]=='2' && (s[i+1]>='0'&&s[i+1]<='6');
        bool check_end = s[i] + s[i+1] == 'e'+'e';
        if(check_one || check_two || check_end)
        {
            bar = i;
            break;
        }
    }
    if(bar == l)
        return 1;
    
    if((s[0]=='1'||s[0]=='2') && s[1]=='0')
        return 1;
    
    vector<int> dp(l+1,0);

    dp[0] = 1;
    for(int i = 0 ; i <l-1; i++)
        {   

            dp[i+1] += dp[i];
            dp[i+1] %=1000000;

            dp[i+2] += dp[i];
            dp[i+2] %=1000000;
        }

    return (dp[l-1] + dp[l])%1000000;
}

int main()
{
    string crypto_code;
    cin>>crypto_code;
    vector<string> vs = split_string(crypto_code);
    if(glb_fail)
    {
        cout<<0;
        return 0;
    }
        
    int ans = 1;
    for(auto s : vs)
    {
        ans *= split_case(s);
        ans %= 1000000;
    }
        
    cout<<ans;
}