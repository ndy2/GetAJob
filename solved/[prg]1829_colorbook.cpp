#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

vector<int> dx;
vector<int> dy;

int visited[101][101];
int pic[101][101];
int row,col;

vector<int> colors;

using namespace std;

void dfs(int y, int x, int target, bool ada)
{
    if(visited[y][x])
        return;
    else if(pic[y][x] == 0)
    {
        visited[y][x] = 1;
        return;
    }
    else
    {
        if(pic[y][x] == target)
        {
            visited[y][x] = 1;
            if(ada)
                colors.push_back(1);
            else
                colors[colors.size()-1] ++;
            for (int i = 0 ; i < 4 ; i ++)
                if(x+dx[i]>=0 && x+dx[i] <col && y+dy[i] >= 0 && y+dy[i] < row)
                    dfs(y+dy[i], x+dx[i], target, false);
        }
        else
        {
            return;
        }
    }
}

vector<int> solution(int m, int n, vector<vector<int>> picture) {
    row = m;
    col = n;
    dx = {-1,0,1,0};
    dy = {0,-1,0,1};
    colors = {};
    memset(visited,0,sizeof(visited));
    memset(pic,0,sizeof(pic));

    for(int i = 0 ; i < m ; i ++)
        for(int j = 0 ; j < n ; j ++)
            pic[i][j] = picture[i][j];
    
    for(int i = 0 ; i < m ; i ++)
    {
        for(int j = 0 ; j < n ; j ++)
        {
            dfs(i,j,pic[i][j],true);
        }
    }
    
    vector<int> answer(2);
    answer[0] = colors.size();
    answer[1] = answer[0]!=0?*max_element(colors.begin(), colors.end()):0;
    return answer;
}
