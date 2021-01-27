#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <utility>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;


vector<vector<int>> number_to_permutations(int n)
{
    if(n == 1 )
        return {{0}};
    else
    {
        vector<vector<int>> cur;
        vector<vector<int>> prev = number_to_permutations(n-1);
        for(auto a : prev)
        {
            for(int i = 0 ; i <n ; i++)
                {
                    vector<int> b = a;  
                    b.insert(b.begin()+i,n-1);
                    cur.push_back(b);
                }
        }
        return cur;
    }
}


bool test(vector<int> p , vector<string>data, map<char,int> freinds_map)
{
    for(auto d : data)
    {
        int f1 = freinds_map[d[0]];
        int f2 = freinds_map[d[2]];
        
        int pos1 = find(p.begin(),p.end(),f1) - p.begin();
        int pos2 = find(p.begin(),p.end(),f2) - p.begin();
        int act = d[4] -'0' +1;
        switch(d[3])
        {
            case '=':
            {
                if(!(abs(pos1-pos2) == act))
                    return false;
                break;
            }
        
            case '>':
            {
                if(!(abs(pos1-pos2) > act))
                    return false;
                break;
            }
        
            case '<':
            {
                if(!(abs(pos1-pos2) < act))
                    return false;
                break;
            }
        }
    }
    return true;
}

int solution(int n, vector<string> data) {
    
    vector<vector<int>> permutation = number_to_permutations(8);
    map<char,int> freinds_map;
    int val = 0;
    int val1, val2;
    for(auto d : data)
    {
        if(freinds_map.find(d[0]) == freinds_map.end())
            {
                freinds_map.insert(make_pair(d[0],val));
                val++;
            }
        if(freinds_map.find(d[2]) == freinds_map.end())
            {
                freinds_map.insert(make_pair(d[2],val));
                val++;
            }

    }

    int count = 0;
    for(auto p : permutation)
    {
        if(test(p,data,freinds_map))
            count ++;
    }

    return count;
}

int main()
{
    int n = 2;
    vector<string> data1 = { "N~F=0", "R~T>2"};
    vector<string> data2 = { "M~C<2", "C~M>1"};

    cout<<solution(n,data1)<<endl;
}