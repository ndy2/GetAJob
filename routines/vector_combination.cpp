#include <vector>
#include <algorithm>

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
