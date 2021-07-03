#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int solution(vector<int> numbers, int target) {
    int answer = 0;
    int l = numbers.size();
    
    queue<vector<int>> q;
    q.push({0,numbers[0]});
    q.push({0,-numbers[0]});

    while(q.empty())
    {
        vector<int> p = q.front();
        int idx = p[0];
        int partial = p[1];
        if(idx ==l-1 && partial == target)
            answer ++;
        q.pop();
        
        if(idx+1 <l)
        {
           q.push({idx+1,partial + numbers[idx+1]});
           q.push({idx+1,partial - numbers[idx+1]}); 
        }
    }
    
    return answer;
}
int main()
{
    cout<<solution({1,1,1,1,1},3)<<endl;
}