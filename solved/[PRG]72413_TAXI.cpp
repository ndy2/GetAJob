#include <string>
#include <vector>
#include <iostream>
#define MIN(A,B) (A)<(B)?(A):(B)

#define INF 0x00FFFFFF
using namespace std;

int cost[201][201];

void FW_logic(int n)
{
    for(int j = 1 ; j <= n ; j ++)
        for(int i = 1; i <=n; i ++)
            for(int k = 1; k <=n ; k ++)
                cost[i][k] = MIN(MIN(cost[i][k], cost[i][j]+ cost[j][k]),INF);
}

void set_inf(int n)
{
    for(int i = 1 ; i <= n ; i ++)
        for(int j = 1; j <=n; j ++)
            if(i!=j && cost[i][j] == 0)
                cost[i][j] = INF; 
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = INF;
    for(auto f : fares)
        cost[f[0]][f[1]] = cost[f[1]][f[0]] = f[2];
    set_inf(n);
    FW_logic(n);
    for(int M = 1; M <= n ; M ++)
        answer = MIN(cost[s][M] + cost[M][a] + cost[M][b], answer);
    return answer;
}

int main()
{
    vector<vector<int>> fares1 ={{4, 1, 10}, {3, 5, 24}, {5, 6, 2}, {3, 1, 41},{5, 1, 24}, {4, 6, 50}, {2, 4, 66}, {2, 3, 22}, {1, 6, 25}};
    cout<<solution(6,4,6,2,fares1)<<endl;
}