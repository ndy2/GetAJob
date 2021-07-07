#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> rotate_cw90 (vector<vector<int>> map)
{
    int M,N;
    M = map.size();
    N = map[0].size();
    vector<vector<int>> map_r(N, vector<int>(M,0));
    for(int r = 0 ; r < N ; r ++)
        for(int c = 0 ; c < M ; c ++)
            map_r[r][c] = map[M-c-1][r];
    return map_r;
    
}

int main() {
    
    int N,M;
    cin>>N>>M;
    vector<vector<int>> map(N, vector<int>(M,0));
    for(int r = 0 ; r < N ; r ++)
        for(int c = 0 ; c < M ; c++)
            cin>>map[r][c];
    int ans = 0;
    //type 1 2 3 4 5
    for(int rotate = 0 ; rotate <360 ; rotate+=90)
    {
        for(int r=0; r <map.size(); r++)
        {
            for(int c = 0 ; c < map[0].size() ;c++)
            {
                //type 1
                if(c < map[0].size()-3 && rotate <180)
                    ans = max(ans, map[r][c] + map[r][c+1] + map[r][c+2] + map[r][c+3]);
                //type 2
                if(c < map[0].size()-1 && r <map.size()-1 && rotate ==0)
                    ans =max(ans, map[r][c] + map[r][c+1] + map[r+1][c] + map[r+1][c+1]);
                //type 3, 4, 5
                if(c < map[0].size()-1 && r <map.size()-2 ){
                    ans =max(ans, map[r][c] + map[r+1][c] + map[r+2][c] + map[r+2][c+1]);
                    ans =max(ans, map[r][c+1] + map[r+1][c+1] + map[r+2][c+1] + map[r+2][c]);                  
               
                    ans =max(ans, map[r][c] + map[r+1][c] + map[r+1][c+1] + map[r+2][c+1]);
                    ans =max(ans, map[r][c+1] + map[r+1][c+1] + map[r+1][c] + map[r+2][c]);
               
                    ans =max(ans, map[r][c] + map[r+1][c] + map[r+2][c] + map[r+1][c+1]);

                }

            }
        }
        map = rotate_cw90(map);
    }
    cout<<ans<<endl;
}       