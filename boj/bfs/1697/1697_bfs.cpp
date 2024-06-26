#include <iostream>
#include <queue>

using namespace std;

struct Node{
public:
	int _height;
	int _x;
	Node(const int & height, const int & x):
	_height(height),
	_x(x){};
};

queue<Node *> Queue_NodePosi;

int main(){
	//input 
	int N,K;
	cin>>N>>K;
	
	//trivial case
	if(N==K){
		cout<<0<<endl;
		return 0;
	}
	bool VISIT[100001] = {false};
	
	//solve
	Node * NodePosi;
	int height = 0;
	int x = N;
	Queue_NodePosi.push(new Node(height, x));
	VISIT[x] = true;
	while(!Queue_NodePosi.empty()){
		NodePosi = Queue_NodePosi.front();
		height = NodePosi->_height;
		x = NodePosi->_x;
		Queue_NodePosi.pop();
		delete NodePosi;
		if(x-1 == K || x+1 == K || 2*x == K) {
			height++;
			break;
		}
		// x-1
		if( 0<= x-1 && !VISIT[x-1]){
			Queue_NodePosi.push(new Node(height+1, x-1));
			VISIT[x-1] = true;
		} 
		
		// x+1
		if( x+1<=100000 && !VISIT[x+1]){
			Queue_NodePosi.push(new Node(height+1, x+1));
			VISIT[x+1] = true;
		} 
		// 2*x
		if( 2*x <= 100000 && !VISIT[2*x]){
			Queue_NodePosi.push(new Node(height+1, 2*x));
			VISIT[2*x] = true;
		}
	}
	
	while(!Queue_NodePosi.empty()){
		Queue_NodePosi.pop();
	}
	
	//output
	cout<<height<<endl;
	return 0;
}