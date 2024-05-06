//AC
#include <iostream>
#include <vector>
#include <cstring>

#define endl '\n'
using namespace std;

void solve(){
    string p;
    cin>>p; // 1 <= p.length() <= 100000
    int n;
    cin>>n;
    string Arr;
    cin>>Arr; // 0 <= Arr.length() <= 100000

    vector<int> X; int xi;
    int head = 0; int tail = 0;
    for(int i = 0 ; i < Arr.length() ;){
        if( Arr[i] == '[' || Arr[i] == ',' || Arr[i] == ']' ) i++;
        if( 0 <= Arr[i] - '0' &&  Arr[i] - '0' <= 9) {
            int num = Arr[i] - '0'; i++;
            while(0 <= Arr[i] - '0' &&  Arr[i] - '0' <= 9) {
                num *= 10;
                num += Arr[i] - '0';
                i++;
            }
            X.push_back(num);
        }
    }
    tail = X.size();
    
    bool frontIshead = true;
    // operation
    for(string::iterator p_itr = p.begin(); p_itr != p.end(); p_itr++){
        if( *p_itr == 'R'){
            frontIshead = !frontIshead;
        } else { //D
            if( head == tail || X.empty()){
                cout<<"error"<<endl;
                return ;
            } else {
                if(frontIshead){
                    head++;
                } else {
                    tail--;
                }
            }
        }
    }

    //output
    if( head == tail || X.empty()){ 
        cout<<"[]"<<endl;
        return ;
    }

    cout<<"[";
    if(frontIshead){
        for(int i = head; i < tail - 1; i++){
            cout<<X[i]<<",";
        }
        cout<<X[tail-1];
    } else {
        for(int i = tail-1; i > head; i--){
            cout<<X[i]<<",";
        }
        cout<<X[head];
    }
    cout<<"]"<<endl;
}

int main(){
    int T;
    cin>>T; // T <= 100
    while(T--){
        solve();
    }
    return 0;
}