#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

bool debug = false;

int N;
int map[2][4][6];
int score =0;

vector<vector<vector<int>>> moves_vec(2, vector<vector<int>>());

void print_map()
{
    if(debug){
    for(int i = 0 ; i <4 ; i++)
        {
            for(int j = 0 ; j <6 ; j++)
                printf("%3d ",map[0][i][j]);
            
            printf("    ");
            for(int j = 0 ; j <6 ; j++)
                printf("%3d ",map[1][i][j]);
            printf("\n");
        }
    printf("\n\n");
    }
}

void input()
{
    cin>>N;

    int t,y,x;
    for(int i = 0 ; i < N ; i ++)
    {
        cin>>t>>y>>x;
        int tg=t;
        if(t!=1) tg = 5-tg;
        moves_vec[0].push_back({t,y,x});
        if(tg ==3) x+=1;
        moves_vec[1].push_back({tg,3-x,y});
    }
}

void domino(int m)
{
    //shift
    for(int i = 0 ; i < 2; i++)
    {
        //t,y,x
        vector<int> mc = moves_vec[i][m];

        vector<int> filled_row_idx = {mc[1]};
        if(mc[0]==3) 
            filled_row_idx.push_back(mc[1]+1);

        int col;
        int col_save;
        for(col = 0 ; col<6; col++)
            for(auto r : filled_row_idx)
                if(map[i][r][col] ==1)
                {
                     col_save = col;
                     col = 7;
                }
                    
        if(col >6) col = col_save-1;
        else col-=1;

        for(auto r : filled_row_idx)
        {
            map[i][r][col] = 1;
            if(mc[0] == 2) map[i][r][col-1] = 1;
        }
            
    }
    if(debug) printf("after shift \n");
    print_map();
    //check boomed col

    vector<vector<int>> boomed_col (2,vector<int>()); 


    for(int i = 0 ; i <2 ; i++)
    {
        int light_boom_idx = 5;
        for(int c = 0 ; c < 6 ; c++)
        {
            int sum = 0;
            for(int row = 0 ; row< 4; row++)
                sum+=map[i][row][c];

            int limit = c<2?1:4;
            if(sum >= limit)
            {
                if(c>=2) { boomed_col[i].push_back(c); score+=1; }
                else boomed_col[i].push_back(light_boom_idx--);
            }
        }
        sort(boomed_col[i].begin(), boomed_col[i].end(), greater<int>());

    }
    
    //explosion and shift

    
    
    for(int i = 0 ; i < 2; i++)
    {
        if(boomed_col[i].size()==2 && boomed_col[i][0] ==5 && boomed_col[i][1] ==2)
        {
            for(int r = 0 ; r < 4; r++)
            {
                map[i][r][2] = map[i][r][1];
                map[i][r][1] = 0;
            }
        }

        else{
        int col_idx = 0;
        for(auto c : boomed_col[i])
        {
            for(int col = c-1+col_idx ; col >=0 ; col --)
            {
                for(int r = 0 ; r < 4; r++)
                    map[i][r][col+1] = map[i][r][col];
            }
            for(int r = 0 ; r < 4; r++)
                    map[i][r][0] = 0;
            col_idx++;
        }
        }
    }
    if(debug) printf("after explosion \n");
    print_map();


}

void ans()
{
    cout<<score<<endl;

    int num_block[2] = {0,0};
    for(int i = 0 ;  i< 2; i++)
        for(int r = 0 ; r < 4; r++)
            for(int c= 0 ; c < 6; c++)
                num_block[i] += map[i][r][c];
    cout<<num_block[0]+num_block[1];
}

void print_moves(int m)
{
    printf("blue : ");
    for(int i = 0 ; i < 3; i ++)
        cout<<moves_vec[0][m][i]<<" ";
    cout<<endl;

    
    printf("green : ");
    for(int i = 0 ; i < 3; i ++)
        cout<<moves_vec[1][m][i]<<" ";
    cout<<endl;
}

void solve()
{
     
    for(int m = 0 ; m < N ; m ++)
    {
        if(debug) print_moves(m);
        domino(m);
    }

    ans();
}

int main() {
    input();
    solve();

    return 0;
}       