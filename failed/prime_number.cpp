#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <set>
#include <algorithm>



using namespace std;

bool is_prime(int num){
    bool flag=true;
    for(int i = 2; i <= num / 2; i++) {
       if(num % i == 0) {
          flag = false;
          break;
       }
    }
    return flag;
}

vector<vector<int>> number_to_permutations(int n)
{
    if(n == 1 )
        return {{0}};
    else
    {
        vector<vector<int>> cur;
        vector<vector<int>> prev = number_to_permutations(n-1);
        for(auto a : prev)
        {
            for(int i = 0 ; i <n ; i++)
                {
                    vector<int> b = a;  
                    b.insert(b.begin()+i,n-1);
                    cur.push_back(b);
                }
        }
        return cur;
    }
}

set<int> numbers_to_set(string numbers)
{
    set<int> ret;
    int n = numbers.length();
    vector<vector<int>> per = number_to_permutations(numbers.length());
    while (n!= 0)
    {
        for(auto a : per)
        {
            string str;
            for(auto b : a)
                str += numbers[b];
            ret.insert(stoi(str));
        }
        n --;
        
    }
        
    return ret;
}


int solution(string numbers) {
    int answer = 0;
    set<int> ret = numbers_to_set(numbers);

    for(auto i : ret)
        if(is_prime(i))
            answer++;

    return answer;
}

int main()
{
    // string numbers = "22";
    // int ans = solution(numbers);
    // cout<<ans<<endl;
    
    set<int> ret = numbers_to_set("22");
    for(auto a : ret)
        cout<<a<<endl;
}