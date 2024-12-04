#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

#define MAX_N 500
#define endl '\n'

// #define DEBUG_LIS
// #define DEBUG_KLIS
using namespace std;
typedef long long ll;

int N;
ll K;
vector<int> arr;
vector<int> nextS[MAX_N+1];

int lis;

int cache[MAX_N] = {0};
ll kcache[MAX_N+1] = {0};

int LIS(int i){
    int & ret = cache[i];
    if(ret) return ret;
    ret = 1;
    for(int j = i+1; j < arr.size(); j++){
        if( arr[i] < arr[j]){
            ret = max(ret, 1 + LIS(j));
        }
    }
    
    for(int j = i + 1; j < arr.size(); j++){
        if(arr[i] < arr[j] && 1 + LIS(j) == ret){
            nextS[i+1].push_back(j);
        }
    }

    sort(nextS[i+1].begin(), nextS[i+1].end(), [](const int & i1, const int & i2){
        return arr[i1] < arr[i2];
    });
    
    return ret;
}

ll kLIS(int i, vector<int> & clis){
#ifdef DEBUG_KLIS
    printf("kLIS(%d) \n", i);
#endif

    ll & ret = kcache[i+1];
    if(clis.size() >= lis){
        if(K==1LL) {
            
#ifdef DEBUG_KLIS
            printf("found klis! : \n");
#endif
	
            for(auto e : clis){
                cout<<e<<" ";
            }
            K--;
            return 0;
        }
        K--;
#ifdef DEBUG_KLIS
printf(" klis(%d) ret : 1 \n", i);
#endif
        return ret = 1LL;
    }

    for(auto jdx : nextS[i+1]){
        int num = arr[jdx];
        if( kcache[jdx+1] && kcache[jdx+1] < K){
            // printf("used kcache[%d] \n", jdx);
            K -= kcache[jdx+1];
			ret += kcache[jdx+1];
        } else {
            clis.push_back(num);
            ret+=kLIS(jdx, clis);
            clis.pop_back();
            if( K <= 0) return 0;
        }
    }
#ifdef DEBUG_KLIS
printf(" klis(%d) ret : %lld \n", i, ret);
#endif
    return ret;
}

void solve(){
    cin>>N>>K;
    arr.resize(N);
    fill(cache, cache + N, 0);
    fill(kcache, kcache + N + 1, 0);

    for(int i = 0; i < N; i++){
        cin>>arr[i];
        nextS[i].clear();
    }

	nextS[N].clear();

    lis = 1;
    for(int i = 0; i < N; i++){
        lis = max(lis, LIS(i));
    }

    for(int i = 0 ; i < N; i++){
        if(LIS(i) == lis){
            nextS[0].push_back(i);
        }
    }

    sort(nextS[0].begin(), nextS[0].end(), [](const int & i1, const int & i2){
        return arr[i1] < arr[i2];
    });

#ifdef DEBUG_LIS
for(int i = 0 ; i < N; i++){
    cout<<cache[i]<<" ";
}
cout<<endl;
#endif

    cout<<lis<<endl;

    vector<int> clis;

    for(auto idx : nextS[0]){
        int num = arr[idx]; 
        clis.push_back(num);
        kLIS(idx, clis);
        clis.pop_back();
        if( K<=0 ) break;
    }
    cout<<endl;

#ifdef DEBUG_KLIS
for(int i = 1; i <= N; i++){
    cout<<kcache[i]<<" ";
}
cout<<endl;
#endif

}

int main(){
    int C;
    cin>>C;
    while(C--) solve();
    return 0;
}