# 17 Oct 2023 - 1361. Validate Binary Tree Nodes

[Validate Binary Tree Nodes - LeetCode](https://leetcode.com/problems/validate-binary-tree-nodes/description/?envType=daily-question&envId=2023-10-17)

You have `n` binary tree nodes numbered from `0` to `n - 1` where node `i` has two children `leftChild[i]` and `rightChild[i]`, return `true` if and only if **all** the given nodes form **exactly one** valid binary tree.

If node `i` has no left child then `leftChild[i]` will equal `-1`, similarly for the right child.

Note that the nodes have no values and that we only use the node numbers in this problem.

**Example 1:**

![https://assets.leetcode.com/uploads/2019/08/23/1503_ex1.png](https://assets.leetcode.com/uploads/2019/08/23/1503_ex1.png)

```
Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
Output: true

```

**Example 2:**

![https://assets.leetcode.com/uploads/2019/08/23/1503_ex2.png](https://assets.leetcode.com/uploads/2019/08/23/1503_ex2.png)

```
Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,3,-1,-1]
Output: false

```

**Example 3:**

![https://assets.leetcode.com/uploads/2019/08/23/1503_ex3.png](https://assets.leetcode.com/uploads/2019/08/23/1503_ex3.png)

```
Input: n = 2, leftChild = [1,0], rightChild = [-1,-1]
Output: false

```

**Constraints:**

- `n == leftChild.length == rightChild.length`
- `1 <= n <= 10^4`
- `-1 <= leftChild[i], rightChild[i] <= n - 1`

---

## Intuition

맨처음에는 “有向连通图的树计数” 가 생각났다. 1학년 2학기 이산수학2 수업에서 基本关联矩阵，支撑树的数目에 관해 배우면서, “有向连通图的树计数”에 대해 배웠었는데,  基本关联矩阵만 있다면(B라고하자) det(BB^T)가 가능한 支撑数的数目이기때문에, 이 값이 1인지 아닌지만 알아보면 된다고 생각했었다. (자세한 내용은 reference 참고)

하지만 n이 10의 4승까지 되는 상황에서는 determinant 계산이 너무 오래걸려서 불가능하다고 판단되었다.

그렇게 다시 생각해보니, 그냥 binary tree를 만들면서, 만약 새로운 노드가 binary tree의 특징을 만족하지 못한다면, false를 리턴하면되지 않을까 라는 생각이 들었다. Binary tree의 구현에 관해서는, 2학년1학기 자료구조 수업때의 경험이 많이 도움이 되었다.(reference 참고)

문제에서 요구하는 것은 “all the given nodes form exactly one valid binary tree” 인지를 판단하는 것이다. 그러면,

1. 만들어진 tree중, parent가 없는 노드는 단 하나여야만 한다.(root 노드)
2. root노드를 제외한 다른 모든 노드들의 parent는 유일해야 한다.

이 두가지 요소를 가지고 판단하면 된다. 이말인 즉슨, 

예를들어 i번째 노드의 leftChild와 rightChild를 생성한다고 할때, 이미 그 leftChild혹은 rightChild가 생성되어있고, parent까지 존재한다면, 바로 알고리즘을 종료하고 false를 리턴하며,

만약 모든 Children을 생성한 후에 root node의 갯수가 1보다 크다면, false를, root node의 갯수가 1이라면 마침내 true를 리턴하면 된다.

<aside>
⚠️ 여기서 주의해야할 점은, leftChild나 rightChild를 생성한다고 할때, 이미 leftChild 혹은 rightChild가 생성되어있다고 바로 false를 리턴하는것이 아닌, parent의 존재 유무까지 파악해야한다. 그렇지 않으면 다음과같은 true상황에도 false를 리턴하는 경우가 생긴다.

```cpp
n = 4
leftChild = [3,-1,1,-1]
rightChild = [-1,-1,0,-1]
```

</aside>

## Approach

구체적인 구현에 있어서는, 간단한 방식과 복잡한 방식 2가지방식이 생각났다.

먼저 복잡한 방식은 `BinNode` 와 `BinTree` 두 구조체를 모두 구현해서 하는 방식이고,

간단한 방식은 `BinNode` 만 구현해서 하는 방식이다. 

시간이된다면 `BinTree` 까지 구현하겠지만, 귀찮아서 간단한 방식으로 구현해보았다.

우선 `BinNode` 구조체의 구현은 다음과 같다.

### BinNode

```cpp
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
    //Constructor
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
```

각 노드들은 _parent, _lc, _rc를 가지고 있으며, data로는 그 노드의 index를 지니고 있다.

이것만으로도 알고리즘을 짤 순 있지만, 생성하려는 Child가 이미 다른 parent를 두고있는지 빠르게 확인하기위해서는, 각 노드들의 위치를 저장하는 array (혹은 벡터)를 maintain하면 더 효율 적일 것이다. (이는 list는 생성과 삭제가 빠르지만 탐색이 느리고, vector는 생성과 삭제가 느리지만 탐색이 빠른 특징을 활용한것이다.)

마지막으로 root node의 갯수를 track하는 변수또한 필요하다. 

- Code1
    
    ```cpp
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
        std::vector<BinNodePosi> parent_address;
        std::vector<BinNodePosi> node_address;
    
        // Solution() : parent_address(10000, nullptr) {} // Initialize the vector in the constructor
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
                        num_root--;
                    }
                    node_address[leftChild[i]] = root->insertAsLc(leftChild[i]);
                    // parent_address[leftChild[i]] = root;
                }
    
                if(rightChild[i] != -1){
                    if(node_address[rightChild[i]]!=nullptr) {
                        BinNodePosi rc = node_address[rightChild[i]];
                        if(rc->_parent != nullptr) return false;
                        num_root--;
                    }
                    node_address[rightChild[i]] = root->insertAsRc(rightChild[i]);
                    // parent_address[rightChild[i]] = root;
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
    ```
    

그렇게 위와 같이 코드를 짜봤는데, 예상하지 못한 case가 있었다.

![testcase 40 failed](17%20Oct%202023%20-%201361%20Validate%20Binary%20Tree%20Nodes%2038f22bf7fff54f60ad7ff65c066dbefc/Untitled.png)

testcase 40 failed

i번째 노드의 leftChild와 rightChild를 생성한다고 할때, 이미 그 leftChild혹은 rightChild가 생성되어있고, parent까지 존재하지 않아도, 만약 그 노드가 i번째 노드가 위치하고 있는 Tree의 root 노드라면, 똑같이 false를 리턴해야했다.

그렇게 수정한 코드로는 다음과같은 결과를 얻었다

- Code2
    
    ```cpp
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
    ```
    

![result - Accepted!](17%20Oct%202023%20-%201361%20Validate%20Binary%20Tree%20Nodes%2038f22bf7fff54f60ad7ff65c066dbefc/Untitled%201.png)

result - Accepted!

메모리면에서 살짝 아쉬운데, `node_address`를 벡터가 아닌 set형식으로 유지시키면 메모리를 줄일수 있겠지만, 그만큼 시간면에서 희생해야 한다.

## Reference

[3.3 支撑树的计数](https://www.notion.so/3-3-21ecb1c719df4df78dbee7ebaffe2553?pvs=21) 

[1. Implementation](https://www.notion.so/1-Implementation-6ce5ca8d6ff74fc9b4417849e01a9409?pvs=21)