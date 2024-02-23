#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Node{

public:
	int _index;
	int _dist;
	Node* _next;
	Node(int index, int dist = 0) : 
		_index(index), 
		_dist(dist),
		_next(nullptr)
		{};
};
//if _dist = 0 => head node

int find_Radius_Tree_DFS(vector<Node *> Graph, int V, int start_index, int& next_start_index){
	int radius = -1;
	vector<bool> VISIT(V+1, false); // initializing with false values
	
	//initial start
	stack<Node *> route;
	route.push(Graph[start_index]);

	Node * n_NodePosi = route.top()->_next;
	VISIT[start_index] = true;
	int distance = 0;
	while(!route.empty()){
		// jump
		while(n_NodePosi != nullptr && VISIT[n_NodePosi->_index]){ // we have to check "index", not "NodePosi"
			n_NodePosi = n_NodePosi->_next;
		}

		// check if the node is of 1 degree (excluding the connected nodes that are inlucded in route)
		if(n_NodePosi == nullptr){
			// if so -> compare the distance, and pop				
			n_NodePosi = route.top();
			if( distance > radius){
				radius = distance;
				next_start_index = n_NodePosi->_index;
			}
			distance -= n_NodePosi->_dist;
			route.pop();
		} else {
			// if not -> push into the stack 
			distance += n_NodePosi->_dist;
			route.push(n_NodePosi);
			VISIT[n_NodePosi->_index] = true;
			n_NodePosi = Graph[n_NodePosi->_index]->_next;
		}
	}
	
	return radius;
}

int main(int argc, char* argv[]){	
	//input
	int V;
	cin>>V;

	vector<int>::iterator iter;
	// initialize Graph
	vector<Node *> Graph(V+1);
	for (int i = 0; i < V; i++){
		int count = 0;
		int i_node;
		cin>>i_node;
		
		// initialize head Node
		Node * head = new Node(i_node);
		Graph[i_node] = head;
		int dist, next_node = 0;
		while(next_node != -1){
			cin>>next_node;
			if(next_node != -1) {
				cin >> dist;
				count++;
				// insert into list
				head->_next = new Node(next_node, dist);
				head = head->_next;
			}
		}
	}
	
	//DFS
	int next_start_index = -1;
	
	//FIND start_index
	find_Radius_Tree_DFS(Graph, V, 1, next_start_index);
	
	//FIND RADIUS
	int radius = find_Radius_Tree_DFS(Graph, V, next_start_index, next_start_index);
	
	cout<<radius;
	
	// deallocate dynamic memories	
	for(int i = 0 ; i < V+1 ; i++){
		Node* NodePosi = Graph[i];
		Node * CurrentNodePosi;
		while(NodePosi != nullptr){
			CurrentNodePosi = NodePosi;
			NodePosi = NodePosi->_next;
			delete CurrentNodePosi;
		}
	}
	
	return 0;
}

