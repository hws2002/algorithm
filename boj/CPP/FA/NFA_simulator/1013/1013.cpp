#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

#define MAX_STATE 7
#define MAX_ALPHABET 3
#define eps -1

#define endl '\n'
// #define DEBUG_NFA_CONSTRUCTION
// #define DEBUG_NFA
using namespace std;


vector< vector< vector<int> > > tran {
    {{eps},{5},{1}},
    {{eps},{2},{eps}},
    {{eps},{3},{eps}},
    {{eps},{3},{4}},
    {{6},{eps},{4}},
    {{eps},{eps},{6}},
    {{0},{eps},{eps}}
};

struct NFA{
public:
    int num_state;
    int num_alphabet;
    int start;
    vector< vector< vector<int> > > trans;
    vector<int> F;
    vector<bool> alreadyOn;
    string nfainput;
    int idx;
    stack<int> oldStates;
    stack<int> newStates;
    char c;
    
    NFA(vector< vector< vector<int> > > & trans, vector<int> F) : start(0), trans(trans), F(F), nfainput("#"), idx(0){
        num_state = trans.size();
        num_alphabet = trans[0].size();
        sort(F.begin(), F.end());
        init();
    }
    
    void init(){
        alreadyOn.resize(num_state, false);
        while(!oldStates.empty()) oldStates.pop();
        while(!newStates.empty()) newStates.pop();
        idx = 0;
        //e_closure(s0)
        addState(start);
        replaceStack();
        nextChar();
    }
    
    void read(const string & s){
        nfainput = s;
        idx = 0;
        init();
    }
    
    void nextChar(){
        // assert(idx < input.size());
        c = nfainput[idx++];
    }
      
    void addState(int s){
        newStates.push(s);
        alreadyOn[s] = true;
        for(auto & t : move(s,eps)){
            if( t != eps && !alreadyOn[t]){
                addState(t);   
            }
        }
    }
    
    void replaceStack(){
        while(!newStates.empty()){
            auto t = newStates.top(); newStates.pop();
            oldStates.push(t);
            alreadyOn[t] = false;
        }
    }

    vector<int>& move(const int & from, const int & to){
        return trans[from][to+1];
    }
    
    void e_closure(){
        while(!oldStates.empty()){
            auto s = oldStates.top(); 
#ifdef DEBUG_NFA
            cout<<"s :"<<s<<endl;
#endif
            for( const auto & t : move(s,c-'0') ){
#ifdef DEBUG_NFA
                cout<<"t :"<<t<<endl;
#endif
                if( t != eps && !alreadyOn[t]){
                    addState(t);
                }
            }
            oldStates.pop();
        }
        
        replaceStack();
    }
        
    bool isAccepted(stack<int> S){
        while(!S.empty()){
            auto s = S.top(); S.pop();
            auto it = lower_bound(F.begin(), F.end(), s);
            if( it != F.end() && *it == s) return true;
        }
        return false;
    }
};

NFA nfa(tran, vector<int> {6});

void solve(){
    string x;
    cin>>x;
    x+='#'; // indicates end of string
    
    nfa.read(x);
    
    // e_closure(s0)
    // c = nextChar()
    nfa.init();
    while(nfa.c != '#'){
#ifdef DEBUG_NFA
        cout<<"nfa.c : "<<nfa.c<<endl;
#endif
        nfa.e_closure();
        nfa.nextChar();
    }
    
    if(nfa.isAccepted(nfa.oldStates)) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
}    

int main(){
#ifdef DEBUG_NFA_CONSTRUCTION
    for(int i = 0; i < nfa.num_state; i++){
        for(int j = eps; j < nfa.num_alphabet-1; j++){
            cout<<"{";
            for(auto e : nfa.move(i,j)){
                cout<<e<<",";
            }
            cout<<"} ";
        }
        cout<<endl;
    }
    
    cout<<nfa.c<<endl;
#endif
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}