#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<vector<int>> get_comb(vector<int> menu_pan, int n)
{
    vector<vector<int>> res;
    vector<int> one;
    int l = menu_pan.size();
    int loop_n = 0 ;
    while(loop_n < l - n+1)
    {
        for(int i = loop_n ; i < l ; i++){
            one.push_back(menu_pan[i]);
            {
                if(one.size() == n )
                {
                    if(find(res.begin(), res.end(), one) == res.end())
                    {
                        res.push_back(one);
                        one.pop_back();
                    }
                    else{
                        one.pop_back();
                    }
                }
            }
        }
        loop_n +=1;
        one.clear();
    }

    return res;

}
