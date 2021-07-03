#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> info = {0};

int count;

vector<int> proc_col_cand(int row, int n )
{
    vector<int> col_cand (n+1,0);
    for(int i = 1 ; i <= row-1; i ++)
    {
        int diff = row-i;
        if(info[i]-diff >=1)
            col_cand[info[i]-diff] = -1;
        col_cand[info[i]] = -1;
        if(info[i]+diff <=n)
            col_cand[info[i]+diff] = -1;
    }
    return col_cand;
}

bool proc(int row, int col, int n)
{
    if(row == n+1)
        {
            count++;
            return false;
        }

    vector<int> col_cand = proc_col_cand(row,  n);
    
    int cur_row_temp_cnt = 0;
    int i;
    for( i = 1 ; i <=n ; i ++)
    {
        bool below_search_done = false;
        if(col_cand[i] == 0 )
        {
            info.push_back(i);

            if(info.size() == n+1) 
            {
                info.pop_back();
                count++;
                return true;
            }

            below_search_done = proc(row+1, i, n);
            if(below_search_done)
            {
             info.pop_back();
            return below_search_done;

            }
            cur_row_temp_cnt ++;
        }
    }
    return false;
      
}


int solution(int n) {
    int answer = 0;
    proc(1,0,n);
   

    return count;
}


int main()
{
    cout<<solution(4);
}