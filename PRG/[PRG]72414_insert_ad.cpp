#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int abs_time(string ls)
{
    return 3600*stoi(ls.substr(0,2)) + 60 * stoi(ls.substr(3,2)) + stoi(ls.substr(6,2));
}

bool plsort(pair<int,char> a, pair<int,char> b)
{
    return a.first < b.first;
}

 vector<pair<int,char>> proc_logs(vector<string> logs)
 {
     vector<pair<int,char>> pl;
     for(auto l : logs)
     {
         int stt = abs_time(l.substr(0,8));
         int end = abs_time(l.substr(9,17));
         pl.push_back({stt,'s'});
         pl.push_back({end,'e'});
     }
    
    sort(pl.begin(), pl.end(), plsort);
    return pl;
 }

 int proc_cur_end(int pt,  vector<pair<int,char>> pl)
 {
     int cur_end = 0;
     for(auto l : pl)
        {
            if(l.first<cur_end && l.second == 's')
                cur_end ++;
            else if(l.first<cur_end && l.second == 'e')
                cur_end --;
            else if(l.first > cur_end)
                break;
        }
    return cur_end;
 }

string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";
    vector<pair<int,char>> pl = proc_logs(logs);
    int abs_pt = abs_time(play_time);
    int abs_at = abs_time(adv_time);
    
    for(auto l : pl)
        cout<<l.first<<" "<<l.second<<endl;
    int cur_stt = 0 ;
    int cur_end = proc_cur_end();
    int target_stt;
    int target_end;
    for(auto l : pl)
    {

    }
    

    return answer;
}

int main()
{
    vector<string> logs1 = {"01:20:15-01:45:14", "00:40:31-01:00:00", "00:25:50-00:48:29", "01:30:59-01:53:29", "01:37:44-02:02:30"    };
    vector<string> logs2 = {"00:00:01-00:00:05", "00:00:06-00:00:08", "00:00:03-00:00:07", "00:00:02-00:00:04"};
    // cout<<solution("02:03:55", "00:14:15",logs1);
    cout<<solution("00:00:20", "00:00:04",logs2);
    


}