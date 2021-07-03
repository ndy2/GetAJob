#include <string>
#include <iostream>
#include <vector>

#define MAX 2000000000
#define MIN -2000000000

using namespace std;

string solution(string s) {
    string answer = "";
    vector<int> list;
    int max = MIN;
    int min = MAX;
    bool flag = 1;
    while(flag)
    {
        int cur;
        int idx = s.find_last_of(' ');
        if(idx != -1){
            int pop_len = s.length() - idx;
            cur = stoi(s.substr(idx+1, s.length()-1));
            if(cur>max) max = cur;
            if(cur<min) min = cur;
       
        while(pop_len--)
            s.pop_back();     }
        else
        {
            cur = stoi(s);
            if(cur>max) max = cur;
            if(cur<min) min = cur;
            flag = 0;
        }
        
    }
    answer = to_string(min)+" "+to_string(max); 
    return answer;
}

int main()
{
    string s = "-1 -2 -3 -4";
    cout<<solution(s)<<endl;
}