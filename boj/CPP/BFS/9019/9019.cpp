#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// #define DEBUG_DSLR

struct Node {
public:
	int _num; // number of node (not index!)
	int _op; // operation code (to get _num from previous num)
	Node * _parent;
	
	//constructor
	Node(const int num):
		_num(num),
		_op(-1),
		_parent(nullptr){};
	
	Node(const int num, const int op, Node * parent):
		_num(num),
		_op(op),
		_parent(parent){};
	
	//decontructor
    // ~Node() {
    //     // Deallocate memory for _parent if it's dynamically allocated
    //     if (_parent != nullptr) {
    //         delete _parent;
    //     }
    // }
};

char num2char(int num){
	if(num == 0)
		return 'D';
	else if (num == 1)
		return 'S';
	else if (num==2)
		return 'L';
	else 
		return 'R';
}

void print_num2char(int num){
	if(num == 0)
		cout<<"D";
	else if (num == 1)
		cout<<"S";
	else if (num==2)
		cout<<"L";
	else 
		cout<<"R";
}

int D(int num){
//operation 0
	num <<= 1;
	num %= 10000;
	return num;
}

int S(int num){
//operation 1
	num -=1;
	num %= 10000;
	if(num < 0) num += 10000;
	return num;
}

int L(int num){
//operation 2
	int leftmost = num / 1000;
	num *= 10;
	num += leftmost;
	num %= 10000;
	return num;
}

int R(int num){
//operation 3
	int rightmost = num % 10;
	num /= 10;
	num += (rightmost * 1000);
	return num;
}


void DSLR(int & A, const int & B){
	bool VISITED[10000] = {false};
	bool solved = false;
	queue<Node *> Queue_Node;
	Node * headPosi =  new Node(A);
	Queue_Node.push(headPosi);
	queue<Node *> Queue_to_delete;
	int count = 0;

	while(!solved && !Queue_Node.empty()){
		count++;
		headPosi = Queue_Node.front();
		A = headPosi ->_num;
		Queue_Node.pop();
		Queue_to_delete.push(headPosi);
		#ifdef DEBUG_DSLR
			cout<<"A :"<<A<<endl;
		#endif
		int next_num = -1;
		for(int op = 0 ; op < 4; op++){
			switch (op) {
				case 0:
					next_num = D(A);
					break;
				case 1:
					next_num = S(A);
					break;
				case 2:
					next_num = L(A);
					break;
				case 3:
					next_num = R(A);
					break;
				default:
					break;
			}
			#ifdef DEBUG_DSLR
				cout<<"next_num :"<<next_num<<endl;
			#endif
			if(next_num == B){
				// basecase(end)
				string res;
				res+=num2char(op);
				while(headPosi->_op != -1){
					res+=num2char(headPosi->_op);
					headPosi = headPosi->_parent;
				}
				//output reverse
				std::reverse( res.begin() , res.end() );
				cout<<res<<endl;
				solved = true;
				break;
			}
			
			if(!VISITED[next_num]){
				Node * childPosi = new Node(next_num, op, headPosi);
				Queue_Node.push(childPosi);
				VISITED[next_num] = true;
			}
		}
	}

	/* dealloc - delete all the Nodes in Queue_Node */
	while(!Queue_Node.empty()){
		headPosi = Queue_Node.front();
		Queue_Node.pop();
		if(headPosi != nullptr)
		delete headPosi;
	}
	
	while(!Queue_to_delete.empty()){
		headPosi = Queue_to_delete.front();
		Queue_to_delete.pop();
		if(headPosi != nullptr)
		delete headPosi;
	}
	
}

int main(int argc, char* argv []){
	int T;
	cin>>T;
	int A, B;
	for(int i = 0 ; i < T ; i++){
		cin>>A>>B;
		DSLR(A,B);
	}
	// output the result as we get input
	return 0;
}
