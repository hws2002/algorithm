#include <iostream>
#include <unordered_set>
#include <cstring>
#include <set>

using namespace std;

int N,M;

int main(){
    int N, M;
    cin>>N>>M;
    unordered_set<string> haventHeard;
    unordered_set<string> haventSeen;
    
    string temp;
    for(int i = 0 ; i <N; i++){
        cin>>temp;
        haventHeard.insert(temp);
    }

    for(int i = 0; i < M; i++){
        cin>>temp;
        haventSeen.insert(temp);
    }
    
    string toFind;
    set<string> overlap;
    if( N < M){
        for(unordered_set<string>::iterator iter = haventHeard.begin(); iter != haventHeard.end(); iter++){
            if(haventSeen.find(*iter) != haventSeen.end()) overlap.insert(*iter);
        }
    } else {
        for(unordered_set<string>::iterator iter = haventSeen.begin(); iter != haventSeen.end(); iter++){
            if(haventHeard.find(*iter) != haventHeard.end()) overlap.insert(*iter);
        }
    }
    
    //output
    cout<<overlap.size()<<endl;
    for(auto name : overlap){
        cout<<name<<endl;
    }
    return 0;
}