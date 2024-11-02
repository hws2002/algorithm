//bfs

#include <iostream>
#include <queue>

using namespace std;

int M,N;
int MAP[1002][1002] = {0};


int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};
int remainingTomato = 0;

struct Node{
public:
    const int _x;
    const int _y;
    const int _height;
    Node(const int & x, const int & y, const int & height):
        _x(x),
        _y(y),
        _height(height){};
};

queue<Node> Ripen;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M;
    for(int i = 1 ; i <= M; i++){
        for(int j = 1; j <= N; j++){
            cin>>MAP[i][j];
            if(MAP[i][j] == 1) 
                Ripen.push( Node(i,j,0));
            else if (MAP[i][j] == 0) remainingTomato++;
        }
    }
    
    //trivial case
    // if(remainingTomato == 0) { cout<<0<<endl; return 0;}
    
    //pre
    std::fill(MAP[0], MAP[0] + N+2, -1);
    std::fill(MAP[M+1], MAP[M+1] + N+2, -1);
    for(int row = 1; row <= M; row++){
        MAP[row][0] = -1;
        MAP[row][N+1] = -1;
    }
	
    //bfs
    int x,y;
    int height = 0;
    while(!Ripen.empty()){
        x =  Ripen.front()._x; y = Ripen.front()._y; height = Ripen.front()._height;
        Ripen.pop();
        for(int i = 0 ; i < 4; i++){
            if(MAP[x + dx[i]][y + dy[i]] == 0){
                Ripen.push( Node(x + dx[i], y + dy[i], height+1));
                MAP[x + dx[i]][y + dy[i]] = 1;
                remainingTomato--;
            }
        }
    }

    // output
    if(remainingTomato <= 0) 
    cout<<height<<endl;
    else cout<<-1<<endl;
    return 0;
}