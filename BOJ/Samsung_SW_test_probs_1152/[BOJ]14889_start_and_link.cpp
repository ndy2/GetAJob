#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int board[20][20];



int team2power(vector<int> team)
{
    int power = 0;
    vector<int> idx;
    for(int i = 0 ; i < team.size()-2; i++)
        idx.push_back(0);
    for(int i = team.size()-2 ; i < team.size(); i++)
        idx.push_back(1);
    
    do{
        vector<int> two;
        for(int i = 0 ; i <team.size() ; i++)
            if(idx[i] == 1)
                    two.push_back(team[i]);
        power +=board[two[0]][two[1]];
        power +=board[two[1]][two[0]];
    }while(next_permutation(idx.begin(), idx.end()));
    
    return power;
}

int main() {
    int N;
    cin>>N;

    for(int r = 0 ; r < N ; r++)
        for(int c= 0 ; c < N ; c++)
            cin>>board[r][c];
    vector<int> idx(N,0);
    for(int i = N/2 ; i < N ; i++)
        idx[i]=1;

    int ans = 1e9;

    do{
        vector<int> team_start, team_link;
        for(int i = 0 ; i < N ; i++)
            if(idx[i] == 0)
                team_start.push_back(i);
            else
                team_link.push_back(i);
        
        int team_start_power = team2power(team_start);
        int team_link_power = team2power(team_link);
        
        ans = min(ans, abs(team_start_power- team_link_power));

    }while(next_permutation(idx.begin(), idx.end()));
    
    
    cout<<ans;
}       