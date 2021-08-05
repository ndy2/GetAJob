// you can use includes, for example:

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

// #https://app.codility.com/demo/results/training3XRZDR-U2N/

int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)

    int ans = 0;
    for(auto a : A)
        ans ^= a;
    return ans;
}
