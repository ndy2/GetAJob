#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

vector<vector<int>> map;
queue<pair<int,int>> q;
bool visited[51];

bool is_char_diff(string s, string t)
{
    int ls = s.size();
    int lt = t.size();
    if(ls!= lt) return false;
    int count = 0;
    for(int i = 0 ; i < ls; i++)
        {
            if(s[i] != t[i])
                count++;
            if(count >=2)
                return false;
        }
    if(count ==1)
        return true;
    else    
        return false;
}

int bfs(int from, int to)
{
    visited[from] = true;
    q.push({from,0});
    while(!q.empty() && q.front().first != to)
    {
        int t = q.front().first;
        int c = q.front().second;
        q.pop();
        for(int s : map[t])
            {
                if(!visited[s]) 
                {
                    visited[s]=true;
                    q.push({s,c+1});
                    
                }
            }
    }

    if(q.empty())  return 0;
    else return q.front().second;

}

int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    words.push_back(begin);
    for(int i = 0 ; i < words.size() ; i ++)
    {
        vector<int> cur;
        for(int j = 0 ; j < words.size(); j++)
        {
            if(i!=j && is_char_diff(words[i], words[j]))
            cur.push_back(j);
        }
        map.push_back(cur);
    }

    int target_idx = find(words.begin(), words.end(), target) - words.begin();
    if(target_idx == words.size()) return 0;



    return bfs(words.size()-1, target_idx);
}

int main()
{
    string begin = "hit";
    string target = "cog";
    vector<string> words = {"hot", "dot", "dog", "lot", "log", "cog"};

    cout<<solution(begin, target, words);
}