#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void printQueue(queue<int> q)
{
	//printing content of queue 
	while (!q.empty()){
		cout<<" "<<q.front();
		q.pop();
	}
	cout<<endl;
}

int main(int argc, char * argv[]){
	queue<int> q;
	queue<int> Q[18];
	
	
	q.push(1); q.push(2);
	Q[1] = q; //deep copy
	
	cout<<"print out q"<<endl;
	printQueue(q);
	
	cout<<"print out Q[1]"<<endl;
	printQueue(Q[1]);
	q.pop();
	
		cout<<"print out q"<<endl;
	printQueue(q);
	cout<<"print out Q[1]"<<endl;
	printQueue(Q[1]);
	
	Q[1].pop();
		
		cout<<"print out q"<<endl;
	printQueue(q);
	cout<<"print out Q[1]"<<endl;
	printQueue(Q[1]);
	
	if (Q[2].empty())
		cout<<"Q[2] is empty"<<endl;
	int posi = 0;
	if ( Q[posi+2].empty() )
		cout<<"Q[2] is empty"<<endl;
	return 0;
}