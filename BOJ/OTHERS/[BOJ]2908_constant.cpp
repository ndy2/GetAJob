#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    string A, B;
    cin>>A>>B;
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    int AA= stoi(A);
    int BB= stoi(B);
    cout<<max(AA,BB);
}
