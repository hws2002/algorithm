#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

// #define DEBUG_MAP
// #define DEBUG_DESTROY_WALL
// #define DEBUG_GSD
// #define DEBUG_VISIT


int N,M;

#define IS_TARGET_PLACE(x,y,t_x,t_y) ( (x) == (t_x) && (y) == (t_y) )

struct Node{
public:
	int _distance;
	int _x;
	int _y; 
	Node(const int & distance, const int & x, const int & y):
		_distance(distance),
		_x(x),
		_y(y)
		{};
};

#ifdef DEBUG_GSD
void printQueue_NodePosi(queue<Node *> Queue_NodePosi){
	cout<<"Current Queue : ";
	Node * current_node;
	while(!Queue_NodePosi.empty()){
		current_node = Queue_NodePosi.front();
		cout<<"("<<current_node->_x<<","<<current_node->_y<<")"<<" ";
		Queue_NodePosi.pop();
	}
	cout<<endl;
}
#endif
/*
given MAP, find a shortest distance from (1,1) to (N,M)
*/
int getShortestDistance( bool ** VISIT){
	#ifdef DEBUG_VISIT
		cout<<"VISIT LOOKS LIKE..."<<endl;
		for(int i = 0 ; i <= N+1; i++){
			for(int j = 0; j <= M+1; j++){
				cout<<VISIT[i][j];
			}
			cout<<endl;
		}
	#endif
	//todo
	int distance = 1;
	int current_x = 1;
	int current_y = 1;
	bool arrived = false;
	queue<Node * > Queue_NodePosi;
	Node * current_node = new Node(distance,current_x,current_y);
	Node * next_node;
	Queue_NodePosi.push(current_node);
	VISIT[1][1] = true;
	while(!Queue_NodePosi.empty()){
		#ifdef DEBUG_GSD
			printQueue_NodePosi(Queue_NodePosi);
		#endif

		current_node = Queue_NodePosi.front();
		Queue_NodePosi.pop();
		distance = current_node->_distance;
		current_x = current_node->_x;
		current_y = current_node->_y;
		if(current_node != nullptr) delete current_node;
		#ifdef DEBUG_GSD
			cout<<"current_node : ("<<current_x<<","<<current_y<<") | distance :"<<distance<<endl;
		#endif
		// right
		if(!VISIT[current_x][current_y+1]){

			if(IS_TARGET_PLACE(current_x,current_y+1,N,M)){
				distance++;
				arrived = true;
				#ifdef DEBUG_GSD
					cout<<"distance : "<<distance;
				#endif
				break;
			}
				#ifdef DEBUG_GSD
					cout<<"pushing ("<<current_x<<","<<current_y+1<<") ";
				#endif
			next_node = new Node(distance+1,current_x,current_y+1);
			Queue_NodePosi.push(next_node);
			VISIT[current_x][current_y+1] = true;
		}
		
		// bottom
		if(!VISIT[current_x+1][current_y]){
			if(IS_TARGET_PLACE(current_x+1,current_y,N,M)){
				distance++;
				arrived = true;
				#ifdef DEBUG_GSD
					cout<<"distance : "<<distance<<endl;
				#endif
				break;
			}
				#ifdef DEBUG_GSD
					cout<<"pushing ("<<current_x+1<<","<<current_y<<") ";
				#endif
			next_node = new Node(distance+1,current_x+1,current_y);
			Queue_NodePosi.push(next_node);
			VISIT[current_x+1][current_y] = true;
		}

		// left
		if(!VISIT[current_x][current_y-1]){
			// if(IS_TARGET_PLACE(current_x,current_y-1,N,M)){
				// return distnace+1;
			// }
				#ifdef DEBUG_GSD
					cout<<"pushing ("<<current_x<<","<<current_y-1<<") ";
				#endif
			next_node = new Node(distance+1,current_x,current_y-1);
			Queue_NodePosi.push(next_node);
			VISIT[current_x][current_y-1] = true;
		}
		
		// top
		if(!VISIT[current_x-1][current_y]){
			// if(IS_TARGET_PLACE(current_x,current_y-1,N,M)){
				// return distnace+1;
			// }
				#ifdef DEBUG_GSD
					cout<<"pushing ("<<current_x-1<<","<<current_y<<") ";
				#endif
			next_node = new Node(distance+1,current_x-1,current_y);
			Queue_NodePosi.push(next_node);
			VISIT[current_x-1][current_y] = true;
		}
		#ifdef DEBUG_GSD
			cout<<"probing ended"<<endl;
		#endif
	}
	return arrived ? distance : 1001*1001 + 1;
}

