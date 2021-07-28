#include <iostream>
#include <vector>
#include <cmath>
#define pow2(x) ((x)*(x))
using namespace std;

bool is_point_in_circle(vector<int> point, int p, int q, int r)
{
    if(pow2(point[0]-p) + pow2(point[1]-q) > pow2(r))
        return false;
    return true;
}

int main()
{
    int TC;
    cin>>TC;
    for(int tc =1 ; tc<=TC; tc++)
    {
        int p,q,r;
        int a,b,c,d;
        scanf("%d %d %d",&p,&q,&r);
        scanf("%d %d %d %d",&a,&b,&c,&d);
        //0 1 2 3
        vector<vector<int>> square_edges = {{c,d},{a,d},{a,b},{c,b}};

        if(p-r>=a && p+r <=c && q-r>=b && q+r<=d)
            printf("#%d NY\n",tc);
        else 
        {
            int dir = 0;
            vector<float> center = {(float)(a+c)/2,(float)(b+d)/2};
            bool is_right = center[0]-float(p)>0;
            bool is_above = center[1]-float(q)>0;
            if(is_right && is_above)
                dir = 0;
            else if(is_right && !is_above)
                dir = 3;
            else if(!is_right && is_above)
                dir = 1;
            else if(!is_right && !is_above)
                dir = 2;
            vector<int> point_far = square_edges[dir];
            if(is_point_in_circle(point_far, p,q,r))
                 printf("#%d YN\n",tc);
            else
                printf("#%d YY\n",tc);
        }
       
    }    
}