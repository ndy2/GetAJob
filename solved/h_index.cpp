#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#define MIN(A,B) (A)<(B)?(A):(B)
using namespace std;

bool sortFunc(int& a, int&b)
{
    return b<a;
}

int solution(vector<int> citations) {
    sort(citations.begin(), citations.end(), sortFunc);
    
    int len = citations.size();
    int cur = 0;
    int count = 1;
    while(citations[cur]> count)
    {
        count ++;
        cur ++;
    }
    return MIN(citations[cur-1], count-1);
}   

int main()
{
    vector<int> citations3 = {10,10,10};

    cout<<solution(citations3)<<endl;

}