int main(int argc, char * argv[]){
	//input
	cin>>N>>M;
	// cout<<N<<M;
	bool ** MAP;
	bool ** VISIT;

	MAP = new bool * [N+2];
	VISIT = new bool * [N+2];

	for(int i = 0 ; i <= N+1; i++){
		MAP[i] = new bool[M+2];
		VISIT[i] = new bool[M+2];
		MAP[i][0] = 1; MAP[i][M+1] = 1;
		VISIT[i][0] = 1; VISIT[i][M+1] = 1;
	}
	std::fill(MAP[0],MAP[0]+M+2,true);
	std::fill(MAP[N+1],MAP[N+1]+M+2,true);
	std::fill(VISIT[0],VISIT[0]+M+2,true);
	std::fill(VISIT[N+1],VISIT[N+1]+M+2,true);

	queue<int> Queue_Ones;
	char num;
	for(int i = 1 ; i <= N; i++){
		for(int j = 1; j <= M; j++){
			cin>>num;
			MAP[i][j] = num - '0';
			VISIT[i][j] = num - '0';
			if(MAP[i][j] == 1){
				Queue_Ones.push(i*1001 + j);
			}
		}
	}
	
	//trivial case
	if(N==1 && M==1) {cout<<1<<endl; return 0;}

	#ifdef DEBUG_MAP
		for(int i = 0 ; i <= N+1; i++){
			for(int j = 0; j <= M+1; j++){
				cout<<MAP[i][j];
			}
			cout<<endl;
		}
	#endif
	
	//solve
	int res = 1001*1001 + 1;
	res = min( res, getShortestDistance( VISIT ) );
	// restore visit
	for(int i = 0; i < N+2; i++){
		for(int j = 0; j < M+2; j++){
			VISIT[i][j] = MAP[i][j];
		}
	}

	int destroy_x = 0;
	int destroy_y = 0;
	while( !Queue_Ones.empty()){
		destroy_x = Queue_Ones.front();
		Queue_Ones.pop();
		destroy_y = destroy_x%1001;
		destroy_x /= 1001;
		// if all directions are blocked, destroying it has no effect
		// => skip it
		

		if(VISIT[destroy_x - 1][destroy_y] 
		   && VISIT[destroy_x][destroy_y+1] 
		   && VISIT[destroy_x+1][destroy_y] 
		   && VISIT[destroy_x][destroy_y-1]) continue;
		#ifdef DEBUG_DESTROY_WALL
			cout<<"position of wall to be destroyed : ("<<destroy_x<<","<<destroy_y<<")"<<endl;
		#endif
		VISIT[destroy_x][destroy_y] = 0;
		res = min( res, getShortestDistance( VISIT ) );
		
		// restore visit
		for(int i = 0; i < N+2; i++){
			for(int j = 0; j < M+2; j++){
				VISIT[i][j] = MAP[i][j];
			}
		}
	}

	//delete dynamic arrays
	for(int i = 0 ; i < M+2 ; i++){
		delete [] MAP[i];
		delete [] VISIT[i];
	}
	delete [] MAP;
	delete [] VISIT;
	
	//output
	if(res == 1001*1001 + 1) cout<<-1<<endl;
	else cout<<res<<endl;
	return 0;
}