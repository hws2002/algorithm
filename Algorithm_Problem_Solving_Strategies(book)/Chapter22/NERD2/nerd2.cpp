#include <iostream>
#include <map>

#define endl '\n'

// #define DEBUG_REMOVE
// #define DEBUG_NERD
using namespace std;

int removeDisqualifed(map<int,int> & m, map<int,int>::iterator itr){
    int q = itr->second;
#ifdef DEBUG_REMOVE
cout<<"q : "<<q<<endl;
#endif
    int ret = 0;
    auto jtr = itr;
    while(itr != m.begin()){
        jtr--;
#ifdef DEBUG_REMOVE
        cout<<"jtr->second : "<<jtr->second<<endl;
#endif
        if(jtr->second < q){
            m.erase(jtr);
            jtr = itr;
            ret++;
        } else break;
    }
    return ret;
}

void solve(){
    
    int N;
    cin>>N;
    int res = 0;
    int p,q;
    map<int,int> Nerds;
    for(int i = 0; i < N; i++){
        cin>>p>>q;
        // check if the input is nerd
        auto it = Nerds.lower_bound(p);
        int num_nerds = Nerds.size();
        if(it != Nerds.end() && it->second > q){ // input is not nerd
            //do nothing
        } else { //input is nerd
#ifdef DEBUG_REMOVE
cout<<"input is nerd"<<endl;
#endif
            Nerds[p] = q;
            num_nerds++;
            //find dis-qualified nerds
            it--;
            auto toremove = removeDisqualifed(Nerds,it);
#ifdef DEBUG_REMOVE
cout<<"toremove : "<<toremove<<endl;
#endif
            num_nerds -= toremove;
        }
#ifdef DEBUG_NERD
for(auto e : Nerds){
    cout<<"("<<e.first<<","<<e.second<<") ";
}
cout<<endl;
cout<<num_nerds<<endl;
#endif
        res += num_nerds;
    }
    
    cout<<res<<endl;
}

int main(){
    int C;
    cin>>C;
    while(C--)solve();
    return 0;
}