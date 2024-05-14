//ValueWithCapacity[capacity] : 무게를 capacity 만큼 담을 수 있을때 취할 수 있는 최대 v \
(capacity 보다 더 적은 용량을 담아도 됌)

#include <iostream>

using namespace std;

int N,K;
int ValueWithCapacity[100'001] = {0};


void load(const int & w, const int & v){
    for (int capacity = K - w; capacity >= 0; capacity--){
        ValueWithCapacity[capacity + w] = max ( ValueWithCapacity[capacity + w], ValueWithCapacity[capacity] + v);
    }    
}

int main(){
    cin>>N>>K;
    
    //solve
    int w,v;
    for(int i = 0; i < N; i++){
        cin>>w>>v;
        load(w,v);
    }
    
    //output
    cout<<ValueWithCapacity[K]<<endl;
    return 0;
}