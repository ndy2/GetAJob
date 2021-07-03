#include <iostream>
#include <vector>
#include <queue>


using namespace std;

typedef struct info{
    vector<vector<int>> map;
    vector<int> papers;
    int used;
}info;

vector<vector<int>> map(10, vector<int>(10,0));
vector<int> remain_papers = {0,5,5,5,5,5};

void input()
{
    for(int r = 0 ; r <10; r++)
        for(int c = 0 ; c < 10 ; c++ )
            cin>>map[r][c];
}

//return {{y,x},{possible size}}
vector<vector<int>> proc(info pi)
{
    vector<vector<int>> imap = pi.map;
    vector<int> ipaper;
    int iused = pi.used;

    vector<int> pos = {-1,-1};
    vector<int> possible_sizes;

    for(int sz = 1; sz<=5 ; sz++)
        if(pi.papers[sz]>0)
            ipaper.push_back(sz);

    int r,c;
    bool glb_is_valid = false;
    for(r = 0 ; r < 10 ; r++)
        for(c = 0 ; c< 10 ; c++)
        {
            if(imap[r][c] == 1)
            {
                pos[0] = r;
                pos[1] = c;

                for(auto s : ipaper)
                {
                    bool is_valid = false;
                    if(r+s-1<10&& c+s-1<10&& imap[r+s-1][c+s-1] == 1)
                        {
                            int stride ;
                            for(stride = 0 ; stride < s ; stride ++)
                            {
                                if(imap[r+s-1][c+stride] == 1 && imap[r+stride][c+s-1] == 1)
                                    continue;
                                else
                                    break;
                            }
                            if(stride == s)
                            {
                                glb_is_valid = true;
                                is_valid = true;
                            }
                        }
                    
                    if(is_valid)
                        possible_sizes.push_back(s);
                    else
                        break;
                }
                r = 15;
                c = 15;
            }
        }

    //if all ones are cleared
    if(r==10 && c ==10)
        pos[0] = -2;
    //if it met one but has no appropriate size of papers
    else if(!glb_is_valid)
        pos[0] = -1;
    return {pos,possible_sizes};
}

vector<info> proc_info(info c, vector<vector<int>> out)
{
    vector<int> pos = out[0];
    vector<int> indices = out[1];

    vector<vector<int>> cmap = c.map;
    vector<int> cpapers = c.papers;
    int cused = c.used;

    vector<info> vi;

    for(auto i : indices)
    {
        vector<vector<int>> pmap = cmap;
        vector<int> ppapers = cpapers;

        for(int r = pos[0] ; r < pos[0] + i ; r++)
            for(int c= pos[1] ; c <pos[1] + i ; c++)
                pmap[r][c] = 0;
        
        ppapers[i] --;
        vi.push_back({pmap, ppapers, cused+1});
    }
    return vi;
}

// lets go brute force!!
// enough memory lets keep all board, papers info and apply bfs
void solve()
{
    int ans = 1e9;

    info init_ = {map, remain_papers,0};
    queue<info> q;
    q.push(init_);
    while(!q.empty())
    {   
        info c = q.front();
        q.pop();
        vector<vector<int>> out = proc(c);
        vector<int> pos = out[0];
        vector<int> indices = out[1];

        if(pos[0] == -1)
            continue;
        if(pos[0] == -2)
            {
                //the answer is set!!! no need to search furthur
                //since it is BFS!!!!
                ans = min(ans, c.used);
                break;
            }
            
        vector<info> generated_infos = proc_info(c, out);
        for(auto gi : generated_infos)
            q.push(gi);
    }
    if(ans==1e9) ans = -1;
    cout<<ans;
}

int main()
{
    input();
    solve();
}
