#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    unordered_map<string,int> um;
    
    for(auto c :clothes)
    {
        if(um.find(c[1]) == um.end())
            um[c[1]] = 1;
        else
            um[c[1]] ++;
    }
    
    int ans = 1;
    for (auto i : um)
    {
        ans *= i.second+1;
    }
    
    return ans-1;
}
