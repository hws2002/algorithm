#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define all(v) v.begin(), v.end()
#define ALPHABETS 26
#define endl '\n'
// #define DEBUG_SORT
// #define DEBUG_MIN
// #define DEBUG_NODE

using namespace std;

typedef pair<string, int> DATA;

struct TrieNode{
    TrieNode* c[ALPHABETS];
    int idx; // 해당 노드를 마지막 노드로 가지는 단어의 idx
    int tap; // 해당 노드에서 tap을 누르면 자동완성되는 단어의 idx
    
    TrieNode() : idx(-1), tap(-1){
		memset(c, 0, sizeof(c));
	};
	
    ~TrieNode(){
        for(int i = 0; i < ALPHABETS; i++){
            if(c[i]) {
#ifdef DEBUG_NODE
				cout<<"deleting "<<c[i]<<endl;
#endif
				delete c[i];
			}
        }
    }
    
    void insert(const char * k, int i){
        if(tap == -1) tap = i;
        if(*k == 0) {
            idx = i;
            return ;
        } else {
			int index = *k - 'A';
			if(c[index] == nullptr){
				c[index] = new TrieNode();
#ifdef DEBUG_NODE
				cout << "Allocating node for character " << *k << " at index " << index << " (address: " << c[index] << ")" << endl;
			} else {
	 			  cout << "Reusing existing node for character " << *k << " at index " << index << " (address: " << c[index] << ")" << endl;
#endif
			}
			c[index]->insert(k+1, i);
		}
    }
};

void print_data(const DATA & d){
    cout<<d.first<<" "<<d.second;
}



int getWordidx(TrieNode * h, const string & w){
    int i = 0;
    while( i < w.length()  && h->c[w[i] - 'A'] != nullptr){
#ifdef DEBUG_MIN
		cout<<"h : "<<h<<endl;
		for(int i = 0; i < 26; i++){
			if(h->c[i]){
				cout<<"h->c["; printf("%c",i+'A'); cout<<"] : "<<h->c[i]<<endl;
			}
		}
#endif
        h = h->c[w[i] - 'A']; i++;
    }
    
    return i >= w.length()? h->idx : -1;
}

int minTyping(TrieNode * root, const string & w){
	TrieNode * h = root;
    int w_idx = getWordidx(h,w);
    if(w_idx < 0) return w.length();
#ifdef DEBUG_MIN
	cout<<"w_idx : "<<w_idx<<" ";
#endif
    int i = 0; 
	h = root;
    while( i < w.length()){
        h = h->c[w[i] - 'A'];
        if(h->tap == w_idx) return min<int>(i+2, w.length());
        i++;
    }
	return w.length();
}


void solve(){
	int N,M;
    cin>>N>>M;
	vector< DATA > raw_data;
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

	TrieNode * root;
    root = new TrieNode();
    for(int i = 0; i < N; i++){
        const auto & d = raw_data[i];
		// cout<<"insert : "<<d.first<<endl;
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
	delete root;
}

int main(){
    int C;
    cin>>C;
    while(C--) solve();
}