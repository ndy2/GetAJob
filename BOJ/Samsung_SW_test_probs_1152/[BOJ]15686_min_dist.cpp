#include <iostream>
#include <vector>
#include <cmath>

#include <algorithm>

using namespace std;

int N,M;
int map[50][50];
bool visited[50][50];

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

int dist(int y0, int x0, int y1, int x1)
{
    return abs(y0-y1) + abs(x0-x1);
}

int main() {
    int t;
    cin>>N>>M;
    vector<vector<int>> store;
    vector<vector<int>> house;
    for(int r = 0 ; r < N ; r++)
        for(int c = 0 ; c < N ; c++)
        {
            cin>>t;
            map[r][c] =t;
            if(t==1)
                house.push_back({r,c});
            else if(t==2)
                store.push_back({r,c,0});
            
        }
    int S = store.size();
    
    vector<int> idx(S,0);
    for(int i = 0 ; i < M ; i++)
        idx[S-i-1] = 1;

    int answer = 1e9;

    do {
        vector<int> remain, removed;
        vector<vector<int>> store_new;
        int cur_ans = 0;
        for(int i = 0 ; i < S ; i++)
            {
                if(idx[i]==1)
                    remain.push_back(i);
                else
                    removed.push_back(i);
            }
        
        for(int i = 0 ; i < S-M ; i++)
                map[store[removed[i]][0]][store[removed[i]][1]] = 0;
         
        for(int i = 0 ; i < house.size() ; i++)
        {
            int house2store = 1e9;
            for(int j = 0 ; j < M ; j++)
                house2store = min(house2store, dist(store[remain[j]][0], store[remain[j]][1], house[i][0], house[i][1]));
            cur_ans += house2store;
        }

        for(int i = 0 ; i < S-M ; i++)
                map[store[removed[i]][0]][store[removed[i]][1]] = 2;
        answer = min(answer,cur_ans);
    }while(next_permutation(idx.begin(), idx.end()));
    cout<<answer;


    return 0;
}       