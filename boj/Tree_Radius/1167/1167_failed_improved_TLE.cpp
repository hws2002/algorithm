#include <iostream>
#include <vector>
#include <stack>


// #define DEBUG_TREE
// #define DEBUG_LATENT
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

// void printList(Node * NodePosi){
// 	while(NodePosi != nullptr){
// 		cout<<NodePosi->_index<<" "<<NodePosi->_dist<<" ";
// 		NodePosi = NodePosi->_next;
// 	}
// 	cout<<endl;
// };

// void printRoute(stack<Node *> route){
// 	while(!route.empty()){
// 		cout<<route.top()->_index<<" ";
// 		route.pop();
// 	}
// 	cout<<endl;
// }


int main(int argc, char* argv[]){
	
	//input
	int V;
	cin>>V;
	vector<int> Latent_Start;
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
		if (count == 1) Latent_Start.push_back(i_node);
	}

	#ifdef DEBUG_TREE
		for(int i = 1; i <= V; i++){
			cout<<"printing out Graph["<<i<<"]"<<endl;
			printList(Graph[i]);
		}
	#endif
	
	#ifdef DEBUG_LATENT
		cout<<"LATENT START"<<endl;
		for(iter = Latent_Start.begin() ; iter != Latent_Start.end(); iter++){
			cout<<*iter<<" ";
		}
		cout<<endl;
	#endif
	
	//DFS
	int radius = -1;
	for(iter = Latent_Start.begin(); iter != Latent_Start.end(); iter++)
	{
		//initial start
		stack<Node *> route;
		
		route.push(Graph[*iter]);
		
		Node * c_NodePosi;
		Node * n_NodePosi;
		bool * VISIT = new bool [V+1](); // initializing with false values
		VISIT[*iter] = true;
		int distance = 0;
		while(!route.empty()){
			c_NodePosi = route.top();
			// c_NodeIndex = c_NodePosi ->_index;
			c_NodePosi = Graph[c_NodePosi->_index];
			n_NodePosi = c_NodePosi->_next;
			// n_NodeIndex = n_NodePosi->_index;
			// if(c_NodePosi->_index == 2) {
			// 	cout<<"n_NodePosi : "<<n_NodePosi<<endl;
			// 	cout<<"n_NodePosi->_index : "<<n_NodePosi->_index<<endl;
			// 	cout<<"VISIT[4] : "<<VISIT[4]<<endl;
			// }
				// jump
			while(n_NodePosi != nullptr && VISIT[n_NodePosi->_index]){ // we have to check "index", not "NodePosi"
				n_NodePosi = n_NodePosi->_next;
			}
			
			// check if the node is of 1 degree (excluding the connected nodes that are inlucded in route)
			if(n_NodePosi == nullptr){
				// if so -> compare the distance, and pop				
				radius = max(radius, distance);
				Node * last_NodePosi = route.top();
				distance -= last_NodePosi->_dist;
				route.pop();
				#ifdef DEBUG_DFS
					cout<<"Current route"<<endl;
					printRoute(route);
				#endif
			} else {
				//if not -> push into the stack 
				distance += n_NodePosi->_dist;
				route.push(n_NodePosi);
				VISIT[n_NodePosi->_index] = true;
				#ifdef DEBUG_DFS
					cout<<"Current route : ";
					printRoute(route);
					cout<<"Distance : "<<distance<<endl;
				#endif
			}
		}
		delete [] VISIT;
	}
	// deallocate dynamic memories
	
	for(int i = 0 ; i < V+1 ; i++){
		Node* NodePosi = Graph[i];
		while(NodePosi != nullptr){
			Node * CurrentNodePosi = NodePosi;
			NodePosi = NodePosi->_next;
			delete CurrentNodePosi;
		}
	}
	
	cout<<radius;
	return 0;
}

