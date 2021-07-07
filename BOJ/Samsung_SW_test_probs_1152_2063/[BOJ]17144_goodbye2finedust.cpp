#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int R,C,T;
int map[50][50];
int diffusion_map[50][50];
int cleaner;

int dy[4] = {0,1,0,-1};
int dx[4] = {1,0,-1,0};

void print_map()
{
    for(int r = 0 ; r < R ; r++)
        {
            for(int c= 0 ; c<C ; c++)
                cout<<map[r][c]<<" ";
            cout<<endl;
        }
    cout<<endl;
    cout<<endl;
    cout<<endl;
}

void input()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(nullptr);
    int cell;
    cin>>R>>C>>T;
    for(int r= 0 ;r < R; r++)
        for(int c = 0 ; c < C ; c++)
        {
            cin>>cell;
            map[r][c] = cell;
            if(cell == -1)
                cleaner = r;
        }
}

void diffuse()
{
    //calc_diffuse_map
    for(int r= 0 ;r < R; r++)
    {
        for(int c= 0 ; c<C ;c++)
        {
            int diffuse_amount = map[r][c]/5;

            for(int d =0 ; d < 4 ; d++)
            {
                int ty = r+dy[d];
                int tx = c+dx[d];
                if(ty>=0 && ty<R && tx>=0 && tx <C && map[ty][tx]!=-1)
                {       
                    map[r][c] -= diffuse_amount;
                    diffusion_map[ty][tx] += diffuse_amount;
                }
            }
        }
    }

    //actual diffuse
    for(int r= 0 ; r < R; r++)
        for(int c = 0 ; c <C ; c++)
            map[r][c] += diffusion_map[r][c];

    memset(diffusion_map, 0, sizeof(diffusion_map));
}

void wind(int pos1, int pos2)
{
    vector<int> r1(C,0),r2(C,0),r3(C,0),r4(C,0);
    copy(&map[0][0], &map[0][0]+C, r1.begin());
    copy(&map[pos1][0], &map[pos1][0]+C, r2.begin());

    copy(&map[pos2][0], &map[pos2][0]+C, r3.begin());
    copy(&map[R-1][0], &map[R-1][0]+C, r4.begin());
    
    vector<int> c1(R,0), c2(R,0);
    for(int r= 0 ; r < R; r++)
    {
        c1[r] = map[r][0];
        c2[r] = map[r][C-1];
    }

    // center two right flow
    map[pos1][1] = 0 ;  map[pos2][1] = 0 ; 
    for(int c = 2; c < C ; c++)
        {
            map[pos1][c] = r2[c-1];
            map[pos2][c] = r3[c-1];
        }
    //right wall above
    for(int r = pos1-1 ; r>=0 ; r--)
        map[r][C-1] = c2[r+1]; 
    //abvoe
    for(int c = C-2; c >=0 ; c--)
        map[0][c] = r1[c+1];
    //left wall above
    for(int r= 1; r<pos1; r++)
        map[r][0] = c1[r-1];
    
    //right wall below
    for(int r= pos2+1; r<R; r++)
        map[r][C-1] = c2[r-1];
    
    //below
    for(int c = C-2; c>=0 ; c--)
        map[R-1][c] = r4[c+1];
    
    //left wall melow
    for(int r = R-2 ; r>=pos2+1 ; r--)
        map[r][0] = c1[r+1];
}

int ans()
{
    int ans=0;
    for(int r = 0; r< R; r++)
        for(int c= 0 ; c< C; c++)
                ans+=map[r][c];
    
    return ans+2;
}

void solve()
{
    bool debug = false;
    for(int t = 0; t < T ;t++)
    {
        
        if(debug) print_map();
        diffuse();
        if(debug) print_map();
        wind(cleaner-1, cleaner);
        if(debug) print_map();
    }
    cout<<ans();
}


int main() {
    input();
    solve();

    return 0;
}       