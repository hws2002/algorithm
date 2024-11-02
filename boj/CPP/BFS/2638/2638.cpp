//bfs

/*
penetrable : 0
cheese : 1
impenetrable : 2

한번 penetrable이 된 칸은 다시 impenetrable이 될 수 없다.

*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

// #define DEBUG_SIMUL
using namespace std;

int N,M;
int MAP[102][102] = {0};
int T = 0;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

struct Node{
public:
    int x;
    int y;
    Node( const int _x, const int _y):
        x(_x),
        y(_y){};
};

queue<Node> PenetrableSeeds;
vector<Node> Cheeses;

//find impenetrable areas (separate) - dfs
void findImpe(){
    
    while(!PenetrableSeeds.empty()){
        int x = PenetrableSeeds.front().x;
        int y = PenetrableSeeds.front().y;
        PenetrableSeeds.pop();
        for(int i = 0 ; i < 4; i++){
            if(MAP[x + dx[i]][y + dy[i]] == 2){
                PenetrableSeeds.push(Node(x+dx[i], y + dy[i]));
                MAP[x + dx[i]][y + dy[i]] = 0;
            }
        }
    }
}

void removeCheese(){
	vector<Node> toRemove;
    for(int i = Cheeses.size()-1 ; i >= 0 ; i--){
        int x = Cheeses[i].x; int y = Cheeses[i].y;
        int cnt = 0;
        for(int j = 0 ; j < 4; j++){
            if(MAP[x + dx[j]][y + dy[j]] == 0){
                cnt++;
            }
        }
        if(cnt >= 2){
            //remove
            PenetrableSeeds.push(Node(x,y));
            Cheeses.erase(Cheeses.begin() + i);
            toRemove.push_back(Node(x,y));
        }
    }
	
	for(auto toremove : toRemove){
		MAP[toremove.x][toremove.y] = 0;
	}
}

void simulate(){
    while(++T){

        findImpe();
#ifdef DEBUG_SIMUL
cout<<"after finding impenetrable"<<endl;
for(int i = 1 ; i <= N; i++){
	for(int j = 1 ; j <= M; j++){
		cout<<MAP[i][j]<<" ";		
	}
	cout<<endl;
}

#endif
        removeCheese();
#ifdef DEBUG_SIMUL
cout<<"after removing cheeses"<<endl;
for(int i = 1 ; i <= N; i++){
	for(int j = 1 ; j <= M; j++){
		cout<<MAP[i][j]<<" ";		
	}
	cout<<endl;
}
cout<<endl;
#endif
        if(Cheeses.empty()) break;
    }
}

int main(){
    //pre
    cin>>N>>M;
    for(int i = 1 ; i <= N; i++){
        std::fill(MAP[i], MAP[i] + M+1, 2);
    }
    int temp;
    for(int i = 1; i <= N ; i++){
        for(int j = 1; j <= M; j++){
            cin>>temp;
            if(temp) {
                MAP[i][j] = 1;
                Cheeses.push_back(Node(i,j));
            }
        }
    }
    
    //pre - 
    PenetrableSeeds.push(Node(1,1));
	
    //simulate
    simulate();
    
    //output
    cout<<T<<endl;    
    return 0;
}