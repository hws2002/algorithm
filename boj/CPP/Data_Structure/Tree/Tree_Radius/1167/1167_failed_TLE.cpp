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

int main(){
	vector<int> Latent_Start;

	// input 2 <= V <= 100,000
	int V;
	cin>>V;  
	
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
	
	//DFS with vertexes within Latent_Start
	vector<int>::iterator iter;
	int radius = -1;
	
	for(iter = Latent_Start.begin(); iter != Latent_Start.end(); iter++){
		#ifdef DEBUG_DFS
			cout<<"Staring vertex : "<<*iter<<endl;
		#endif
		// every time initiate new `visit` 1d array
		int * VISIT = new int[V+1]();
		// initiate 'route' stack
		stack<Node *> route;
		
		int distance = 0;
		int c_node_i = *iter; // current node index
		VISIT[c_node_i] = true;
		route.push(Graph[c_node_i]);		
			
		while(!route.empty()){
			Node * c_NodePosi = route.top();// current Nodeposi
			// !the Last element in `route` is head Node, whereas others are all child node
			c_node_i = c_NodePosi->_index; // current node index

			Node * n_NodePosi = Graph[c_node_i]->_next; // next NodePosi
			int n_node_i = n_NodePosi->_index; // next Node index
			
			// check if already visited
			// and check degree simultaneously
			if(VISIT[n_node_i]){
				bool did_pop = false;
				while(VISIT[n_node_i]){
					n_NodePosi = n_NodePosi ->_next;
					if(n_NodePosi == nullptr){
						// compare the distance, and pop out 1 element from stack
						// ! subtract corresponding value from `distance`
						radius = max(radius, distance);
						Node * pop_out_NodePosi = route.top();
						#ifdef DEBUG_DFS
							cout<<"pop_out_NodePosi->_index : "<<pop_out_NodePosi->_index<<endl;					
						#endif
						distance -= pop_out_NodePosi->_dist;
						route.pop();
						did_pop = true;
						break;
					} else {
						n_node_i = n_NodePosi ->_index;
					}
				}
				if(!did_pop){
					n_node_i = n_NodePosi -> _index;
					distance += n_NodePosi -> _dist;
					VISIT[n_node_i] = true;
					route.push(n_NodePosi);
					#ifdef DEBUG_DFS
						cout<<"Current route"<<endl;
						printRoute(route);
					#endif
				}
			} else	{
				n_node_i = n_NodePosi -> _index;
				distance += n_NodePosi -> _dist;
				VISIT[n_node_i] = true;
				route.push(n_NodePosi);
				#ifdef DEBUG_DFS
					cout<<"Current route"<<endl;
					printRoute(route);
				#endif
			}
		}
		delete[] VISIT;
	}
	
	#ifdef DEBUG_LATENT
		cout<<"LATENT START"<<endl;
		for(iter = Latent_Start.begin() ; iter != Latent_Start.end(); iter++){
			cout<<*iter<<" ";
		}
		cout<<endl;
	#endif
	
	// deallocate dynamic memories
	// for(int i = 0 ; i < V ; i++){
	// 	Node* NodePosi = Graph[i];
	// 	while(NodePosi != nullptr){
	// 		Node * CurrentNodePosi = NodePosi;
	// 		NodePosi = NodePosi->_next;
	// 		delete CurrentNodePosi;
	// 	}
	// }
	
	// output
	cout<<radius<<endl;
	return 0;
}



