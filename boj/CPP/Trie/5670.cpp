#include <iostream>
#include <cstring>
#include <vector>
#include <map>

#define MAX_N 100'000
#define endl '\n'
using namespace std;

int N;

struct TrieNode{
public:
    map<char, TrieNode> c;
    bool end;
    TrieNode() : end(false){};
};

void insert(TrieNode & root, const string & s){
    TrieNode * here = &root;
	// printf("%p \n",here);
    for(int i = 0 ; i < s.size(); i++){
		// printf("s[%d] : %c, ", i, s[i]);
		if( here->c.find(s[i]) == here->c.end()){
			// cout<<"creating new TrieNode"<<endl;
            here->c[s[i]] = TrieNode();
        }
        here = &(here->c[s[i]]);
		// printf(" here address : %p \n",here);

    }
    here->end = true;
}

double ret = 0;

void dfs(TrieNode & root, double cost){
    TrieNode * here = &root;
    cost++;
    while(here->c.size() == 1 && !here->end){
        here = &(here->c.begin()->second);
    }
    
    if(here->end)
        ret += cost;

    for(auto & [word, node] : here->c){
        dfs(node, cost);
    }
}


void printTrie(const char & w, TrieNode & node){
    cout<<w<<endl;
    for(auto & [word, n] : node.c){
        printTrie(word, n);
    }
}

void solve(){
    string s;
    TrieNode root = TrieNode();
    ret = 0;
    for(int i = 0 ; i < N; i++){
        cin>>s;
        insert(root,s);
    }
    // printf("%p\n", root);
    // cout<<root.c.size()<<endl;
    
// for(auto & [word, node] : root.c){
//     printTrie(word,node);
// }
    //dfs
    for(auto & [word, node] : root.c){
        dfs(node,0);
    }
    printf("%.2f \n", ret/double(N));
}

int main(){
    while(cin>>N){
        solve();
    }
}