#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define MAX_N 50
#define MAX_A 1'000
// #define DEBUG_ERA
// #define DEUBG_INIT
// #define DEBUG_MATCH
using namespace std;

int N,M;
int A[MAX_N];

vector<int> evens;
vector<int> odds;
vector<int> num2eidx;
vector<int> eidx2num;
vector<int> num2oidx;
vector<int> oidx2num;

vector<int> res;
vector<int> oddMatch; // oddMatch[i] : i번째 홀수과 연결되어 있는 짝수의 index (evens인덱스 기준)
vector<int> evenMatch; // evenMatch[i] : i번째 짝수과 연결되어 있는 홀수의 index (odds인덱스 기준)
vector<bool> visited;
vector<bool> isPrime((MAX_A<<1), true);
const int source = 0;
int omatchedwiths;
int ematchedwiths;

void eratosthenes(){
    int sqrtn = (int)sqrt((MAX_A<<1));
    isPrime[0] = isPrime[1] = false;
    for(int d = 2; d <= sqrtn; d++){
        if( isPrime[d] ){
            for(int i = d*d; i <= (MAX_A<<1); i+=d){
                isPrime[i] = false;
            }
        }
    }
    
}

bool dfs(int here, bool ishereodd){// odd    
    if(ishereodd){
        if(visited[oidx2num[here]]) return false;
#ifdef DEBUG_MATCH
        printf("dfs(%d, %d) \n", here, ishereodd);
#endif
        visited[oidx2num[here]] = true;
        for(int e = 0; e < evens.size(); e++){
#ifdef DEBUG_MATCH
    printf("in dfs, %d is",odds[here] + evens[e]);
#endif
            if( e != ematchedwiths && isPrime[odds[here] + evens[e]] ){
#ifdef DEBUG_MATCH
printf("prime! \n");
#endif
               if( evenMatch[e] == -1 || dfs( evenMatch[e], true)){
                    oddMatch[here] = e;
                    evenMatch[e] = here;
                    return true;
                }
            }
#ifdef DEBUG_MATCH
printf(" not prime! \n");
#endif
        }        
    } else { // here is even
        if(visited[eidx2num[here]]) return false;
        visited[eidx2num[here]] = true;
        for(int o = 0; o < odds.size(); o++){
            if( o != omatchedwiths && isPrime[evens[here] + odds[o]] ){
                if( oddMatch[o] == -1 || dfs( oddMatch[o], false)){
                    evenMatch[here] = o;
                    oddMatch[o] = here;
                    return true;
                }
            }
        }
        
    }
    
    return false;
}

void bipartiteMatch(){
    //exclude 
    bool firstisodd = A[0] % 2 == 1 ? true : false;
    if( firstisodd ){
        for(int e = 0; e < evens.size(); e++){
            ematchedwiths = e;
            if( !isPrime[A[0] + evens[e]] ) continue;
            int num_match = 1;
            #ifdef DEBUG_MATCH
      printf(" %d isprime ! \n", A[0] + evens[e]);
        #endif
            // reset Match
            oddMatch = vector<int> (odds.size(), -1);
            evenMatch = vector<int> (evens.size(), -1);
            
            for(int odd = 0; odd < odds.size(); odd++){
                visited = vector<bool> (N, false);
                // exclude source - even
                visited[0] = true;
                visited[eidx2num[e]] = true;
                if(dfs(odd, true)){
                #ifdef DEBUG_MATCH
        printf("dfs(%d,true) success ! \n", odds[odd]);
          #endif
                    num_match++;
                }
            }
            #ifdef DEBUG_MATCH
      printf("num_match : %d \n", num_match);
      #endif
            if (num_match >= odds.size()){
                res.push_back(evens[e]);
            } 
        }
        
    } else { // first number is even
        for(int o = 0; o < odds.size(); o++){
            omatchedwiths = o;
            if( !isPrime[A[0] + odds[o]]) continue;
            int num_match = 1;
              #ifdef DEBUG_MATCH
      printf(" %d isprime ! \n", A[0] + odds[o]);
        #endif
            oddMatch = vector<int> (odds.size(), -1);
            evenMatch = vector<int> (evens.size(), -1);
            
            for(int e = 0; e < evens.size(); e++){
                visited = vector<bool> (N,false);
                visited[0] = true;
                visited[oidx2num[o]] = true;
                if(dfs(e,false)){
                  #ifdef DEBUG_MATCH
        printf("dfs(%d,true) success ! \n", evens[e]);
          #endif
                    num_match++;
                }
                
            }
            
            if( num_match >= evens.size()){
                res.push_back(odds[o]);
            }
        }
    
    }
}


int main(){
    //pre
    eratosthenes();
#ifdef DEBUG_ERA
for(int i = 1; i <= 200; i++){
    cout<<isPrime[i]<<" ";
    if( i % 50 == 0) printf("\n");
}
#endif
    cin>>N;
    
    for(int i = 0; i < N; i++){
        cin>>A[i];
        if(A[i] % 2 == 1){ //odd
            // num2oidx[i] = odds.size();
            num2oidx.push_back(odds.size());
            // oidx2num[num2oidx[i]] = i;
            oidx2num.push_back(i);
            odds.push_back(A[i]);
        } else {
            num2eidx.push_back(evens.size());
            // num2eidx[i] = evens.size();
            // eidx2num[num2eidx[i]] = i;
            eidx2num.push_back(i);
            evens.push_back(A[i]);
        }
    }
#ifdef DEUBG_INIT
cout<<"odds : ";
for(auto o : odds){
  cout<<o<<" ";
}
cout<<endl<<"oidx2num : ";
for(auto o : oidx2num){
  cout<<o<<" ";
}
cout<<endl<<"evens : ";
for(auto e : evens){
  cout<<e<<" ";
}
cout<<endl<<"eidx2num : ";
for(auto e : eidx2num){
  cout<<e<<" ";
}
cout<<endl;
#endif
    if( odds.size() != evens.size()){
        cout<<-1<<endl;
        return 0;
    }
    
    //bipartite match
    bipartiteMatch();
    
    if(res.empty()) cout<<-1<<endl;
    else {
        sort(res.begin(), res.end());
        for(auto e : res){
            cout<<e<<" ";
        }
    }
    return 0;
}