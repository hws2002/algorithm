// 19:59 ~ 
// dp - buttomup

// 1 : 빈칸
// 0 : 벽
#include <iostream>
#include <algorithm>

#define NUM_STATE 3
#define DEBUG_CALC
using namespace std;

typedef enum {
    HORI, // horizontal
    VERT, // vertical
    DIAG // diagonal
} State;



int N;
bool MAP[18][18] = {false};
int routes[NUM_STATE][18*18 + 18] = {0};

void printRoutes(State state){
	cout<<"printing out routes ends with "<<state<<" state : "<<endl;
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= N; j++)
			cout<<routes[state][i*18 + j]<<" ";
		cout<<endl;
	}	
}

void calcRoutes(State state, int posi){
    int x = posi / 18; int y = posi % 18;
    int numRoutes = routes[state][posi];
    if(state == HORI){
        // -→
        if(MAP[x][y+1]){
            routes[HORI][posi + 1] += numRoutes;
            calcRoutes(HORI, posi+1);
            //↘
            if( MAP[x+1][y] && MAP[x+1][y+1]){
                routes[DIAG][posi + 19] += numRoutes;
                calcRoutes(DIAG, posi+19);
            }
        } 
        return ;
    } else if (state == VERT){
        //↓
        if(MAP[x+1][y]){
            routes[VERT][posi + 18] += numRoutes;
            calcRoutes(VERT, posi + 18);
            //↘
            if( MAP[x][y+1] && MAP[x+1][y+1]){
                routes[DIAG][posi + 19] += numRoutes;
                calcRoutes(DIAG, posi + 19);
            }
        }
        return;
    } else {
        // -→
        if(MAP[x][y+1]){
            routes[HORI][posi + 1] += numRoutes;
            calcRoutes(HORI, posi+1);
        } 
        //↓
        if( MAP[x+1][y]){
            routes[VERT][posi + 18] += numRoutes;
            calcRoutes(VERT, posi+18);
        }
        //↘
        if(MAP[x][y+1] && MAP[x+1][y] && MAP[x+1][y+1]){
            routes[DIAG][posi + 19] += numRoutes;
            calcRoutes(DIAG, posi + 19);
        }
        return ;
    }
}


int main(){
    
    cin>>N;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin>>MAP[i][j];
            MAP[i][j] = !MAP[i][j];
        }
    }
    
    //solve - dfs
    
    //caculate number of routes
    routes[HORI][1*18 + 2] = 1;
    calcRoutes(HORI, 1* 18 + 2);
#ifdef DEBUG_CALC
printRoutes(HORI);
printRoutes(VERT);
printRoutes(DIAG);
#endif
    cout<<routes[HORI][N*18 + N] + routes[VERT][N*18 + N] + routes[DIAG][N*18 + N]<<endl;
    return 0;
}