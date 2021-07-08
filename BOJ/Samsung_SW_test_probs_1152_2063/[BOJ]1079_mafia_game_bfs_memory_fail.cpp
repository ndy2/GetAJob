#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N;
vector<int> guilty;
int map[16][16];
int mafia_idx;

typedef struct info
{
    int night;
    int player_cnt;
    vector<int> civils;
    vector<int> guilty;
}info;

void input()
{
    cin>>N;
    int g;
    for(int i = 0 ; i < N ; i++)
    {
        cin>>g;
        guilty.push_back(g);
    }

    for(int r= 0 ; r <N; r++)
        for(int c = 0 ; c <N ; c++)
            cin>>map[r][c];

    cin>>mafia_idx;
}

void print_info(info in)
{
    printf("night : %d, player_cnt : %d\n", in.night, in.player_cnt);
    cout<<endl;

    printf("civil idx\n");
    for(auto c : in.civils)
        cout<<c<<" ";
    cout<<endl;
    printf("guilty\n");
    for(auto g : in.guilty)
        cout<<g<<" ";
    cout<<endl;
    cout<<endl;
}

void solve()
{
    vector<int> civils;
    for(int i = 0 ; i < N ; i++)
        civils.push_back(i);
    civils.erase(civils.begin() + mafia_idx);

    queue<info> q;
    q.push({0,N,civils,guilty});
    
    int ans =0;

    while(!q.empty())
    {
        info pos = q.front();
        // print_info(pos);
        q.pop();

        //mafia win
        if(pos.player_cnt == 1)
            {
                ans = max(pos.night,ans);
                continue;
            }

        int player_cnt = pos.player_cnt;
        vector<int> civils_pos = pos.civils;
        //night
        if(player_cnt %2 ==0)
        {
            for(auto i : civils_pos)
            {
                vector<int> guilty_changed = pos.guilty;
                vector<int> civil_pos_changed = civils_pos;
                civil_pos_changed.erase(find(civil_pos_changed.begin(), civil_pos_changed.end(), i));

                for(auto c : civil_pos_changed)
                    guilty_changed[c] += map[i][c];
                guilty_changed[mafia_idx] += map[i][mafia_idx];
                guilty_changed[i] = - 1e9;

                q.push({pos.night+1, player_cnt-1,civil_pos_changed, guilty_changed });
            }
        }
        
        //days
        else
        {
            vector<int> guilty_day = pos.guilty;
            int poll_dead = max_element(guilty_day.begin(), guilty_day.end()) - guilty_day.begin();

            if(poll_dead != mafia_idx)
            {
                civils_pos.erase(find(civils_pos.begin(), civils_pos.end(), poll_dead));
                guilty_day[poll_dead] = - 1e9;
                q.push({pos.night, player_cnt-1,civils_pos,guilty_day});
            }
            //mafia dead
            else
                ans = max(pos.night, ans);
        }
    }
    cout<<ans;
}


int main()
{
    input();
    solve();
}