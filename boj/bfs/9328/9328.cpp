//bfs

#include <iostream>
#include <queue>
#include <iomanip>

// #define DEBUG_INPUT
// #define DEBUG_DFS
#define MAX_H 105
#define VISITED 90
#define OPENEDAFTER 91
using namespace std;


int h,w;
bool keys[26] = {false};
int MAP[MAX_H][MAX_H] = {0};
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

struct Node{
public:
    int x;
    int y;
    Node( const int _x, const int _y):
        x(_x),
        y(_y){}
};

void printMAP(){
	cout<<endl;
	for(int i = 0 ; i <= h+3; i++){
		for(int j = 0; j<= w+3; j++){
			if(3 <=MAP[i][j] && MAP[i][j] <= 28) cout<<setw(3)<<(char) (MAP[i][j] + 'A' - 3);
			else if ( 29 <= MAP[i][j] && MAP[i][j] <= 54) cout<<setw(3)<<(char) (MAP[i][j] + 'a' -29);
			else if (MAP[i][j] == 2) cout<<setw(3)<<"$";
			else cout<<setw(3)<<MAP[i][j];
		}
		cout<<endl;
	}
}

void printKeys(){
	for(int i = 0 ; i <26; i++){
		if(keys[i]){
			cout<<(char) (i + 'a')<<" ";
		}
	}
	cout<<endl;
}

void printDoors(vector<Node> d []){
	for(int i = 0; i < 26; i++){
		if(d[i].empty()) continue;
		else {
			cout<<(char)(i + 'A')<<" : ";
			for(auto node : d[i]){
				cout<<"("<<node.x<<","<<node.y<<") ";
			}
			cout<<endl;
		}
	}
}

void solve(){
    cin>>h>>w;
    char c;
    vector<Node> doors[26];
    for(int i = 0; i <= h+3 ; i++){
        for(int j = 0; j <= w + 3; j++){
            if( i == 0 || i == h+3 || j == 0 || j == w+3) {
                MAP[i][j] = 1; // surround by walls
            } else if ( i == 1 || i == h+2 || j == 1 || j == w+2){
                MAP[i][j] = 0;
            } else {
                cin>>c;
                if( c == '*') MAP[i][j] = 1; // walls
                else if ( c == '$') MAP[i][j] = 2; // documents
                else if ( 'A' <= c && c <= 'Z') {
                    MAP[i][j] = c - 'A' + 3; // doors
					doors[c -'A'].push_back(Node(i,j));
                }else if ( 'a' <= c && c <= 'z') {
                    MAP[i][j] = c - 'a' + 29; // keys
                } else { // empty, do nothing
					MAP[i][j] = 0;
				} 
			}
        }
    }

    string key;
    cin>>key;
	if(key != "0")
    for(int i = 0; i < key.length() ; i++){
        keys[key[i] - 'a'] = true;
		//unlock doors
		for(int j = 0; j < doors[ key[i] - 'a'].size(); j++){
			int _x = doors[ key[i] - 'a'][j].x;
			int _y = doors[ key[i] - 'a'][j].y;
			MAP[_x][_y] = 0;
		}
    }
#ifdef DEBUG_INPUT
printMAP();
printDoors(doors);
#endif
	
    // bfs
    // how to find keys?
    int res = 0;
    queue<Node> q;
    q.push(Node(1,1));
    MAP[1][1] = 1;

    while(!q.empty()){
#ifdef DEBUG_DFS
printMAP();
#endif
        int x = q.front().x; int y = q.front().y;
#ifdef DEBUG_DFS
cout<<"x,y : "<<x<<","<<y<<endl;	
#endif
		q.pop();
        for(int i = 0 ; i < 4; i++){
            if( MAP[x + dx[i]][y + dy[i]] == 2){
                // documents
                res++;
                q.push(Node( x + dx[i], y + dy[i]));
				MAP[x + dx[i]][y + dy[i]] = 1;
            } else if ( MAP[x + dx[i]][y + dy[i]] == 0){
                // empty
                q.push(Node( x + dx[i], y + dy[i]));
				MAP[x + dx[i]][y + dy[i]] = 1;
            } else if ( 3 <= MAP[x + dx[i]][y + dy[i]] && MAP[x + dx[i]][y + dy[i]] <= 28){
                //doors
				MAP[ x + dx[i]][y + dy[i]] = VISITED; // mark it as a door that has been visited but couldn't open
            }  else if( 29 <= MAP[x + dx[i]][y + dy[i]] && MAP[x + dx[i]][y + dy[i]] <= 54){
				
				//keys
				if(keys[MAP[x + dx[i]][y + dy[i]] - 29] == false){
					
					keys[MAP[x + dx[i]][y + dy[i]] - 29] = true;
					// push unlocked doors into queue
					for(int j = 0; j < doors[ MAP[x + dx[i]][y + dy[i]] - 29].size(); j++){
						int _x = doors[ MAP[x + dx[i]][y + dy[i]] - 29][j].x;
						int _y = doors[ MAP[x + dx[i]][y + dy[i]] - 29][j].y;
						if( MAP[_x][_y] == VISITED){
							q.push(Node(_x,_y));
							MAP[_x][_y] = OPENEDAFTER;
						} else if( MAP[_x][_y] != OPENEDAFTER){
							MAP[_x][_y] = 0;
						}
					}
				}
				q.push(Node(x+dx[i], y+dy[i]));
				MAP[x + dx[i]][y + dy[i]] = 1;
#ifdef DEBUG_DFS
printKeys();
#endif
			} else {
                //1 or OPENEDAFTER -> walls, do nothing
            }
            
        }
    }
    
    cout<<res<<endl;
    
	//reset
    for(int i = 0; i < 26; i++){
        keys[i] = false;
    }
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}