#include <iostream>
#include <vector>

#define MAX_N 100'000
using namespace std;
typedef long long ll;

struct TreeNode{
public:
    int height;
    vector<int> children;
    TreeNode(int height) : height(height){};
};

vector<TreeNode *> tree;

int N,S,D;

ll ret = 0;

int dfs1(int here, int p){
    for(const auto & c : tree[here]->children){
        if( c != p){
            tree[here]->height = max(tree[here]->height, dfs1(c,here)+1);
        }
    }
    return tree[here]->height;
}

void dfs2(int here, int p){
    for(const auto & c : tree[here]->children){
        if(c != p){
            if(tree[c]->height >= D){
                ret+=2;
                dfs2(c,here);
            } else {
                // do nothing
            }
        }
    }
}

int main(){
    cin>>N>>S>>D; S--;
    int x,y;
    tree.resize(N);
    TreeNode *p, *c;
    for(int i = 0; i < N-1; i++){
        cin>>x>>y; x--; y--;
        p = tree[x] ? tree[x] : new TreeNode(0); 
        c = tree[y] ? tree[y] : new TreeNode(0);
        tree[x] = p;
        tree[y] = c;
        p->children.push_back(y);
        c->children.push_back(x);
    }
    
    //dfs1 - get height
    dfs1(S,-1);

// for(int i =0 ; i <N; i++){
//     cout<<tree[i]->height<<" ";
// }
// cout<<endl;
    //dfs2 - get answer
    dfs2(S,-1);
    
    cout<<ret<<endl;
    return 0;
}