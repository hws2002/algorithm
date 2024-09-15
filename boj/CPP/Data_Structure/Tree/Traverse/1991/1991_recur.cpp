#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

struct TreeNode{
public:
    TreeNode* _parent;
    TreeNode* _left;
    TreeNode* _right;
    int _value;
    
    TreeNode(int value, TreeNode * parent, TreeNode * left, TreeNode * right){
        _value = value + 'A';
        _parent = parent;
        _left = left;
        _right = right;
    }
    
    void travPre(){
        printf("%c", _value);
        if(_left) _left->travPre();
        if(_right) _right->travPre();
    };
    
    void travIn(){
        if(_left) _left->travIn();
        printf("%c", _value);
        if(_right) _right->travIn();
    };
    void travPost(){
        if(_left) _left->travPost();
        if(_right) _right->travPost();
        printf("%c", _value);
    };
};

class Tree{
public:
    //size는 pass
    TreeNode * _root;
    
    Tree(){
        _root = new TreeNode(0, nullptr, nullptr, nullptr);
    };
    
    // ~Tree() {
    //     if(_root != nullptr) remove(_root);
    // }
    
    TreeNode * insert(char value){
        _root = new TreeNode(value, nullptr, nullptr, nullptr);
        return _root;
    }
    
    TreeNode * insert(int value, TreeNode * parent){
        TreeNode * left = new TreeNode(value, parent, nullptr, nullptr);
        parent->_left = left;
        return left;
    }
    
    TreeNode * insert(TreeNode * parent, int value){
        TreeNode * right = new TreeNode(value, parent, nullptr, nullptr);
        parent->_right = right;
        return right;
    }
    
    // void remove(TreeNode * posi){
    //     remove(_root->_left);
    //     remove(_root->_right);
    //     delete _root;
    // }    
    
    void travPre(){
        printf("%c",_root->_value);
        if(_root->_left) _root->_left->travPre();
        if(_root->_right)_root->_right->travPre();
    };
    
    void travIn(){
        if(_root->_left)_root->_left->travIn();
        printf("%c",_root->_value);
        if(_root->_right)_root->_right->travIn();
    };
    
    void travPost(){
        if(_root->_left)_root->_left->travPost();
        if(_root->_right)_root->_right->travPost();
        printf("%c",_root->_value);
    };
};

int main(){
    int N;
    Tree bintree = Tree();
    vector< TreeNode * > TreeNodePosis(26, nullptr);
    TreeNodePosis[0] = bintree._root;
    // case test - pass
    // printf("%c\n",bintree._root->_value);
    // bintree.insert('B' - 'A', bintree._root);
    // bintree.insert(bintree._root, 'C' - 'A');
    
    cin>>N;
    char c_parent, c_left, c_right;
    int parent, left, right;
    while(N--){
        cin>>c_parent>>c_left>>c_right;
        parent = c_parent - 'A';
        left = c_left - 'A';
        right = c_right - 'A';
        // printf("%d %d %d \n",parent,left,right);
        TreeNode * parentTree = TreeNodePosis[parent];
        if(parentTree == nullptr) {
            parentTree = new TreeNode(parent, nullptr, nullptr, nullptr);
            TreeNodePosis[parent] = parentTree;
            cout<<"parentTree created"<<endl;
        }
        
        if(left != -19){ //not '.'
            TreeNode * leftTree = TreeNodePosis[left];
            if(leftTree == nullptr) {
                leftTree = new TreeNode(left, parentTree, nullptr, nullptr);
                parentTree->_left = leftTree;
                TreeNodePosis[left] = leftTree;
            } else {
                parentTree->_left = leftTree;
                leftTree->_parent = parentTree;
            }
        }
        
        if(right != -19){ //not '.'
            TreeNode * rightTree = TreeNodePosis[right];
            if(rightTree == nullptr){
                rightTree = new TreeNode(right, parentTree, nullptr, nullptr);
                parentTree->_right = rightTree;
                TreeNodePosis[right] = rightTree;
            } else {
                parentTree ->_right = rightTree;
                rightTree->_parent = parentTree;
            }
        }
        // cout<<"iteration end"<<endl;
    }
    
    //traverse
    bintree.travPre();
    cout<<endl;
    bintree.travIn();
    cout<<endl;
    bintree.travPost();
    cout<<endl;
    return 0;
}