#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct ball{
    int color;
    int size;
    int orig_idx;
}ball;

bool sortballs(ball a, ball b){
    return a.size<b.size;
}

void print_balls(vector<ball> balls)
{
    for(auto b : balls){
        cout<<b.color<<" "<<b.size<<" "<<b.orig_idx<<endl;
    }
}


int main(){

    int N;
    
    scanf("%d", &N);
    vector<ball> balls;
    set<int> colors;
    vector<int> color_map;
    map<int,int> inv_color_map;


    for(int i = 0 ; i < N ; i ++)
    {
        ball b;
        scanf("%d %d", &b.color, &b.size);
        b.orig_idx = i;
        if(colors.find(b.color)  == colors.end())
            {
                colors.insert(b.color);
                color_map.push_back(b.color);
            }
            
        balls.push_back(b);
    }

    int num_colors = colors.size();
    vector<int> size_table_by_color(num_colors, 0);
    sort(balls.begin(), balls.end(), sortballs);

    int i = 0;
    int j;

    for(j = 0 ; j < num_colors ; j++)
        inv_color_map[color_map[j]] = j;

    int total = 0;

    
    vector<int> ans_arr(N, 0);
    for(i = 0 ; i <N ; i ++)
    {
        size_table_by_color[inv_color_map[ balls[i].color]] += balls[i].size;
        total += balls[i].size;
        ans_arr[balls[i].orig_idx] = total - size_table_by_color[inv_color_map[balls[i].color]];
    }

    for(auto a : ans_arr)
        printf("%d\n", a);

}
