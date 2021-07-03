#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int sub_sol(string number, int k)
{
    string answer = "";
    int l = number.size();
    int idx = max_element(number.begin(), number.begin() + k +1) - number.begin();
    return  idx;
}

string solution(string number, int k) {
    string answer;
    int bf = 0;
    int sz = number.size();
    string number_save = number;
    int offset = 0;
    while(k>0 )
    {
        int idx = sub_sol(number, k);
        number =  number.substr(idx+1, number.size() - idx);
        answer.push_back(number_save[idx + offset]);
        k-= idx;
        offset += idx+1;
        if(answer.size() == sz-k)
            return answer;
    }
    answer += number;
    
    return answer;
}

int main()
{
    // cout<<solution("1924",2)<<endl;
    // cout<<solution("1231234",3)<<endl;
    // cout<<solution("4177252841",4)<<endl;
    cout<<solution("1111",2)<<endl;

}