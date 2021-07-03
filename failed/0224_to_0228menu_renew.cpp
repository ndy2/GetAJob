#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool menu_arr[26];

//next permutation을 써서 combination구함
vector<vector<int>> get_comb2(vector<int> menu_pan, int n)
{
    vector<vector<int>> res;
    vector<int> ind;
    int l = menu_pan.size();

    for(int i = 0 ; i < n ; i ++)
        ind.push_back(1);
    
    for(int i = 0 ; i < l - n ; i ++)
        ind.push_back(0);
    
    sort(ind.begin(), ind.end());

    do{
        vector<int> cur;
        for(int i = 0 ; i < l ; i++)
        {
            if(ind[i] == 1)
                cur.push_back(menu_pan[i]);
        }
        res.push_back(cur);
    }while(next_permutation(ind.begin(), ind.end()));

    return res;
}


//vector<int> -> string e.g. {0,4} -> AE
string to_alpha(vector<int> v)
{
    string s;
    for(int i : v)
        s.push_back(i+'A');
    return s;
}

//후보하나를 체크하며 몇개 등장한지 구함
int check_cand_one(vector<int> cand_one, vector<string> orders)
{
    int count=0;
    for(auto o : orders)
    {
        bool cur = false;
        int cur_count = 0 ;
        for(auto c: cand_one)
        {
            if(o.find(c+'A')!= -1)
                cur_count ++;
            if(cur_count == cand_one.size())
                cur =true;
        }
        if(cur)
            count+=1;
    }
    return count;
}


//시작
vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    
    //string당 주문 횟수 저장 중복제거 용으로 사용됨
    vector<pair<string, int>> answer_val;

    //주문가능한 모든 메뉴를 오름차순으로 저장함 (e.g. A,E 만 주문 가능 하면 {0,4})
    vector<int> menu_pan;
    for(string s : orders)
        for(char c : s)
            if(menu_arr[c-'A'] == false)
                menu_arr[c-'A'] = true;

    for(int i = 0 ; i < 26 ; i++)
        if(menu_arr[i]==true)
            menu_pan.push_back(i);

    //course를 돈다 중복제거를 위해 큰 숫자부터 실행할 필요 있음 걍 냅둠
    for(int n : course)
    {
        //n에 따른 가능한 모든 후보
        vector<vector<int>> cand = get_comb2(menu_pan,n);
        
        //모든 후보를 돌며
        for(auto cand_one : cand)
        {
            // 몇개인지 셈
            int count = check_cand_one(cand_one, orders);
            
            //두개 이상이고 중복이 아니면 두 벡터에 저장함
            if(count >=2 && !is_duplicated(answer_val, cand_one))  
            {
                answer_val.push_back(make_pair(to_alpha(cand_one), count));
                answer.push_back(to_alpha(cand_one));
            }
        }
    }
    
    return answer;
}


int main()
{
    // vector<int> menu_pan = {1,2,3,4,5,6,7};
    // vector<vector<int>> candidate= get_comb2(menu_pan, 3);
    // for(auto a : candidate)
    //     {
    //         for(auto b: a)
    //         {
    //             cout<<b<<" ";
    //         }
    //         cout<<endl;
    //     }

    vector<string> orders ={"ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH"};
    vector<int> course = {2,3,4};
    vector<string> result = solution(orders,course);
    for(auto a : result)
        {
           cout<<a<<" ";
        }
}