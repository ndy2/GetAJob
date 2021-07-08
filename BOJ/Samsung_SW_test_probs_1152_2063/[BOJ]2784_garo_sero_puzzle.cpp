#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<string> words(6,"");

//      j a k
// ->i  A A A 
// ->b  A A A
// ->l  A A A 

//comb : i j k l a b
vector<string> comb2string(vector<int> comb)
{
    return {words[comb[0]] , words[comb[5]] , words[comb[3]]};
}

bool mysort(int a, int b)
{
    return words[a][0] < words[b][0] ? true:
           words[a][0] > words[b][0] ? false:
           words[a][2] > words[b][2] ? true:false;
}

int main()
{
    vector<string> ans = {"0"};
    for(int i = 0 ; i < 6 ; i++)
        cin>>words[i];
    
    for(int i = 0 ; i < 6 ; i++)
    {
        vector<int> comb;
        for(int j = 0 ; j < 6; j++)
        {
            if(i==j)
                continue;
            if(words[i][0] == words[j][0])
                {
                    for(int k = 0 ; k <6 ; k++)
                    {
                        if(k == i|| k ==j )
                            continue;
                        if(words[i][2] == words[k][0])
                            {
                                for(int l = 0 ; l <6 ; l++)
                                    {
                                        if(l == i || l == j || l == k)
                                            continue;
                                        if(words[j][2] == words[l][0] && words[k][2] == words[l][2])
                                        {   
                                            int a,b;
                                            vector<int> remains;
                                            for(int q= 0 ; q < 6; q++)
                                                if(q != i && q != j && q != k && q != l)
                                                    remains.push_back(q);
                                            a = remains[0];
                                            b = remains[1];
                                            if(words[a][1] == words[b][1])
                                            {
                                                sort(remains.begin(), remains.end(), mysort);
                                                a = remains[0];
                                                b = remains[1];
                                                
                                                if(words[i][1] == words[a][0] && words[l][1] == words[a][2] 
                                                    &&words[j][1] == words[b][0] && words[k][1] == words[b][2])
                                                     comb = {i,j,k,l,a,b};
                                            }
                                        }

                                    }
                            }
                    }
                }
        }
    
        if(!comb.empty())
            {
                ans = comb2string(comb);
                for(auto r : ans)
                    cout<<r<<endl;
                return 0;
            }
        
    }
    cout<<0;
    return 0;
    
}