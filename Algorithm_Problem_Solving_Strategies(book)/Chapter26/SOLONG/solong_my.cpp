#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define all(v) v.begin(), v.end()
#define ALPHABETS 26
#define endl '\n'
// #define DEBUG_SORT
// #define DEBUG_MIN
using namespace std;

typedef pair<string, int> DATA;

struct TrieNode{
    TrieNode * c[ALPHABETS];
    int idx; // 해당 노드를 마지막 노드로 가지는 단어의 idx
    int tap; // 해당 노드에서 tap을 누르면 자동완성되는 단어의 idx
    
    TrieNode() : idx(-1), tap(-1){
		memset(c, 0, sizeof(c));
	};
    ~TrieNode(){
        for(int i = 0; i < ALPHABETS; i++){
            if(c[i]) delete c[i];
        }
    }
    
    void insert(const char * k, int i){
        if(tap == -1) tap = i;
        if(*k == 0) {
            idx = i;
            return ;
        }
        if(c[*k-'A'] == nullptr)
            c[*k - 'A'] = new TrieNode();
        c[*k -'A']->insert(k+1, i);
    }
};

void print_data(const DATA & d){
    cout<<d.first<<" "<<d.second;
}

int N,M;

int minTyping(TrieNode * h, const string & w){
    vector<int> taps;
    int i = 0;
    while( i < w.length() && h->c[w[i] - 'A'] != nullptr){
#ifdef DEBUG_MIN
cout<<" i, h->idx, h->tap : "<<i<<" "<<h->idx<<" "<<h->tap<<endl;
#endif
        h = h->c[w[i] - 'A']; i++;
        taps.push_back(h->tap);
    }
#ifdef DEBUG_MIN
cout<<" out of cycle.  i, h->idx, h->tap : "<<i<<" "<<h->idx<<" "<<h->tap<<endl;
#endif

    return i >= w.length() && h->idx != -1 ? 
            min<int>( lower_bound( all(taps), h->idx) - taps.begin() + 2, w.length())
        :   w.length();
}

vector< DATA > raw_data;

void solve(){
    cin>>N>>M;
	raw_data.clear();
    string tmp;
    int appear;
    for(int i = 0 ; i < N; i++){
        cin>>tmp>>appear;
        raw_data.push_back({tmp, appear});
    }    
    
    //sort
    sort( all(raw_data), [](const DATA & d1, const DATA & d2){
        if( d1.second != d2.second) return d1.second > d2.second;
        return d1.first < d2.first;
    });


    TrieNode * root = new TrieNode();
    for(int i = 0; i < N; i++){
        const auto & d = raw_data[i];
        root->insert(d.first.c_str(), i);
    }
	
    root->tap = -1;
	
#ifdef DEBUG_SORT
cout<<"--------SORTED RAW_DATA-----------"<<endl;
for(const auto & d : raw_data){
    print_data(d);
    cout<<endl;
}
cout<<endl;
#endif
	
    //minTyping
    int res = 0;
	while(M--){
		cin>>tmp;
		int mint = minTyping(root, tmp);
        res += mint+1;
#ifdef DEBUG_MIN
cout<<"mint :" <<mint<<endl;
#endif
	}
    cout<<res-1<<endl;
}

int main(){
    int C;
    cin>>C;
    while(C--) solve();
}