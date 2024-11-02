// bst insert 구현
#include <iostream>

// #define DEBUG_BST

typedef int KeyType;
typedef long long ll;

using namespace std;

ll res = 1;
struct Node{
public:
    Node* parent;
    Node* left;
    Node* right;
    KeyType key;
    ll height;
    
    Node(Node * _parent, Node * _left, Node* _right, const KeyType & _key, const ll & _height):
        parent(_parent),
        left(_left),
        right(_right),
        key(_key),
        height(_height){};
    void insert(const KeyType & _key, const ll & _height){
        if(_key < key){
            if(left){
                left->insert(_key, _height + 1);
            } else {
                left = new Node(this, nullptr, nullptr, _key,_height+1);
                res += _height + 1;
            }
        } else {
            if(right){
                right->insert(_key, _height + 1);
            } else {
                right = new Node(this, nullptr, nullptr, _key, _height + 1);
                res += _height + 1;
            }
        }
    };
    
    void travPre(){
        cout<<key<<endl;
        if(left) left->travPre();
        if(right) right->travPre();
    }
    void travIn(){
        if(left) left->travIn();
        cout<<key<<endl;
        if(right) right->travIn();
    }
};

class BST{
public:
  Node * root;
  
  BST(const KeyType & _key){
      root = new Node(nullptr, nullptr, nullptr, _key, 1);
  };
  
  ~BST(){};
  void insert(KeyType _key){
    KeyType key = root->key;
    if( _key < key){
        if(root->left){
            root->left->insert(_key,root->height+1);
        } else {
            root->left = new Node(root, nullptr, nullptr, _key, root->height+1);
            res += root->height + 1;
        }
    } else {
        if(root->right){
            root->right->insert(_key, root->height + 1);
        } else {
            root->right = new Node(root, nullptr, nullptr, _key, root->height + 1);    
            res += root->height + 1;
        }
    }
  }
  
  void travPre(){
    cout<<"traverse bst (prefix)"<<endl;
    cout<<root->key<<endl;
    if(root->left) root->left->travPre();
    if(root->right) root->right->travPre();
  }
  
   void travIn(){
    cout<<"traverse bst (infix)"<<endl;
    if(root->left) root->left->travIn();
    cout<<root->key<<endl;
    if(root->right) root->right->travIn();
  }
};

int N;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N;
    int p;
    cin>>p;
    BST bst = BST(p);
    for(int i = 0; i < N-1; i++){
        cin>>p;
        bst.insert(p);
    }
    
#ifdef DEBUG_BST
// this should print out 1~N in ascending order
bst.travIn();
#endif

    //output
    cout<<res<<endl;
    return 0;
}
