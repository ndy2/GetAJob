#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;


struct cmp{
    bool operator()(string s1, string s2){
        return s1<s2?true:
                (s2.size()<s1.size());
    }
};



string solution(vector<int> numbers) {
    string answer = "";
    priority_queue<string, vector<string>,cmp>  numbers_str;
    for(auto a : numbers)
    {
        numbers_str.push(to_string(a));
    }
    string cur;
    while(!numbers_str.empty())
    {
        cur = numbers_str.top();
        answer += cur;
        numbers_str.pop();
    }

    return answer;
}

int main()
{
    cout<<solution({6,10,2});
    cout<<solution({6,10,2});

}