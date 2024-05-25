// start : 12:44

// 1 : connected
// 0 : disconnected

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>

// #define DEBUG_BFS
using namespace std;

struct Node {
public:
    int _x;
    int _y;
    // int _h;
    Node(const int x , const int y){
        _x = x;
        _y = y;
        // _h = h;
    }
};


vector<Node> startPoints;
vector<int> res;
int N;
int MAP[27][27] = {0};
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

#ifdef DEBUG_BFS
void printMAP(){
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= N; j++){
			cout<<MAP[i][j]<<" ";
		}
		cout<<endl;
	}
}
#endif 

void bfs(){

    for(int i = 0 ; i < startPoints.size(); i++){
        int x = startPoints[i]._x;
        int y = startPoints[i]._y;
        if(MAP[x][y] == 0) continue;
#ifdef DEBUG_BFS
cout<<"bfs with "<<num<<"th street, x,y : "<<x<<","<<y<<endl;
#endif
		queue<Node> q;
        q.push(Node(x,y));
		MAP[x][y] = 0;
        int num = 1;
		while(!q.empty()){
            x = q.front()._x;
            y = q.front()._y;
            q.pop();
            for(int j = 0 ; j < 4; j++){
                if(MAP[x + dx[j]][y + dy[j]]){
                    q.push(Node(x + dx[j], y + dy[j]));
                    MAP[x + dx[j]][y + dy[j]] = 0;
					num++;
                }
            }
		}
		
        res.push_back(num);
#ifdef DEBUG_BFS
cout<<"ends bfs, number of houses in this street : "<<res.back()<<endl;
printMAP();
#endif
    }
}

int main(){
    cin>>N;
    string row;
    for(int i = 1; i <= N; i++){
        cin>>row;
        for(int j = 1 ; j <= N; j++){
            MAP[i][j] = row[j-1]-'0';
            if(MAP[i][j] == 1 && MAP[i-1][j] != 1 && MAP[i][j-1] != 1){
                startPoints.push_back( Node(i,j) );
            }
        }
    }
    
    //bfs
    bfs();
    
    //output
    cout<<res.size()<<endl;
    std::sort(res.begin(), res.end());
    for(auto item : res){
        cout<<item<<endl;
    }
    return 0;    
}