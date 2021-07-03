#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int arrived_cnt = 0;
    int cur_time = 0;
    vector<pair<int,int>> bridge;
    int ts = truck_weights.size();
    int weight_on_bridge = 0 ;
    while(arrived_cnt < ts)
    {
        cur_time++;
        for(int i= 0 ; i <bridge.size() ; i ++)
            bridge[i].second++;
        if(!bridge.empty() &&bridge[0].second == bridge_length)
        {
            weight_on_bridge -= bridge[0].first;
            bridge.erase(bridge.begin());
            arrived_cnt++;
        }
        int tolerable = weight - weight_on_bridge;
        if(!truck_weights.empty() && truck_weights[0] <= tolerable)
        {
            bridge.push_back({truck_weights[0],0});
            weight_on_bridge += truck_weights[0];
            truck_weights.erase(truck_weights.begin());
        }
                 
    }
    
    return cur_time;
}
int main()
{
    // cout<<solution(2,10,{7,4,5,6})<<endl;;
    // cout<<solution(100,100,{10})<<endl;;
    cout<<solution(100,100,{10,10,10,10,10,10,10,10,10,10})<<endl;;

}