#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#include <string.h>

using namespace std;

int N,M,fuel;
int map[21][21];
int map_user[21][21];
vector<int> map_dest[21][21];

bool visited[21][21];

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

vector<vector<int>> user;
vector<int> taxi;
vector<int> dest;

void input()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(nullptr);
    cin>>N>>M>>fuel;
    for(int r= 1 ;r <= N; r++)
        for(int c = 1 ; c <= N ; c++)
            cin>>map[r][c];
    int y1,x1,y2,x2;
    cin>>y1>>x1;
    taxi = {y1,x1};
    for(int u = 0 ; u < M ; u++)
        {
            cin>>y1>>x1>>y2>>x2;
            user.push_back({y1,x1,y2,x2});
        }
}


void init_maps(){
    int idx=0;
    memset(map_user,-1,sizeof(map_user));

    for (auto u : user)
    {
        map_user[u[0]][u[1]] = idx;
        map_dest[u[2]][u[3]] .push_back(idx);
        idx++;
    }
}

bool mysort(vector<int> a , vector<int> b)
{
    return
    a[0]<b[0]?true:
    a[0]>b[0]?false:
    a[1]<b[1]?true:false;
}

bool user2dest_suc(int user_idx)
{
    
    queue<vector<int>> qv;
    taxi.push_back(0);
    qv.push(taxi);
    // q vector : pos_y, pos_x, dist
    int dist_stamp;
    bool user_meet = false;
    while(!qv.empty()){
        vector<int> pos =qv.front();
        qv.pop();
        
        if(visited[pos[0]][pos[1]])
            continue;
        visited[pos[0]][pos[1]] = true;
        //check user meet
        if(pos[0] == dest[0] && pos[1] == dest[1])
            {
                dist_stamp = pos[2];
                user_meet = true;
                break;
            }
        
        for(int d = 0 ; d<4; d++)
            {
                int ty = pos[0] + dy[d];
                int tx = pos[1] + dx[d];
                if(ty>=1 && ty<=N && tx>=1 && tx<=N && map[ty][tx]!=1 && !visited[ty][tx])
                    qv.push({ty,tx, pos[2]+1});
            }
    }
    if(!user_meet) return false;
    fuel -=dist_stamp;
    if(fuel<0) return false;
    
    fuel +=2*dist_stamp;
    taxi = dest;
    map_dest[taxi[0]][taxi[1]].erase(find (map_dest[taxi[0]][taxi[1]].begin(), map_dest[taxi[0]][taxi[1]].end(), user_idx)) ;
    memset(visited, 0, sizeof(visited));
    return true;
}

int dest2user_suc()
{
    
    queue<vector<int>> qv;
    taxi.push_back(0);
    qv.push(taxi);
    // q vector : pos_y, pos_x, dist
        
    vector<int> meet_user_idx;
    int dist_stamp = 1e9;
    while(!qv.empty()){
        vector<int> pos =qv.front();
        qv.pop();

        if(visited[pos[0]][pos[1]])
            continue;
        visited[pos[0]][pos[1]] = true;
        if(pos[2] > dist_stamp)
            break;
        //check user
        if(map_user[pos[0]][pos[1]]!=-1)
            {
                meet_user_idx.push_back(map_user[pos[0]][pos[1]]);
                dist_stamp = pos[2];
            }
        if(dist_stamp!=1e9) continue;
        for(int d = 0 ; d<4; d++)
            {
                int ty = pos[0] + dy[d];
                int tx = pos[1] + dx[d];
                if(ty>=1 && ty<=N && tx>=1 && tx<=N && map[ty][tx]!=1 && !visited[ty][tx])
                    qv.push({ty,tx, pos[2]+1});
            }
    }
    fuel -=dist_stamp;
    if(fuel<=0) return -1;
    
    vector<vector<int>> users;
    for(auto u : meet_user_idx)
        users.push_back(user[u]);

    if(users.size()>1) sort(users.begin(), users.end() , mysort);

    taxi = {users[0][0], users[0][1]};
    dest = {users[0][2], users[0][3]};
    int ret = map_user[taxi[0]][taxi[1]];
    map_user[taxi[0]][taxi[1]] = -1;
    
    memset(visited, 0, sizeof(visited));
    return ret;
}

void solve()
{
    int ans;
    init_maps();
    for(int i = 0 ; i < M ; i++)
    {
        int user = dest2user_suc();
        if(user ==-1)
        {
            ans =-1;
            break;
        }
        if(!user2dest_suc(user))
        {
            ans = -1;
            break;
        }
        ans = fuel;
    }
    cout<<ans;
    
}


int main() {
    input();
    solve();
    return 0;
}       