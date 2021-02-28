#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <cmath>
#include <bits/stdc++.h> 

using namespace std;

void print_lines(vector<string> lines){
    for (auto a : lines)
    {
        cout<<a<<endl;
    }
}

int S_to_int(string S)
{
    return 1000*(3600*stoi(S.substr(0,2)) + 60*stoi(S.substr(3,2)) + stoi(S.substr(6,2))) + stoi(S.substr(9,3));
}

int T_to_int(string T)
{
    if(T.find('.') == string::npos)
        return 1000* (T[0] - '0');
    else
    {
        int c = pow(10,  5 - T.length());
        return 1000* (T[0] - '0') + c * stoi(T.substr(2,T.length()- 1));
    }
    
}

vector<pair<int,int>> lines_to_list(vector<string> lines)
{
    string S,T;
    vector<pair<int,int>> list_To_oriented;
    for (auto a : lines)
    {
        S = a.substr(11, 12);
        T = a.substr(24,a.length()-25);
        int To = S_to_int(S);
        int From = To - T_to_int(T)+1;
        list_To_oriented.push_back(make_pair(From,To));
    }
    return list_To_oriented; 
}

int solution(vector<string> lines) {
    int answer = 0;
    vector<pair<int,int>> list_To_oriented = lines_to_list(lines);
    vector<int> list;
    int n = lines.size();
    for (int i = 0 ; i< n; i++)
    {
        int count = 1;
        for(int j = i+1 ; j<n ; j++)
        {
            if(list_To_oriented[j].first >= list_To_oriented[i].second + 1000)
                j = n;
            else
                count ++;
        }
        list.push_back(count);
    }

    return *max_element(list.begin(), list.end());
}


int main()
{

    vector<string> lines_1 {"2016-09-15 01:00:04.001 2.0s","2016-09-15 01:00:06.001 2.0s",
                            "2016-09-15 01:00:07.000 2s","2016-09-15 01:00:07.000 2s","2016-09-15 01:00:07.000 2s"};
    vector<string> lines_2 {"2016-09-15 01:00:04.002 2.0s","2016-09-15 01:00:06.001 2.0s",
                            "2016-09-15 01:00:07.000 2s","2016-09-15 01:00:07.000 2s","2016-09-15 01:00:07.000 2s"};
    vector<string> lines_3 {"2016-09-15 20:59:57.421 0.351s",
                            "2016-09-15 20:59:58.233 1.181s",
                            "2016-09-15 20:59:58.299 0.8s",
                            "2016-09-15 20:59:58.688 1.041s",
                            "2016-09-15 20:59:59.591 1.412s",
                            "2016-09-15 21:00:00.464 1.466s",
                            "2016-09-15 21:00:00.741 1.581s",
                            "2016-09-15 21:00:00.748 2.31s",
                            "2016-09-15 21:00:00.966 0.381s",
                            "2016-09-15 21:00:02.066 2.62s"};
    
    cout<<solution(lines_1)<<endl;
    cout<<solution(lines_2)<<endl;                        
    cout<<solution(lines_3)<<endl;
}