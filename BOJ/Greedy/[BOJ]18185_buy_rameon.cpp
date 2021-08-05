#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int main()
{
    int N;
    cin>>N;
    vector<int> amounts = {0};

    int amount;
    int max_amount = -1;
    for(int i = 1 ; i <=N ; i++)
        {
            cin>>amount;
            amounts.push_back(amount);
            max_amount = max(max_amount , amount);
        }
    
    vector<int> prev_info(4,0);
    int money_sum = 0;
    for(int i = 1 ; i<=N ; i++)
    {
        int cur_amount = amounts[i];
        
        int cnt_one_2_two = min(prev_info[1], cur_amount);
        cur_amount -= cnt_one_2_two;
        int cnt_two_2_three = min(prev_info[2], cur_amount);
        cur_amount -= cnt_two_2_three;
        int cnt_one = cur_amount;

        money_sum -= 3*cnt_one_2_two;
        money_sum += 5*cnt_one_2_two;

        money_sum -= 5*cnt_two_2_three;
        money_sum += 7*cnt_two_2_three;

        money_sum += 3*cnt_one;

        prev_info[1] = cnt_one;
        prev_info[2] = cnt_one_2_two;
        prev_info[3] = cnt_two_2_three;
    }
    printf("%d",money_sum);
}