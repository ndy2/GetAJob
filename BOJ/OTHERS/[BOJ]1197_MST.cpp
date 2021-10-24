#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int V,E;
vector<vector<int>> edges;
vector<int> parents;
vector<int> setSize;

bool mysort(vector<int> a, vector<int> b){
    return a[2]<b[2];
}

void input(){
    cin>>V>>E;
    for(int e = 0 ; e < E ; e++){
        int A,B,C;
        cin>>A>>B>>C;
        edges.push_back({A,B,C});
    }
    parents.push_back(0);
    setSize.push_back(1);
    for(int i = 1 ; i <= V ; i++){
        parents.push_back(i);
        setSize.push_back(1);
    }

    sort(edges.begin(), edges.end(), mysort);
}

int _find(int a){
    if(a==parents[a])
        return a;
    else{
        return  parents[a]=_find(parents[a]);
    }
}

void _union(int a, int b){

    int idx1 = _find(a);
    int idx2 = _find(b);

    if(setSize[idx1]<setSize[idx2]){
        swap(idx1,idx2);
    }

    parents[idx2] = parents[idx1];

    setSize[idx1] +=setSize[idx2];
    setSize[idx2] = 0;

}

void solve(){
    int cost = 0 ;

    int numEdges = 0;
    for(auto e : edges){
        if(_find(e[0])!=_find(e[1]))
            {
                _union(e[0],e[1]);
                cost+=e[2];
            }
    }

    cout<<cost;
}

int main(){
    input();
    solve();
}