#include <iostream>
#include <vector>

#define MAX_N 51
#define endl '\n'
// #define DEBUG_LENGTH
using namespace std;
typedef long long ll;

int n;
ll p,l;

ll length[MAX_N] = {0};

void curve(const string& seed, int g){
    if(l <= 0 ) return ;
    
    if(g==0){
        if( seed.size() < p){
            p -= seed.size();
        } else {
            for(int i = 0; i < seed.size(); i++){
                if(p == 1){
                    if( l > 0 ){
                        cout<<seed[i];
                        l--;
                    }
                    if( l == 0 ) return;
                }
                else p--;
            }
        }
        return ;
    }

    for(int i = 0 ; i < seed.size(); i++){
        if(seed[i] == 'X'){
            if( length[g] < p)
                p -= length[g];
            else
                curve("X+YF",g-1);
        } else if (seed[i] == 'Y'){
            if( length[g] < p)
                p -= length[g];
            else  
                curve("FX-Y", g-1);
        } else {
            if(p==1){ 
                if(l > 0){
                    cout<<seed[i];
                    l--;
                }
                if(l==0) return;
            }
            else p--;
        }
        if(l==0) return;
    }
}

void solve(){
    cin>>n>>p>>l;
    curve("FX",n);
    cout<<endl;
}

int main(){
    length[0] = 1;
    for(int i = 1 ; i < MAX_N; i++){
        length[i] = 2LL*length[i-1] + 2;
    }

#ifdef DEBUG_LENGTH
for(int i = 0; i < MAX_N ; i++){
    cout<<length[i]<<" ";
    if(i%10==0) cout<<endl;
}
cout<<endl;
#endif

    int c;
    cin>>c;
    while(c--) solve();
    return 0;
}