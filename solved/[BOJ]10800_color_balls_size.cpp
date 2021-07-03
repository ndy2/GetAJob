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
    int orig_idx;
}ball;



typedef vector<ball> vb;

int main(){

    int N;
    
    scanf("%d", &N);
    set<int> colors;
    vector<int> color_map;
    map<int,int> inv_color_map;
    vb balls[2002];

    for(int i = 0 ; i < N ; i ++)
    {
        ball b;
        int size;
        scanf("%d %d", &b.color, &size);
        b.orig_idx = i;
        if(colors.find(b.color)  == colors.end())
            {
                colors.insert(b.color);
                color_map.push_back(b.color);
            }
      balls[size].push_back(b); 
    }

    int num_colors = colors.size();
    vector<int> size_table_by_color(num_colors, 0);

    int i = 0;
    int j;

    for(j = 0 ; j < num_colors ; j++)
        inv_color_map[color_map[j]] = j;

    int total = 0;

    
    vector<int> ans_arr(N, 0);
    for(i = 0 ; i <2002 ; i ++)
    {
        for(auto b : balls[i])
        {
        }
        for(auto b : balls[i])
        {
           ans_arr[b.orig_idx] = total - size_table_by_color[inv_color_map[b.color]];
        }
        for(auto b : balls[i])
        {            total += i;
                    size_table_by_color[inv_color_map[ b.color]] += i;

        }
    }

    for(auto a : ans_arr)
        printf("%d\n", a);
}
