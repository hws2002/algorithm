#include <iostream>

#define MOD 20090711
#define endl '\n'

// #define DEBUG_TREAP
// #define DEBUG_LOOP
using namespace std;

struct RNG{
    int seed, a,b;
    RNG(int seed, int a, int b) : seed(seed), a(a), b(b){};
    
    int next(){
        int ret = seed;
        seed = ( 1LL * seed * a + b) % MOD;
        return ret;
    }
};


template <typename T>
struct TreapNode{
	T key;
	int priority, size;
	TreapNode<T> *left, *right;
	TreapNode<T>(const T & k) : key(k), priority(rand()), size(1), left(nullptr), right(nullptr){};
	~TreapNode<T>(){
	    if(left) delete left;
	    if(right) delete right;
	}
	
	void setLeft(TreapNode<T> * l) {left = l; calcSize();}
	void setRight(TreapNode<T> * r) {right = r; calcSize();}
	
	void calcSize(){
		size = 1;
		if(left) size += left->size;
		if(right) size += right->size;
	}
};

template <typename T>
pair<TreapNode<T> *, TreapNode<T> * > split(TreapNode<T> * root, T key){
    if(root == nullptr) return {nullptr, nullptr};
    if(root->key < key){
        auto rs = split(root->right, key);
        root->setRight(rs.first);
        return {root, rs.second};
    } else {
        auto ls = split(root->left, key);
        root->setLeft(ls.second);
        return {ls.first, root};
    }
}

template <typename T>
TreapNode<T> * insert(TreapNode<T> * root,  TreapNode<T> * node){
	if(root==nullptr) return node;
	if(root->priority < node->priority){
		auto lr = split(root, node->key);
		node->setLeft(lr.first);
		node->setRight(lr.second);
		return node;
	} else {
		if( root->key < node->key){
			root->setRight(insert(root->right, node));
		} else {
			root->setLeft(insert(root->left, node));
		}
		return root;
	}
}

template <typename T>
TreapNode<T> * merge(TreapNode<T> * l, TreapNode<T> * r){
    if(l == nullptr) return r; //만약 둘다 NULL이라면 nullptr을 반환
    if(r == nullptr) return l; 
    if( l->priority < r->priority){
        r->setLeft(merge(l, r->left));
        return r;
    } else {
        l->setRight(merge(l->right, r));
        return l;
    }
}

template <typename T>
TreapNode<T> * erase(TreapNode<T> * root, T key){
    if( root == nullptr ) return root;
    if( root->key == key){
        TreapNode<T> * ret = merge(root->left, root->right);
        delete root;
        return ret;
    }
    if( root->key < key) root->setRight(erase(root->right, key));
    else root->setLeft(erase(root->left, key));
    return root;
}

template <typename T>
TreapNode<T> * kth(TreapNode<T> * root, T k){
    if(root==nullptr) return nullptr;
    int leftsize = 0;
    if(root->left != nullptr) leftsize = root->left->size;
    if(leftsize >= k) return kth(root->left, k);
    if(leftsize +1 == k) return root;
    else return kth(root->right, k - leftsize - 1);
}

template <typename T>
void printTreap(TreapNode<T> * h){
    if(h->left) printTreap(h->left);
    cout<<h->key<<" ";
    if(h->right) printTreap(h->right);
}

void solve(){
    int N,a,b;
    cin>>N>>a>>b;
    RNG rng(1983, a, b);
    
    TreapNode<int> * root = nullptr;
    int ret = 0;
    while(N--){
        int nxt = rng.next();
#ifdef DEBUG_LOOP
        cout<<"nxt : "<<nxt<<" ";
#endif
        root = insert<int>(root, new TreapNode<int>(nxt));
#ifdef DEBUG_LOOP
        cout<<"root->size : "<<root->size<<" ";
#endif
#ifdef DEBUG_TREAP
        printTreap<int>(root);
#endif
        auto median = kth<int>(root, (root->size+1)/2)->key;
#ifdef DEBUG_LOOP
        cout<<"median : "<<median<<endl;
#endif
        ret = (ret + median) % MOD;
    }
    cout<<ret<<endl;
    delete root;
}

int main(){
    int C;
    cin>>C;
    while(C--) solve();
    return 0;
}