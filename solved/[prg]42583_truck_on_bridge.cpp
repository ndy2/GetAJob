#include <string>
#include <vector>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int arrived_cnt = 0;
    int cur_time = 0;
    vector<pair<int,int>> bridge; //무게, 진행상황 (다리위에서 보낸 시간)
    int ts = truck_weights.size();
    int weight_on_bridge = 0 ;
    while(arrived_cnt < ts)
    {
        cur_time++;
      //다리위 모든 트럭의 진행 상황 업데이트
        for(int i= 0 ; i <bridge.size() ; i ++)
            bridge[i].second++;
      
      //다리의 맨 앞 녀석이 도착할 수 있다면
        if(!bridge.empty() &&bridge[0].second == bridge_length)
        {
          //도착시키고 다리위의 무기 제거
            weight_on_bridge -= bridge[0].first;
            bridge.erase(bridge.begin());
            arrived_cnt++;
        }
      //견딜 수 있는 하중보다 대기 중인 트럭의 맨 앞 트럭 무게가 더 적다면
        int tolerable = weight - weight_on_bridge;
        if(!truck_weights.empty() && truck_weights[0] <= tolerable)
        {
          //트럭을 다리에 올리고 무게를 늘림 대기 트럭에서는 제거함
            bridge.push_back({truck_weights[0],0});
            weight_on_bridge += truck_weights[0];
            truck_weights.erase(truck_weights.begin());
        }    
    }
    return cur_time;
}

// 마지막 트럭을 다리에 실었을떄 다리의 길이 만큼을 cur_time에 추가해 return 함으로써 다리가 무지막지하게 긴 경우의 overhead를 줄일 수 있다.
