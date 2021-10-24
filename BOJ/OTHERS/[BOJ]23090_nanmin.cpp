#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

int main()
{
    int N;
    vector<int> heights;
    long long sumGaro = 0;
    cin>>N;
    int x,y;
    cin>>x>>y;
    sumGaro += abs(x);
    heights.push_back(y);
    
    int mid = y;
    printf("%d %d\n", y,abs(x));

    priority_queue<int> maxpq;
    priority_queue<int,vector<int>,greater<int>> minpq;

    for(int i = 1 ; i < N ; i++){
        cin>>x>>y;
        sumGaro +=abs(x);
        heights.push_back(y);
        int prev_mid = mid;
        if(mid < y ){
            minpq.push(y);
            if(minpq.size() == maxpq.size()+2){
                maxpq.push(mid);
                mid = minpq.top();
                minpq.pop();
            }
        }else{
            maxpq.push(y);
            if(maxpq.size() == minpq.size()+1){
                minpq.push(mid);
                mid = maxpq.top();
                maxpq.pop();
            }
        }

        long long sumSero = sumSero + abs(prev_mid - mid) * (minpq.size()-maxpq.size()) + abs(mid-y);

        printf("%lld %lld\n", mid, sumGaro + sumSero);
    }

}