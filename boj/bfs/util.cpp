

#include <iostream>

using namespace std;

template <typename T>
void printQueue(queue<T> Queue_T){
	T current_node;
	while(!Queue_T.empty()){
		current_node = Queue_T.front();
		cout<<current_node;
		Queue_T.pop();
	}
	cout<<endl;
}
