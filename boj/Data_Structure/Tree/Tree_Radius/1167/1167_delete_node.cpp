#include <iostream>
#include <vector>
#include <stack>

// #define DEBUG_TREE
// #define DEBUG_DFS
// #define DEBUG_DELETE

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

void deleteVertex(vector<Node *> & graph, int index){
	#ifdef DEBUG_TREE
		for(int i = 1; i <= 5; i++){
			if (graph[i] == nullptr) continue;
			cout<<"printing out graph["<<i<<"]"<<endl;
			printList(graph[i]);
		}
	#endif
	
	#ifdef DEBUG_DELETE
		cout<<"Deleting "<<index<<" from graph!"<<endl;
	#endif
	
	Node * NodePosi = graph[index];
	// Node * delete_NodePosi;
	while(NodePosi != nullptr){
		// delete_NodePosi = NodePosi;
		NodePosi = NodePosi->_next;
		// delete delete_NodePosi;
		// delete_NodePosi = nullptr;
		if(NodePosi == nullptr) break;
		int h_Index = NodePosi->_index;
		Node * h_NodePosi = graph[h_Index]; 
		Node * prev_NodePosi;
		
		while(h_NodePosi != nullptr && h_NodePosi->_index != index){ //index = 4
			prev_NodePosi = h_NodePosi;
			h_NodePosi = h_NodePosi->_next;
		}
		
		prev_NodePosi->_next = h_NodePosi ->_next;
		delete h_NodePosi;
		if(graph[h_Index]->_next == nullptr || graph[h_Index]->_next->_next == nullptr){
			deleteVertex(graph, h_Index);
		}
	}
	#ifdef DEBUG_DELETE
		cout<<"Deleted "<<index<<" from graph!"<<endl;
	#endif
	
}

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
	
	//DFS
	int radius = -1;
	vector<bool> VISIT(V+1, false); // initializing with false values
	for(iter = Latent_Start.begin(); iter != Latent_Start.end(); iter++)
	{
		//initial start
		stack<Node *> route;
		route.push(Graph[*iter]);
		// stack<Node *> last_NodePosi;
		
		Node * c_NodePosi;
		Node * n_NodePosi = route.top()->_next;
		VISIT[*iter] = true;
		int distance = 0;
		while(!route.empty()){
			
			// jump
			while(n_NodePosi != nullptr && VISIT[n_NodePosi->_index]){ // we have to check "index", not "NodePosi"
				n_NodePosi = n_NodePosi->_next;
			}
			
			// check if the node is of 1 degree (excluding the connected nodes that are inlucded in route)
			if(n_NodePosi == nullptr){
				// if so -> compare the distance, and pop				
				radius = max(radius, distance);
				n_NodePosi = route.top();
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
				#endif
		}
		
       // Reset VISIT array for the next iteration
        fill(VISIT.begin(), VISIT.end(), false);
		
		// Delete Node *iter from Graph
		// after deleting node, if there exists any node that has just become 1 degree, we can delete that Node
		// but it can go recursively => recursive function
		
		// delete vertex `*iter` from Graph
		deleteVertex(Graph, *iter);
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

