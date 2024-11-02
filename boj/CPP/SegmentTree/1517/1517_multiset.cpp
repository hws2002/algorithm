#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#define MAX_N 500'000
using namespace std;
typedef long long ll;

int N;
vector<int> A;
multiset<int> ms;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    A.resize(N);
    for(int i = 0; i < N; i++){
        cin >> A[i];
    }
    
    // solve
    ms.insert(A.back());
    ll res = 0;
    for(int i = A.size() - 2; i >= 0; i--){
        auto it = ms.lower_bound(A[i]);
        res += distance(ms.begin(), it);
        ms.insert(A[i]);
    }

    cout << res << endl;
    return 0;
}
