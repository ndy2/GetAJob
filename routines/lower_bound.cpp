#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{   vector<int> vec = {1,2,3,3,3,5,5,6,6,7,8};
    vector<int>::iterator lower_bound3 = lower_bound(vec.begin(), vec.end(),3);
    vector<int>::iterator lower_bound4 = lower_bound(vec.begin(), vec.end(),4);

    cout<<"lower bound : n을 이상의 수 중 가장 처음 등장하는 index의 iterator 없으면 end"<<endl;

    cout<<"lower_bound3 : " << *lower_bound3<< " has of index " << lower_bound3 - vec.begin() <<endl;
    cout<<"lower_bound4 : " << *lower_bound4<< " has of index " << lower_bound4 - vec.begin() <<endl;

}
