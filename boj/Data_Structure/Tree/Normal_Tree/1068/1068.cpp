#include <iostream>
#include <vector>

// #define DEBUG_TREE
using namespace std;

struct Node{
public:
    Node * parent;
    vector<Node *> children;
    bool isLeaf;
    int numLeaf;
    
    //constructor
    Node( Node * _parent, const bool isleaf, const int numleaf):
        parent(_parent),
        isLeaf(isleaf),
        numLeaf(numleaf){};
    
    //
    void insertChild(Node * child){
        children.push_back(child);
    }
    
    //
    void updateNumLeaf(){
        Node * _parent = parent;
        while(_parent){
            _parent->isLeaf = false;
            _parent->numLeaf = 0;
            for(auto child : _parent->children){
                _parent->numLeaf += child->numLeaf;
            }
            _parent = _parent->parent;
        }
    }
};

vector<Node *> NodePosis;
int N; // 1<= N <= 50

int main(){
    cin>>N;
    NodePosis = vector<Node *> (N, nullptr);
    int p;
    
    for(int i = 0 ; i < N; i++){
        cin>>p;
        if(p == -1){
            //root
            if(NodePosis[i] == nullptr){
                NodePosis[i] = new Node(nullptr, true, 1);
            }
        } else {
            
            if(NodePosis[p] == nullptr){
                NodePosis[p] = new Node(nullptr, true, 1);
            }
            
            if(NodePosis[i] == nullptr){
                NodePosis[i] = new Node(NodePosis[p], true,1);
            }
            
            NodePosis[i]->parent = NodePosis[p]; // 이줄이 빠지면 위의 tescase를 통과하지 못한다.
            NodePosis[p]->insertChild(NodePosis[i]);
            NodePosis[i]->updateNumLeaf();
        }
    }
    
#ifdef DEBUG_TREE
for(auto Node : NodePosis){
    cout<<"printing out children of Node : "<<Node<<endl;
    for(auto child : Node->children){
        cout<<child<<" ";
    }
    cout<<endl;
    cout<<"numLeaf of subtree whose root is Node : "<<Node->numLeaf<<endl;
}
#endif

    int to_remove;
    cin>>to_remove;
    
    int res = 0;
    for(int i = 0 ; i < N; i++){

        if(NodePosis[i] && NodePosis[i]->parent == nullptr){

            res += NodePosis[i]->numLeaf;
        }
    }
    
    Node * toRemoveNode = NodePosis[to_remove];
    res -= toRemoveNode->numLeaf;
    if(toRemoveNode->parent && toRemoveNode->parent->children.size() == 1){
        res += 1;
    }
    cout<<res<<endl;
    return 0;
}