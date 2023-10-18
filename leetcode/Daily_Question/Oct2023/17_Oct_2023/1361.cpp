#include <iostream>
using namespace std;

struct BinNode;
using BinNodePosi = BinNode *;

struct BinNode{
    BinNode* _parent, *_lc, *_rc;
    int _index;

    BinNodePosi insertAsLc(int e){
        return _lc = new BinNode(e,this);
    }
    BinNodePosi insertAsRc(int e){
        return _rc = new BinNode(e,this);
    }
    void attachAsLc(BinNodePosi posi){
        _lc = posi;
    }
    void attachAsRc(BinNodePosi posi){
        _rc = posi;
    }

public:
    //Constructer
    BinNode(int index){
        _index = index; _parent = nullptr; _lc = nullptr; _rc = nullptr;
    }

    BinNode(int index, BinNode * parent){
        _index = index;
        _parent = parent;
        _lc = nullptr;
        _rc = nullptr;
    }
    BinNode(int index, BinNode * lc, BinNode * rc){
        _index = index;
        _parent = nullptr;
        _lc = lc;
        _rc = rc;
    }
};


class Solution {
public:
    int num_root = 0;
    std::vector<BinNodePosi> node_address;
    Solution() : node_address(10000,nullptr){}
    bool buildBinTree(const int n,const vector<int> & leftChild,const vector<int> & rightChild){
        for(int i = 0; i < n; i++){
            BinNodePosi root;
            if( node_address[i] == nullptr){
                num_root++;
                node_address[i] = root = new BinNode(i);
            } else {
                root = node_address[i];
            }

            if(leftChild[i] != -1){
                if(node_address[leftChild[i]]!=nullptr) {
                    BinNodePosi lc = node_address[leftChild[i]];
                    if(lc->_parent != nullptr) return false;
                    else {
                        BinNodePosi parent = root;
                        while(parent->_parent != nullptr){
                            parent = parent->_parent;
                        }
                        if(leftChild[i] == parent->_index) return false;
                        root->attachAsLc(lc);
                        num_root--;
                    }
                }
                node_address[leftChild[i]] = root->insertAsLc(leftChild[i]);
            }

            if(rightChild[i] != -1){
                if(node_address[rightChild[i]]!=nullptr) {
                    BinNodePosi rc = node_address[rightChild[i]];
                    if(rc->_parent != nullptr) return false;
                    else {
                        BinNodePosi parent = root;
                        while(parent->_parent != nullptr) {parent = parent->_parent;
                        }
                        if(rightChild[i] == parent->_index) return false;
                        root->attachAsRc(rc);
                        num_root--;
                    }
                }
                node_address[rightChild[i]] = root->insertAsRc(rightChild[i]);
            }
        }
        return true;
    }
    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
        bool res = buildBinTree(n,leftChild,rightChild);
        if(res) return num_root == 1 ? true : false;
        else return false;
    }
};

int main(){
    
    return 0;
}