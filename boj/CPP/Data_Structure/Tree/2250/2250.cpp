#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 10'001
#define endl '\n'
using namespace std;

int N;

struct TreeNode{
    int num, c;
    TreeNode * l;
    TreeNode * r;
    TreeNode(int num = -1, TreeNode * l = nullptr, TreeNode * r = nullptr):
        num(num),
        c(-1),
        l(l),
        r(r){};
};

vector<int> num2bi(MAX_N); // num2bi[num] : num번째 노드가 bfs에서의 발견된 순서
vector<int> num2in(MAX_N); // num2bi[num] : num번째 노드가 infix에서의 순서
vector<TreeNode *> tree;

void infix(TreeNode * h, int& idx){
    if (h == nullptr){
       return ; 
	}
	// printf("num : %d \n", h->num);
    infix(h->l, idx);
    h->c = idx++;
    infix(h->r, idx);
}

int main(){
    cin>>N;
    int p,l,r;
    vector<int> indegree(N,0);
    tree.resize(N,nullptr);
    
    // creat tree
    for(int i = 0; i < N; i++){
        cin>>p>>l>>r;
        p--;l--;r--;
        if(tree[p] == nullptr){
            tree[p] = new TreeNode(p);
        }
        TreeNode * lp, *rp;
		if(l >= 0){
			if(tree[l] == nullptr){
				lp = new TreeNode(l);
				tree[l] = lp;
			} else {
				lp = tree[l];
			}
			tree[p]->l = lp;
			indegree[l]++;
		}
		if(r >= 0){
			if(tree[r] == nullptr){
				rp = new TreeNode(r);
				tree[r] = rp;
			} else {
				rp = tree[r];
			}
			tree[p]->r = rp;
			indegree[r]++;
		}
    }
    
    // infix traverse
    // <=> set c of each nodes
    int root = 0;
    for (int i = 0 ; i < N; i++){
        if(indegree[i] == 0){
            root = i;
			// printf("root : %d \n",root);
			int idx = 0;
            infix(tree[i],idx);
            break;
        }
    }
// for(int i = 0;  i<N;i++){
// 	printf("num, c : %d, %d \n", tree[i]->num, tree[i]->c);
// }
    int ret_l = 0;
    int ret_w = 1;
    // bfs -> level traverse
    typedef pair<int,int> pii;
    queue<pii> q;
    int h = root; int level = 0;
    q.push({h,level});
    int level_s = h;
    int level_e = h;
    int prev_level = 0;
    while(!q.empty()){
        auto t = q.front(); q.pop();
        h = t.first; level = t.second;
        if( level != prev_level){
            if(ret_w < tree[level_e]->c - tree[level_s]->c + 1){
                ret_w = tree[level_e]->c - tree[level_s]->c + 1;
                ret_l = prev_level;
            }
            level_s = h;
        }
        prev_level = level;
        if(tree[h]->l){
            q.push({tree[h]->l->num, level+1});
        }
        if(tree[h]->r){
            q.push({tree[h]->r->num, level+1});
        }
        level_e = h;
    }

	if( ret_w < tree[level_e]-> c - tree[level_s]->c + 1){
		ret_w = tree[level_e]->c - tree[level_s]->c + 1;
		ret_l = prev_level;
	}
    cout<<ret_l+1<<" "<<ret_w<<endl;
    return 0;
}