#include <string>
#include <vector>
#include <queue>
#include <iostream>

#define MIN(x,y) x<y?x:y
using namespace std;

int sub_sol(string s, int l)
{
    queue<string> spl;
    string red;
    string save=s.substr(0,l);
    string cur;
    int combo=0;
    for(auto c : s)
    {
        cur+=c;
        if(cur.size() == l)
        {
            spl.push(cur);
            cur.clear();
        }
            
    }
    spl.push(cur);
    cout<<endl;
    
    string apd_num;
    while(!spl.empty())
    {
        cur = spl.front();
        spl.pop();
        if(cur == save){
            combo+=1;
        }
        else{
            if(combo>1) apd_num = to_string(combo);
            else apd_num ="";
            red +=apd_num + save;
            save = cur;
            combo = 1;
            if(spl.empty()) red+=cur;
        }
    }
    return red.size();
}

int solution(string s) {
    if(s.size() == 1) return 1;
    int answer = 2000;
    int target = s.size()/2;
    int cur;
    for(int i = 1 ; i <= target ; i ++)
    {
        cur = sub_sol(s, i);
        answer = MIN(cur,answer);
    }
        
    return answer;
}
