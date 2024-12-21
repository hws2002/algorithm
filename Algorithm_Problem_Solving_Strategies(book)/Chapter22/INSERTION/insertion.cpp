#include <iostream>
#include <vector>

#define endl '\n'

using namespace std;

int N;

template <typename T>
struct TreapNode{
	T key;
	int priority, size;
	TreapNode<T> *left, *right;
	TreapNode<T>(const T & k) : key(k), priority(rand()), size(1), left(nullptr), right(nullptr){};
	
	void setLeft(TreapNode<T> * l) {left = l; calcSize();}
	void setRight(TreapNode<T> * r) {right = r; calcSize();}
	
	void calcSize(){
		size = 1;
		if(left) size += left->size;
		if(right) size += right->size;
	}
};

// typedef pair<TreapNode *, TreapNode *> NodePair;

// NodePair split()

template <typename T>
TreapNode<T> * insert(TreapNode<T> * root,  TreapNode<T> * node){
	if(root->nullptr) return node;
	if(root->priority < node->priority){
		auto lr = split(root, node->key);
		
	} else {
		if( root->key < node->key){
			
		} else {
			
		}
	}
}
	
void solve(){
	cin>>N;
	vector<int> nums(N);
	for(int i = 0; i < N; i++){
		cin>>nums[i];
	}
	
	
	vector<int> res(N);
	for(int i = nums.size() -1; i>=0; i--){
		cout<<"hello"<<endl;
	}
	
	for(int i = res.size() - 1; i>= 0; i--)
		cout<<res[i]<<" ";
	cout<<endl;
}

int main(){
	int C;
	cin>>C;
	while(C--)solve();
	return 0;
}