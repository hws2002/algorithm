#include <iostream>
#include <stack>

#define MAX_N 500'000
using namespace std;
typedef long long ll;

int N;
int A[MAX_N] = {0};

stack< pair<int,int> > s;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N;
    int temp;
    ll res = 0;
    cin>>temp;
    s.push({temp,1});
    for(int i = 1; i < N; i++){
        cin>>temp;
        if( s.top().first > temp){
            res += 1;
            s.push({temp,1});
        } else {
            
            while(!s.empty() && s.top().first < temp){
                res += s.top().second;
                s.pop();
            }
            
            int num_temp = 0;    
            
            if(!s.empty() && s.top().first == temp){
                num_temp = s.top().second;
                res += num_temp;
                s.pop();
            }
        
            if( !s.empty() )
                res += 1;
            s.push({temp,1+num_temp});
        }
    }
    
    cout<<res<<endl;
    
    return 0;
}