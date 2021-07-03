#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int solution(vector<int> scoville, int K) {
    priority_queue<int,vector<int>, greater<int>> pq;
    for(auto s : scoville)
        pq.push(s);
    
    int answer = 0;
    int target;
    while(pq.size()>=2)
    {
        answer++;
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        target = a + 2*b;
        pq.push(target);
        if(pq.top() >=K)
            break;
        if(pq.top() < K)
            return -1;
    }
    return answer;
}

int main(){
    // cout<<solution({1,2,3,9,10,12},7)<<endl;
    cout<<solution({1,2,3,9,10,12},500)<<endl;

}