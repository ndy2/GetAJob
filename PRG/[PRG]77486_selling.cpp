#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include<iterator>

using namespace std;

typedef struct node
{
    int parents;
    int idx;
    string name;
    int money;
}node;

node make_node(int parents, int idx, string name, int money)
{
    node n;
    n.parents = parents;
    n.idx = idx;
    n.name = name;
    n.money = money;
    return n;
}

vector<node> tree;
map<string,int> name_2_idx;

using namespace std;

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer;
    
    //make top
    node top = make_node(-1, 0, "-", 0);
    tree.push_back(top);
    name_2_idx["-"] = 0;
        
    int n = enroll.size();
    //generate inital tree
    for(int i = 0 ; i < n ; i ++)
    {
        int cur_idx = tree.size();
        int cur_money = 0;
        vector<string>::iterator iter = seller.begin();
        bool is_sell_done = false;
        
        while(!is_sell_done)
        {   
            iter = find(iter, seller.end(), enroll[i]);
            is_sell_done = iter == seller.end();
            if(!is_sell_done)
            {
                cur_money += amount[iter - seller.begin()];
            }
            iter ++;
        }
        
        node cur = make_node(name_2_idx[referral[i]], cur_idx, enroll[i],cur_money*100);
        tree.push_back(cur);
        name_2_idx[enroll[i]] = cur_idx;
        
    }
    
    
    
    return answer;
}

int main()
{
    vector<string> enroll = {"john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young"};
    vector<string> referral = {"-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward"};
    vector<string> seller = {"young", "john", "tod", "emily", "mary"};

    vector<int> amount = {12, 4, 2, 5, 10};

    vector<int> result = solution(enroll, referral, seller, amount);

    for(auto r : result)
    {
        cout<<r<<endl;
    }
}