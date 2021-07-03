#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int arr[31] = {0,};
int can_get_from_right[31] ={0,};
int can_get_from_left[31] ={0,};

int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = 0;
    for(int i = 1 ; i <= n ; i ++)
        arr[i] = 1;
    
    for(auto l : lost)
    {
        arr[l] = 0;
    }
    for(auto r : reserve)
    {
        if(find(lost.begin(), lost.end(), r) == lost.end())
        {
            can_get_from_right[r-1]++;
            can_get_from_left[r+1]++;    
        }
        
        arr[r]+=1;
    }
   
    
    
    for(int i = 1 ; i <=n ; i ++)
    {
        if(arr[i]== 0 && can_get_from_right[i] ==1)
        {
            arr[i] = 1;
            arr[i+1] -=1;
            can_get_from_left[i+2]-=1;
        }
        else if(arr[i]== 0 &&can_get_from_left[i] ==1)
        {
            arr[i] = 1;
            arr[i-1] -=1;
            can_get_from_right[i-2]-=1;
        }
    }
    
    for(int i = 1; i <=n ; i ++)
    {
        if(arr[i] == 0 && (can_get_from_right[i] + can_get_from_left[i]) ==2)
        {
            arr[i] = 1;
            arr[i-1] -=1;
            can_get_from_right[i-2]-=1;
        }
    }
    
    for(int i = 1 ; i <=n ; i++)    
        answer+=arr[i]>=1?1:0;         
                
    return answer;
}