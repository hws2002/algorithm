#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
0 : X
1 : .
2 : *
3 : S
4 : D
*/

// #define DEBUG_INPUT
// #define DEBUG_EMPTY_FLOOD
// #define DEBUG_LOOK4

#define ADJACENT_2_TARGET(_x,_y,x,y) ( \
    ( (_x+1) == (x) && (_y) == (y) ) \
    || ( (_x) == (x) && (_y+1) == (y) ) \
    || ( (_x-1) == (x) && (_y) == (y) ) \
    || ( (_x) == (x) && (_y-1) == (y) ) \
)


struct Node{
public:
	int _time_spent;
	int _x, _y;
	Node(const int  & time_spent, const int & x, const int & y) :
		_time_spent(time_spent),
		_x(x),
		_y(y) {};
};

queue<Node *> Queue_S;
int MAP[52][52] = {0};
bool VISIT[52][52] = {false};
int D_x, D_y;
int S_x, S_y;
queue<int> Queue_flood;

void probe_S(int time_spent, const int & x, const int & y){
	if( !VISIT[x][y] && MAP[x][y] == 1 || MAP[x][y] == 4 ){
		Queue_S.push( new Node(time_spent + 1, x, y) );
		VISIT[x][y] = true;
	}
}

void look4neighborhoods(int ** map, const int & time_spent, const int & x, const int & y){	
	if(!VISIT[x][y] && map[x][y] == 1){
		Queue_S.push( new Node(time_spent+1, x, y));
		VISIT[x][y] = true;
	}
}

void expand(const int & x , const int & y){
	if(MAP[x][y] == 1){
		MAP[x][y] = 2;
		Queue_flood.push(x*51 + y);
#ifdef DEBUG_EMPTY_FLOOD
	cout<<"pushed ("<<x<<","<<y<<")"<<endl;
#endif
	}
}

