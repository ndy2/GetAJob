#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <map>

using namespace std;

typedef struct airport{
    string abr;
    bool checked;
}airport;

struct cmp{
    bool operator()(airport a, airport b)
    {
        return a.abr>b.abr;
    }
};

void dfs(map<string,priority_queue<string, vector<airport>, cmp>> mymap, string airport, vector<airport>& passed, int count , int n)
{
    if(mymap[airport].empty() && count == n)
        return;
    else if(mymap[airport].empty())
    {
        mymap[airport]
        dfs(mymap,)
    }

    
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<airport> answer = {{"ICN",0}};
    int n = tickets.size();
    map<string,priority_queue<string, vector<airport>, cmp>> mymap;
    
    for(auto t : tickets)
    {
        mymap[t[0]].push({t[1],0});
    }

    string cur = "ICN";
    string prev;
    dfs(mymap, "ICN", answer, 0, n);


    return answer;
}


int main()
{
    vector<vector<string>> tickets1 = {{"ICN","JFK"},{"HND","IAD"},{"JFK","HND"}};
    vector<vector<string>> tickets2 = {{"ICN","SFO"},{"ICN","ATL"},{"SFO","ATL"},
                                       {"ATL","ICN"},{"ATL","SFO"}};
    
    vector<string> answer = solution(tickets2);
    for (auto a : answer)
    {
        cout<<a<<endl;
    }    
}