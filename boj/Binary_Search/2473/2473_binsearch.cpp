#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

// #define DEBUG_SOLUTIONS
// #define DEBUG_BINARY

typedef long long ll;
using namespace std;
vector<ll> Solutions;

int main(){
    int N;
    cin>>N;
    ll temp;
    for(int i = 0 ; i < N; i++){
        cin>>temp;
        Solutions.push_back(temp);
    }
    
    //sort
    std::sort(Solutions.begin(), Solutions.end());

#ifdef DEBUG_SOLUTIONS
for(auto s : Solutions){
    cout<<s<<" ";
}
cout<<endl;
#endif

    ll solution1 = Solutions[0];
    ll solution2 = Solutions[1];
    ll solution3 = Solutions[2];
    ll res = abs(solution1 + solution2 + solution3);
    ll s1,s2;
    //binary search
    for(int i = 0 ; i < N; i++){
        if(res <= 0 ) break;
        s1 = Solutions[i];
        for(int j = i+1; j < N; j++){

            s2 = Solutions[j];
#ifdef DEBUG_BINARY
cout<<"s1,s2 : "<<s1<<","<<s2<<" ";
#endif
            auto iter = std::lower_bound(Solutions.begin(), Solutions.end(), -(s1+s2));
            auto temp = iter;
            
            if(iter == Solutions.end()){
#ifdef DEBUG_BINARY
cout<<"only consider down , *iter : "<<*iter<<endl;
#endif
                //only consider down
                iter--;
                while(iter != Solutions.begin() && (*iter == s1 || *iter == s2)) --iter;
                if(iter != Solutions.begin() || (iter == Solutions.begin() && *iter != s1 && *iter != s2)){
#ifdef DEBUG_BINARY
cout<<"down , *iter : "<<*iter<<endl;
#endif
                    if( abs(s1 + s2 + *iter) < res){
                        res = abs(s1 + s2 + *iter);
                        solution1 = s1; solution2 = s2; solution3 = *iter;
                    }
                }
            } else if(iter == Solutions.begin()){
#ifdef DEBUG_BINARY
cout<<"only consider up , *iter : "<<*iter<<endl;
#endif
                //only consider up
                while( iter != Solutions.end() && (*iter == s1 || *iter == s2) ){
                    ++iter;
                }
                if(iter != Solutions.end()){
#ifdef DEBUG_BINARY
cout<<" up , *iter : "<<*iter<<endl;
#endif
                    if( abs(s1 + s2 + *iter) < res){
                        res = abs(s1 + s2 + *iter);
                        solution1 = s1; solution2 = s2; solution3 = *iter;
                    }
                }
            } else {
#ifdef DEBUG_BINARY
cout<<" consider both up and down, *iter : "<<*iter<<endl;
#endif
                //up
                while( iter != Solutions.end() && (*iter == s1 || *iter == s2) ){
                    ++iter;
                }
                if(iter != Solutions.end()){
#ifdef DEBUG_BINARY
cout<<" up , *iter : "<<*iter<<endl;
#endif
                    if( abs(s1 + s2 + *iter) < res){
                        res = abs(s1 + s2 + *iter);
                        solution1 = s1; solution2 = s2; solution3 = *iter;
                    }
                }
                //down
                iter = --temp;
                while( iter != Solutions.begin() && (*iter == s1 || *iter == s2)){
                    --iter;
                }
                if(iter != Solutions.begin() || (iter == Solutions.begin() && *iter != s1 && *iter != s2)){
#ifdef DEBUG_BINARY
cout<<"down , *iter : "<<*iter<<endl;
#endif
                    if( abs(s1 + s2 + *iter) < res){
                        res = abs(s1 + s2 + *iter);
                        solution1 = s1; solution2 = s2; solution3 = *iter;
                    }
                } 
            }
            if(res <= 0) break;
        }
    }
    
    if(solution1 > solution3) swap(solution1, solution3);
    if(solution1 > solution2) swap(solution1, solution2);
    if(solution2 > solution3) swap(solution2, solution3);
    cout<<solution1<<" "<<solution2<<" "<<solution3<<endl;
    return 0;
}