int main(){
	//input
	int R,C;
	cin>>R>>C;
	char _c;

	for(int i  = 1 ; i <= R; i++){
		for(int j  = 1 ; j <= C; j++){
			cin>>_c;
			switch (_c) {
				case '.':
					MAP[i][j] = 1;	
					break;
				case '*':
					MAP[i][j] = 2;
					Queue_flood.push(i*51 + j);
					break;

				case 'S':
					MAP[i][j] = 1;
					S_x = i; S_y = j;
					break;

				case 'D':
					MAP[i][j] = 4;
					D_x = i; D_y = j;
					break;
				default:
					break;
			}
		}
	}
	
#ifdef DEBUG_INPUT
	cout<<"MAP : "<<endl;
	for(int i = 0; i <= R+1 ;i++){
		for(int j = 0; j <= C + 1; j++){
			cout<<MAP[i][j];
		}
		cout<<endl;
	}
	cout<<"S : ("<<S_x<<","<<S_y<<")"<<endl;
#endif
	
	int res = -1;
	int time_spent = 0;

	if( Queue_flood.empty()){
		//solve 
		Node * S;
		S = new Node(time_spent,S_x,S_y);
		Queue_S.push(S);
		VISIT[S_x][S_y] = true;
		int count = 0;
		while(!Queue_S.empty()){
count++;
			S = Queue_S.front();
			Queue_S.pop();
			time_spent = S->_time_spent;
			S_x = S->_x; S_y = S->_y;
#ifdef DEBUG_EMPTY_FLOOD
	cout<<"current S : ("<<S_x<<","<<S_y<<")"<<" ("<<count<<")"<<endl;	
#endif
			if( (S_x == D_x) && (S_y == D_y) ){
				res = time_spent;
				break;
			}
			probe_S(time_spent, S_x,S_y+1);
			probe_S(time_spent, S_x,S_y-1);
			probe_S(time_spent, S_x+1,S_y);
			probe_S(time_spent, S_x-1,S_y);
		}
		if(res > 0) cout<<res<<endl;
		else cout<<"KAKTUS"<<endl;
		return 0;
	} else {
		// if Queue_flood is not empty
		int res = -1;
		// STEP1 : 
		vector<int **> Vector_Map_Aftertsec; vector<int **>::iterator iter;

		int ** new_map = new int * [R+2];
		for(int i = 0 ; i < R + 2; i++){
			new_map[i] = new int [C+2];
			for(int j = 0; j < C + 2; j++){
				new_map[i][j] = MAP[i][j];
			}
		}
		Vector_Map_Aftertsec.push_back(new_map);
		
		
		int flood, flood_x, flood_y;
		while( !Queue_flood.empty() ){
			int count = Queue_flood.size();
			
			//expand
// #ifdef DEBUG_EMPTY_FLOOD
// 			cout<<"size of Queue : "<<q_size<<endl;
// #endif
			while( count-- > 0){
				flood = Queue_flood.front();
				Queue_flood.pop();
				flood_x = flood / 51; flood_y = flood % 51;
#ifdef DEBUG_EMPTY_FLOOD
	cout<<"(flood_x, flood_y) : ("<<flood_x<<","<<flood_y<<")"<<endl;
#endif
				expand(flood_x,flood_y+1);
				expand(flood_x,flood_y-1);
				expand(flood_x+1,flood_y);
				expand(flood_x-1,flood_y);
				
				new_map = new int * [R+2];
				for(int i = 0; i < R+2 ; i++){
					new_map[i] = new int[C+2];
					for(int j = 0 ; j < C+2; j++){
						new_map[i][j] = MAP[i][j];
					}
				}
			}
			Vector_Map_Aftertsec.push_back(new_map);
		}

#ifdef DEBUG_EMPTY_FLOOD
int _count = 0;
for(iter = Vector_Map_Aftertsec.begin(); iter != Vector_Map_Aftertsec.end(); iter++){
	cout<<"Vector_Map_Aftertsec["<<_count++<<"] : "<<endl;
	new_map = *iter;
	for(int i = 0 ; i < R+2; i++){
		for(int j = 0 ; j < C + 2 ; j++){
			cout<<new_map[i][j];
		}		
		cout<<endl;
	}
	cout<<endl;
}
#endif
		
		//solve
		Node * S;
		S = new Node(time_spent,S_x,S_y);
		Queue_S.push(S);	
		VISIT[S_x][S_y] = true;
		int v_size = Vector_Map_Aftertsec.size();
		while(!Queue_S.empty()){
			S = Queue_S.front();
			time_spent = S->_time_spent;
			S_x = S->_x; S_y = S->_y;
			Queue_S.pop();
			delete S;
#ifdef DEBUG_LOOK4
	cout<<"time_spent, S_x, S_y : "<<time_spent<<","<< S_x<<","<<S_y<<endl;
#endif
			//if current S is adjacent to D, print out time_spent+1 and terminate
			if ( ADJACENT_2_TARGET(S_x,S_y,D_x,D_y) ) {
				res = time_spent+1;
				break;
			}
			
			//if not, look for 4 neighborhoods
			if( time_spent >= v_size-1){
				look4neighborhoods(Vector_Map_Aftertsec[v_size-1],time_spent,S_x,S_y+1);
				look4neighborhoods(Vector_Map_Aftertsec[v_size-1],time_spent,S_x,S_y-1);
				look4neighborhoods(Vector_Map_Aftertsec[v_size-1],time_spent,S_x+1,S_y);
				look4neighborhoods(Vector_Map_Aftertsec[v_size-1],time_spent,S_x-1,S_y);
			} else {
				look4neighborhoods(Vector_Map_Aftertsec[time_spent+1],time_spent,S_x,S_y+1);
				look4neighborhoods(Vector_Map_Aftertsec[time_spent+1],time_spent,S_x,S_y-1);
				look4neighborhoods(Vector_Map_Aftertsec[time_spent+1],time_spent,S_x+1,S_y);
				look4neighborhoods(Vector_Map_Aftertsec[time_spent+1],time_spent,S_x-1,S_y);
			}
		}
		
		if(res > 0) cout<<res<<endl;
		else cout<<"KAKTUS"<<endl;
		
		//delete allocated memories

		for(iter = Vector_Map_Aftertsec.begin(); iter != Vector_Map_Aftertsec.end(); iter++){
			new_map = *iter;
			for(int  i = 0 ; i < R+2; i++){
				delete[] new_map[i];
			}
			delete [] new_map;
		}
		
		return 0;
	}
	
	return 0;
}