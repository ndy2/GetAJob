#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

map<string,int> airport_map;

bool iss_empty(vector<vector<string>> t_map)
{
    int l = 0 ;
    for(auto v : t_map)
        {
            l += v.size();
            if(l!=0)
                return false;
        }
    return true;
}

bool dfs(string from, vector<vector<string>>& t_map, vector<string> & answer , vector<string> & real_ans)
{
    if(iss_empty(t_map) || real_ans.size()!=1)
        return true;
    else{
        vector<string> des =  t_map[airport_map[from]];
        for(int i = 0 ; i < des.size(); i++ )
        {   
            if(iss_empty(t_map) || real_ans.size()!=1)
                return true;
            des =  t_map[airport_map[from]];
            string target = des[i];
            answer.push_back(target);
            des.erase(des.begin() + i);
            t_map[airport_map[from]] = des;
            
            if(iss_empty(t_map))
                real_ans = answer;
            if(!dfs(target, t_map, answer,real_ans))
                {
                    des.insert( des.begin() + i, target);
                    t_map[airport_map[from]] = des;
                    answer.pop_back();
                }
        }
        return false;

    }
}


vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer ={"ICN"};
    vector<string> airports;
    auto cmp = [](string a, string b){return a<b;};
    for(auto t : tickets)
        for(auto a : t)
            if(find(airports.begin(), airports.end(), a) == airports.end())
                airports.push_back(a);
    sort(airports.begin(), airports.end(), cmp);
    for(int i = 0 ; i< airports.size(); i++)
        airport_map[airports[i]] = i;
    vector<vector<string>> t_map;

    for(int i = 0 ; i < airports.size(); i ++)
    {
        vector<string> to;
        for(auto t : tickets)
        {
            if(t[0] == airports[i])
                to.push_back(t[1]);
        }
        t_map.push_back(to);
    }
    for(int i = 0 ; i < t_map.size() ; i ++)
        sort(t_map[i].begin(), t_map[i].end());

    vector<string> real_ans = {""};
    dfs("ICN", t_map , answer, real_ans);

    return real_ans;

}

int main()
{
    vector<vector<string>> tickets = {{"ICN", "JFK"},
                                      {"HND", "IAD"},
                                      {"JFK", "HND"}};
    vector<vector<string>> tickets2 = {{"ICN", "SFO"}, {"ICN", "ATL"}, {"SFO", "ATL"}, {"ATL", "ICN"}, {"ATL","SFO"}};
    vector<vector<string>> tickets3 = {{"ICN","A"},{"A","B"},{"B","A"},{"A","ICN"},{"ICN","A"}};
    vector<vector<string>> tickets4 = { { "ICN", "COO" }, { "ICN", "BOO" }, { "COO", "ICN" } };

  
    // for(auto s : solution(tickets))
    //     cout<<s<<" ";
    // cout<<endl;
     for(auto s : solution(tickets2))
        cout<<s<<" ";
    cout<<endl;
    //  for(auto s : solution(tickets3))
    //     cout<<s<<" ";
    // cout<<endl;

    //  for(auto s : solution(tickets4))
    //     cout<<s<<"**";
    // cout<<endl;
}