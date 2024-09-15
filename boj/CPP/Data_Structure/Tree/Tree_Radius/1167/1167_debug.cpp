#include <iostream>
#include <vector>
#include <stack>

// #define DEBUG_TREE
// #define DEBUG_DFS

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


void printList(Node * NodePosi){
	while(NodePosi != nullptr){
		cout<<NodePosi->_index<<" "<<NodePosi->_dist<<" ";
		NodePosi = NodePosi->_next;
	}
	cout<<endl;
};

void printRoute(stack<Node *> route){
	while(!route.empty()){
		cout<<route.top()->_index<<" ";
		route.pop();
	}
	cout<<endl;
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
	int radius = -1;
	vector<bool> VISIT(V+1, false); // initializing with false values
	
	//initial start
	stack<Node *> route;
	route.push(Graph[1]);

	Node * n_NodePosi = route.top()->_next;
	VISIT[1] = true;
	int distance = 0;
	int start_index = 0;
	while(!route.empty()){
		// jump
		while(n_NodePosi != nullptr && VISIT[n_NodePosi->_index]){
			n_NodePosi = n_NodePosi->_next;
		}

		// check if the node is of 1 degree (excluding the connected nodes that are included in route)
		if(n_NodePosi == nullptr){
			// if so -> compare the distance, and pop -> next loop
			n_NodePosi = route.top();
			if( distance > radius){
				radius = distance;
				start_index = n_NodePosi->_index;
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
			#ifdef DEBUG_DFS
				cout<<"Current route"<<endl;
				printRoute(route);
				cout<<"Distance : "<<distance<<endl;
			#endif
	}

   	// Reset VISIT array for the next iteration
	fill(VISIT.begin(), VISIT.end(), false);
	
	//FIND RADIUS
	
	while(!route.empty()){
		route.pop();
	}
	
	// cout<<"start index : "<<start_index<<endl;
	
	route.push(Graph[start_index]);
	VISIT[start_index] = true;

	n_NodePosi = route.top()->_next;
	radius = -1;
	distance = 0;
	while(!route.empty()){
		while(n_NodePosi != nullptr && VISIT[n_NodePosi->_index]){
			n_NodePosi = n_NodePosi -> _next;
		}
		
		if (n_NodePosi == nullptr){
			radius = max(radius, distance);
			n_NodePosi = route.top();
			distance -= n_NodePosi->_dist;
			route.pop();
		} else {
			distance += n_NodePosi->_dist;
			route.push(n_NodePosi);
			VISIT[n_NodePosi->_index] = true;
			n_NodePosi = Graph[n_NodePosi->_index]->_next;
		}
			#ifdef DEBUG_DFS
				cout<<"Current route"<<endl;
				printRoute(route);
				cout<<"Distance : "<<distance<<endl;
			#endif
	}
	
	cout<<radius;
	
	// deallocate dynamic memories	
	for(int i = 0 ; i < V+1 ; i++){
		Node* NodePosi = Graph[i];
		if(NodePosi == nullptr) continue;
		Node * CurrentNodePosi;
		while(NodePosi != nullptr){
			CurrentNodePosi = NodePosi;
			NodePosi = NodePosi->_next;
			delete CurrentNodePosi;
		}
	}
	
	return 0;
}