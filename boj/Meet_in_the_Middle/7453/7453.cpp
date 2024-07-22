#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#define MAX_N 4'000
// #define BRUTE_FORCE
// #define MAP
#define LOWER_BOUND
typedef long long ll;
#define endl '\n'
using namespace std;

int n;
int A[MAX_N];
int B[MAX_N];
int C[MAX_N];
int D[MAX_N];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n;
    for(int i = 0 ; i < n; i++){
        cin>>A[i]>>B[i]>>C[i]>>D[i];
    }
    
    #ifdef BRUTE_FORCE
    int res = 0;
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum = A[i];
        for(int j = 0; j < n; j++){
            sum += B[j];
            for(int k = 0; k < n; k++){
                sum+=C[k];
                for(int l = 0; l < n; l++){
                    sum+=D[l];
                    if(sum == 0){
                        res++;
                    }
                    sum-=D[l];
                }
                sum-=C[k];
            }
            sum-=B[j];
        }
        sum -=A[i];
    }
    #endif
    
    #ifdef MAP
    map<int,int> m;
    for(int i = 0; i < n; i++){
        int a = A[i];
        for(int j = 0; j < n; j++){
            if(m.find(a + B[j]) == m.end()){
                m[a+B[j]] = 1;
            } else {
                m[a+B[j]] += 1;
            }
        }
    }
    
    int m_max = (--m.end())->first;
    int m_min = m.begin()->first;
    
    int res = 0;
    for(int i = 0; i < n; i++){
        int c = C[i];
        for(int j = 0; j < n; j++){
            if( c + D[j] < m_min || m_max < c + D[j]) continue;
            auto it = m.find(-(c + D[j]));
            if( it != m.end()){
                res += it->second;
            }
        }
    }
    #endif
    
    #ifdef LOWER_BOUND
    vector<int> m(n*n);
    for(int i = 0; i < n; i++){
        int a = A[i];
        for(int j = 0; j < n; j++){
            m[i*n + j] = a + B[j];
            // m.push_back(a + B[j]);
        }
    }
    
    //sort
    std::sort(m.begin(), m.end());
    
    ll res = 0;
    for(int i = 0 ; i < n; i++){
        int c = C[i];
        for(int j = 0; j < n; j++){
            int tofind = -(c + D[j]);
            if( tofind < m[0] || m.back() < tofind) continue;
            auto it1 = lower_bound(m.begin(), m.end(), tofind);
            if( *it1 != tofind) continue;
            auto it2 = upper_bound(m.begin(), m.end(), tofind);
            res += (ll)distance(it1, it2);
        }
    }
    #endif
    
    cout<<res<<endl;
    return 0;
}