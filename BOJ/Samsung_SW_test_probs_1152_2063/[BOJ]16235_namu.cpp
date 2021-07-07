#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string.h>

using namespace std;
int map[10][10];
int map_s2d2[10][10];
deque<int> map_tree[10][10];
int dy[8] = {0,0,1,-1,1,1,-1,-1};
int dx[8] = {1,-1,0,0,1,-1,1,-1};

int N,M,K;

void input()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(nullptr);

    int p,y,x,z;
    cin>>N>>M>>K;

    for(int r = 0 ; r < N ; r++)
        for(int c = 0 ; c < N ; c++)
            {
                cin>>map_s2d2[r][c];
                map[r][c] = 5;
            }
    for(int i = 0 ; i < M ; i++)
            {
                cin>>y>>x>>z;
                map_tree[y-1][x-1].push_back(z);
            }
}

void solve()
{
    for(int y = 0 ; y < K ; y++)
    {
        //spring & summer
        int tree_age;
        
        vector<vector<int>> tree_age_5times;

        for(int r= 0 ; r<N; r++)
            for(int c = 0 ; c<N ;c++)
            {
                vector<int> tree_upgrade;
                vector<int> tree_dead;
                bool outed = false;
                while(!map_tree[r][c].empty())
                {
                    tree_age=map_tree[r][c].front();
                    map_tree[r][c].pop_front();

                    if(!outed&&map[r][c] >= tree_age)
                    {
                        map[r][c] -=tree_age;
                        tree_age++;
                        tree_upgrade.push_back(tree_age);
                        if(tree_age%5==0)
                            tree_age_5times.push_back({r,c});
                    }
                    else{
                        outed = true;
                        tree_dead.push_back(tree_age);
                    }
                }
                for(const auto& tu : tree_upgrade)
                    map_tree[r][c].push_back(tu);
                for(const auto& td : tree_dead)
                    map[r][c]+=td/2;

                
            }
        
        //autumn
        for(const auto& ta5 : tree_age_5times)
        {
            for(int d = 0 ; d < 8 ; d++)
            {
                int ty = ta5[0]+dy[d];
                int tx = ta5[1]+dx[d];
                if(ty>=0 && ty<N && tx>=0 && tx<N)
                    map_tree[ty][tx].push_front(1);
            }
        }

        //winter
        for(int r = 0 ; r < N ; r++)
            for(int c = 0 ; c < N ; c++)
                    map[r][c] += map_s2d2[r][c];
    }

    int tree_cnt=0;
    for(int r = 0 ; r < N ; r++)
        for(int c = 0 ; c < N ; c++)
            tree_cnt+=map_tree[r][c].size();        

    cout<<tree_cnt;
}


int main() {
    input();
    solve();

    return 0;
}       