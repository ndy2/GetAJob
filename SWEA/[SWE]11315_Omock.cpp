#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<vector<int>> dir = {{1,0} , {1,1}, {0,1}, {-1,1}}; 
void dfs(int x, int y, vector<vector<char>> board , int combo , int dir_idx, int N , bool& ans) 
{
    if(board[y][x] == '.') 
    {
    }
    else
    {
        if (combo ==4)
        {
            ans = true;
        }
        
        else if(y+dir[dir_idx][1] >= 0 && y+dir[dir_idx][1] < N && x+dir[dir_idx][0] >= 0 && x+dir[dir_idx][0] < N )
            dfs(x+dir[dir_idx][0] ,y+dir[dir_idx][1] , board, combo +1, dir_idx, N ,ans);
        
    }
}

int main()
{
    vector<string> ans;
    int T;
    cin>>T;
    for(int i = 0 ; i < T ;  i ++)
    {
        string s = "NO"; 
        int N;
        cin >> N;
        vector<vector<char>> board (N, vector<char>(N,0));
        
    
        for(int j = 0 ; j < N ; j ++)
            for(int k = 0 ; k < N ; k ++)
                cin >>board[j][k];
        bool b =false;
        for(int y = 0 ; y < N ; y ++)
            for(int x = 0 ; x < N ; x ++)
                if(board[y][x] == 'o')
                {
                for(int d = 0 ; d < 4 ; d++)
                    {   
                        dfs(x,y,board,0,d,N , b);
                        if(b)
                                {
                                    s = "YES";
                                    y = N; x = N ; d = 4;
                                }
                    }
                }
                
        ans.push_back(s);

    }

    for(int i = 0 ; i < ans.size() ; i ++ )
        cout <<"#"<<i+1<<" "<<ans[i]<<endl;

    

}