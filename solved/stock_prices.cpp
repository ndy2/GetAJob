#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> prices) {
    int len = prices.size();
    vector<int> answer(len);
    
    for (int i = 0 ; i <len ; i++)
    {
        int count = 0 ;
        for(int j = i+1 ; j < len ; j++)
        {  
            if(j == i +1 && (prices[j]<prices [i]))
                {count = 1 ; j = len;}
            else if(prices[j] >= prices [i])
                count ++;
            else
                {j = len; count++;}
        }
        answer[i] = count;
    }

    return answer;
    
}

int main()
{
    vector<int> prices = {5,8,6,2,4,1};
    vector<int> ans = solution(prices);
    for (auto a : ans)
    {
        cout<<a<<endl;
    }
}