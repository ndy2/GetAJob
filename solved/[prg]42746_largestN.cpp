#include <string>
#include <vector>
#include <algorithm>
using namespace std;


bool sort2(string a, string b)
{
    return b+a<a+b;
}

string solution(vector<int> numbers) {
    string answer = "";
    vector<string> ns;
    for(auto n : numbers)
        ns.push_back(to_string(n));
    sort(ns.begin(), ns.end(), sort2);
    
    for(auto n : ns)
        answer+=n;
    
    if(answer[0]=='0')
       answer = "0";
    return answer;
}
