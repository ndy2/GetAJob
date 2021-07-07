#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

int N,M,T;
int map[50][50];
int glb_visited[50][50];

bool debug = false;

vector<vector<int>> rotates;

void print_map()
{
    if(debug){
    for(int i = 0 ; i <N ; i++)
        {
            printf("disk %d ", i+1);
            for(int j = 0 ; j <M ; j++)
                printf("%3d ",map[i][j]);
            printf("\n");
        }
    printf("\n\n");
    }
}

void input()
{
    cin>>N>>M>>T;
    for(int r=  0 ;r < N ; r++)
        for(int c = 0 ; c < M ; c++)
             cin>>map[r][c];
    
    int x,d,k;
    for(int t = 0 ; t <T; t++)
    {
        cin>>x>>d>>k;
        if(d == 0)
            k = M-k;
        rotates.push_back({x,k});
    }
}

float get_avg()
{
    int sum = 0;
    int cnt = 0;
    for(int r = 0 ; r < N ; r++)
        for(int c = 0 ; c <M ; c++)
            if(map[r][c]>0)
            {
                sum+=map[r][c];
                cnt+=1;
            }
                
    return (float)sum/(float)cnt;
}

//remove cons neighbors
//each cor search four neighbors
void remove()
{
    int mark[50][50];
    memset(mark, 0, sizeof(mark));

    bool stage_2_2 = true;
    for(int r_xi = 0 ; r_xi < N ; r_xi ++)
        for(int c_xi = 0 ; c_xi < M ; c_xi++)
            for(int d = 0 ; d < 4 ; d ++)
            {
                int cur = map[r_xi][c_xi];
                if(cur == -1)
                    continue;
                int ty = r_xi + dy[d];
                int tx = c_xi + dx[d];

                if(tx == -1) tx = M-1;
                else if(tx == M) tx = 0;

                if(ty>=0 && ty < N && cur == map[ty][tx])
                {
                       stage_2_2 = false; 
                       mark[r_xi][c_xi] = 1;
                       mark[ty][tx] = 1;
                }
           }
    
    if(stage_2_2)
    {
        float avg = get_avg();
        for(int r= 0 ; r < N ; r++)
            for(int c = 0 ; c < M ; c++)
                if(map[r][c]>0)
                {
                    if((float)map[r][c] >avg)
                        map[r][c]-=1;
                    else if((float)map[r][c]<avg)
                        map[r][c]+=1;
                }
    }
    else{
        for(int r = 0 ; r < N ; r++)
            for(int c = 0 ; c < M ; c++)
                if(mark[r][c] == 1)
                    map[r][c] = -1;
    }
    print_map();
}

void rotate(vector<int> ri)
{
    int xi = ri[0];
    int ki = ri[1];

    int amount = N/xi;
    //rotate!
    for(int r_xi = xi-1 ; r_xi < N ; r_xi +=xi)
    {
        int r_disk[50];
        copy(&map[r_xi][0], &map[r_xi][0] + ki, &r_disk[M-ki]);
        copy(&map[r_xi][0]+ki, &map[r_xi][0]+M, &r_disk[0]);
        copy(&r_disk[0], &r_disk[0]+M, &map[r_xi][0]);
    }

    print_map();
}

int get_ans()
{
    int ans = 0;
    for(int r = 0 ; r < N ; r++)
        for(int c = 0 ; c <M ; c++)
            if(map[r][c]>0)
                ans+=map[r][c];
    return ans;
}

void solve()
{
    print_map();

    int i = 1;
    for(auto r : rotates)
    {
        if(debug)cout<<i++<<endl;
        rotate(r);
        remove();
    }
    cout<<get_ans();   
}

int main() {
    input();
    solve();

    return 0;
}       