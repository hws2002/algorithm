#include <iostream>
#include <set>

#define MAX_G 100'000

// #define DEBUG_SET
using namespace std;

int G,P;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>G>>P;
    
    //creat set
    int arr[G];
    for(int i = 0; i < G; i++){
        arr[i] = -(i+1);
    }
    
    set<int> S(arr, arr + G);
#ifdef DEBUG_SET
for(auto elem : S){
    cout<<elem<<" ";
}
cout<<endl;
#endif

    int gi;
    for(int i = 0; i < P; i++){        
        cin>>gi;
        auto it = S.lower_bound(-gi);
        if(it == S.end()){
            cout<<i<<endl;
            break;
        }
        S.erase(it);
        if(i == P-1) cout<<P<<endl;
    }
    
    return 0;
}