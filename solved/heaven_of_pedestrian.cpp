#include <vector>
#include <iostream>
#define NO_TURN 2

using namespace std;

int MOD = 20170805;

typedef struct cases
{
    int from_left;
    int from_up;
}cases;

void fill_map(int r, int c, vector<vector<int>> city_map, vector<vector<cases>>& case_map)
{
    if(city_map[r][c]==1)
        case_map[r][c] = {0,0};
    else
    {
        if(r == 0 )
            case_map[r][c].from_left = case_map[r][c-1].from_left;
        else if (c == 0)
             case_map[r][c].from_up = case_map[r-1][c].from_up;
        else 
        {
            case_map[r][c].from_left  = city_map[r][c-1]==NO_TURN? case_map[r][c-1].from_left :(case_map[r][c-1].from_left+ case_map[r][c-1].from_up)%MOD;
            case_map[r][c].from_up   =  city_map[r-1][c]==NO_TURN? case_map[r-1][c].from_up   :(case_map[r-1][c].from_left+ case_map[r-1][c].from_up)%MOD;
        }
    }
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int m, int n, vector<vector<int>> city_map) {
    int answer = 0;
    int moves_to_go = m+n+1;
    vector<cases> case_map_row(n, {0,0});
    vector<vector<cases>> case_map(m, case_map_row);
    case_map[0][0] = {1,1};
    int i = 1;
    while(i <= moves_to_go)
    {   
        int r,c;
        r = 0;
        c = i - r;
        while(r>=0 && c>=0)
        {
            c = i - r;
            if(c<0) break;
            if(r<m && c <n)
            {
                if(city_map[r][c]==1)
                case_map[r][c] = {0,0};
            else
            {
                if(r == 0 )
                    case_map[r][c].from_left = case_map[r][c-1].from_left;
                else if (c == 0)
                    case_map[r][c].from_up = case_map[r-1][c].from_up;
                else 
                {
                    case_map[r][c].from_left  = city_map[r][c-1]==NO_TURN? case_map[r][c-1].from_left :(case_map[r][c-1].from_left+ case_map[r][c-1].from_up)%MOD;
                    case_map[r][c].from_up   =  city_map[r-1][c]==NO_TURN? case_map[r-1][c].from_up   :(case_map[r-1][c].from_left+ case_map[r-1][c].from_up)%MOD;
                }
            }
            }
            r++;
        }
        i++;
    }
    answer = (case_map[m-1][n-1].from_left+ case_map[m-1][n-1].from_up)%MOD;
    return answer;
}


int main()
{
    vector<vector<int>> city_map1 = {{0,0,0},{0,0,0},{0,0,0}};
    vector<vector<int>> city_map2 = {{0,2,0,0,0,2},
                                     {0,0,2,0,1,0},
                                     {1,0,0,2,2,0}};
    vector<vector<int>> city_map3 = {{0,0,0,0,0,2},
                                     {0,0,1,0,0,0},
                                     {1,0,2,2,2,0}};
    cout<<solution(3,6,city_map2)<<endl;

}