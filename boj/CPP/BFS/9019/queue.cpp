#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int main(int argc, char * argv []){
	vector<queue<int> > Queues;
	queue<int> queue;
	queue.push(12);
	Queues.push_back(queue);
	cout<<"queue.front() : "<<queue.front()<<endl;
	cout<<"Queues[0].front : "<<Queues[0].front()<<endl;
	queue.pop();
	if(Queues[0].empty()){
		cout<<"Queues[0] is empty!"<<endl;
	} else {
		cout<<"Queues[0] is not empty!"<<endl;
		cout<<"Queues[0].front : "<<Queues[0].front()<<endl;
	}
	return 0;
}