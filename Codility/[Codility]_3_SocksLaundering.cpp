//https://app.codility.com/demo/results/trainingETQZ7B-CS6/

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(int K, vector<int> &C, vector<int> &D) {
    // write your code in C++14 (g++ 6.2.0)
    int cleaned_pair = 0;

    //clean : need one clean sock to add one;
    vector<bool> clean(vector<bool>(51,0));
    for(auto c : C)
    {
        if(clean[c]) 
        {
            cleaned_pair ++;
            clean[c] = false;
        }
        else {
            clean[c] = true;
        }
    }
    
    //
    vector<int> dirty(vector<int>(51,0));
    for(auto d : D)
        dirty[d]++;
    
    //한개 남은 것들 다 처리
    for(int i = 0 ; i < 51 ; i++)
    {
        if(clean[i] && dirty[i]>=1 && K>=1)
            {
                dirty[i]--;
                K--;
                cleaned_pair++;
            }
    }

    //더러운 애들 중 2개 이상인 애들 처리
    while(1)
    {
        // printf("K : %d\n", K);
        // printf("cleaned_pair : %d\n", cleaned_pair);
        bool is_cleaned_this_loop = false;
        for(int i = 0 ; i < 51 ; i++)
            if(dirty[i]>=2 && K>=2)
            {
                is_cleaned_this_loop = true;
                cleaned_pair++;
                dirty[i]-=2;
                K-=2;
            }
        if(K<=1 || !is_cleaned_this_loop)
             break;
    }

    return cleaned_pair;
}