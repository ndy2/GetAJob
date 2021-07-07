#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main()
{
    int N,T,ans=0;
    cin>>N>>T;
    
    string s;
    vector<string> rm;

    vector<int> e(26,0);
    for(int i = 0; i < N ; i++)
    {
        cin>>s;
        int l = s.size();
        string r = s.substr(4,l-8);
        rm.push_back(r);

        for(auto c : r)
            e[c-'a'] = 1;
            
    }
    if(T<=4)
    {
        cout<<ans;
        return 0;
    }
    int cnt = 0;
    map<int,int> idx2alpha;
    for(int i = 0 ; i < 26 ; i++)
    {
        if(i== 0 || i == 2 || i==8 || i==13 ||i==19)
            continue;
        if(e[i] == 1)
        {
            idx2alpha[cnt] = i;
            cnt++;
        }
    }       
    int num = cnt<T-5?cnt:T-5;
    vector<int> idx(cnt,0);
    fill_n(idx.end()-num ,num,1);

    do{
        vector<int> learned_idx;
        for(int i = 0 ; i < cnt; i++)
            if(idx[i] == 1)
                learned_idx.push_back(i);
        vector<int> alpha(26,0);
        alpha[0] = 1;
        alpha[2] = 1;
        alpha[8] = 1;
        alpha[13] = 1;
        alpha[19] = 1;
        
        for(int i = 0 ; i < learned_idx.size(); i++)
        {
            int t = idx2alpha[learned_idx[i]];
            alpha[t] =1;
        }
        int cur_ans = 0;
        for(auto s : rm)
        {
            bool can_learn = true;
            for(auto c : s)
            {
                if(alpha[c-'a'] == 0)
                    {
                        can_learn = false;
                        break;
                    }
            }
            if(can_learn)
                cur_ans++;
        }
        ans = max(cur_ans, ans);

    }while(next_permutation(idx.begin(), idx.end()));

    cout<<ans;
    return 0;
}