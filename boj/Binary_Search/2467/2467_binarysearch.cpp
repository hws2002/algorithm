#include <iostream>
#include <set>
#include <limits.h>

#define MAX_N 100'000
using namespace std;

int N;

set<int> solutions;
int s1 = 0;
int s2 = 0;

int main(){
    int res = INT_MAX;
    cin>>N;
    int solution;
    cin>>s1; solutions.insert(s1);
    cin>>s2; solutions.insert(s2);
    res = abs(s1 + s2);
    
    for(int i = 2; i < N; i++){
        cin>>solution; if(res == 0) continue;

        auto iter = solutions.lower_bound(-solution);
        if(iter != solutions.end()){
            if( abs((*iter) + solution) < res){
                res = abs((*iter) + solution);
                s1 = (*iter);
                s2 = solution;
            }
        }
        if(iter != solutions.begin()){
            if( abs((*--iter) + solution) < res){
                res = abs((*iter) + solution);
                s1 = (*iter);
                s2 = solution;
            }    
        }
        
        solutions.insert(solution);
    }
    
    //output
    if(s1 > s2) swap(s1,s2);
    cout<<s1<<" "<<s2<<endl;
    return 0;
}