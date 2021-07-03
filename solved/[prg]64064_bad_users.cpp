#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

//banned id 별로 가능한 user_id의 index를 뽑는다.
vector<int> get_vi(string b, vector<string> user_id)
{
    int l = b.size();
    vector<int> vi;
    for(int i = 0 ; i < user_id.size() ; i++)
    {
        
        if(user_id[i].size() == l)
        {
            int j;
            for(j= 0 ; j < l ; j ++)
            {
                if(b[j]!='*' && b[j]!=user_id[i][j])
                    break;
            }
            if(j==l)
                vi.push_back(i);
        }
    }
    return vi;
}

vector<vector<int>> vvi;
int l;
set<set<int>> ssi;
int arr[9] = {0,};
set<int> s;

//dfs로 가능한 모든 조합을 고른다.
//set과 set의 size를 통해서 중복을 방지하고 최종 valid한 경우만 set의 set에 삽입한다.
//더 연습이 필요 한 부분이다.
//백준 백트래킹 N과 M 시리즈 문제를 공부하자.
void dfs(int y)
{
    if(y == l)
    {
        for(int i = 0 ; i <l ; i ++)
            s.insert(arr[i]);
        if(s.size() == l)
            ssi.insert(s);
        s.clear();
    }
    else{
        for(int i = 0 ; i < vvi[y].size() ; i ++)
        {
            arr[y] = vvi[y][i];
            dfs(y+1);
        }
    }
}


int solution(vector<string> user_id, vector<string> banned_id) {
    for (auto b : banned_id)
        vvi.push_back(get_vi(b,user_id));
    l = vvi.size();
    dfs(0);
    return ssi.size();
}

int main(){
    // cout<<solution({"frodo", "fradi", "crodo", "abc123", "frodoc"}, {"fr*d*", "abc1**"})<<endl;
    cout<<solution({"frodo", "fradi", "crodo", "abc123", "frodoc"}, {"fr*d*", "*rodo", "******", "******"})<<endl;

}