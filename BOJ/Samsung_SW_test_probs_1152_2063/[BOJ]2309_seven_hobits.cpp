#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
vector<int> portion(3,0);


int main()
{
    vector<int> heights(9,0);
    for(int i = 0 ; i < 9 ; i++)
        cin>>heights[i];

    int sum = 0;
    for(int i = 0 ; i < 9 ; i ++)
        sum+=heights[i];
    
    int target = sum-100;
    vector<int> ind(9,0);
    fill_n(ind.end()-2,2,1);

    do{
        int cur = 0;
        for(int i = 0 ; i < 9 ; i++)
            if(ind[i]==1)
                cur+=heights[i];
        if(cur == target)
            break;
    }while(next_permutation(ind.begin(),ind.end()));

    vector<int> ind_hobits;
    int found = 0;
    for(int i = 0 ; i < 9 ; i++)
        if(ind[i]==1){
            heights.erase(heights.begin()+i-found);
            found++;
            }
    sort(heights.begin(), heights.end());
    for(auto h : heights)
        cout<<h<<"\n";
    
    return 0;
}