#include <iostream>
#include <vector>
#include <string>

using namespace std;

string S;



int main()
{
    int TC;
    cin>>TC;
    for(int tc =1 ; tc<=TC; tc++)
    {
        int D,N;
        cin>>D>>N;
        vector<vector<int>> horses(N,{0,0});
        for(int i = 0 ; i < N ; i++)
            cin>>horses[i][0]>>horses[i][1];
        double t = -100;
        for(auto h : horses)
        {
            int l = D-h[0];
            int s = h[1];
            double cur_time = (double)l/(double)s;
            t = cur_time>t?cur_time:t;
        }
        double ans = D/t;
        printf("#%d %.10f\n",tc,ans);
    }    
}