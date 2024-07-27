// bitmasking

#include <iostream>
#include <cstring>

#define endl '\n'
using namespace std;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int M;
    cin>>M;
    string op; int x;
    int set = 0;
    while(M--){
        cin>>op;
        if(op == "add"){
            cin>>x;
            set |= (1<<x);
        } else if (op == "check"){
            cin>>x;
            if( set & (1<<x)) cout<<1<<endl;
            else cout<<0<<endl;
        } else if (op == "remove"){
            cin>>x;
            set &= ~(1<<x);
        } else if (op == "toggle"){
            cin>>x;
            set ^= (1<<x);
        } else if (op == "all"){
            set |= ( (1<<22) -1);
        } else { //empty
            set &= 0;
        }
    }

    return 0;
}  