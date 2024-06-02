// SIMULATION

#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

#define MAX_RC 52
#define GOING2PURIFIER(x, y, a, b) ( (x==a) && (y==b)) 
#define DEBUG_SIMUL
using namespace std;

struct Purifier{
public:
    int r1;
    int r2;
    
    Purifier(const int _r1, const int _r2):
        r1(_r1),
        r2(_r2){};
    
};

struct Dust{
public:
    int r;
    int c;
    int val;
    Dust(const int _r, const int _c, const int _val):
        r(_r),
        c(_c),
        val(_val){};
};

Purifier purifier(0,0);
int R,C,T;
int MAP[MAX_RC][MAX_RC] = {0};
int dr[4] = {1,-1,0,0};
int dc[4] = {0,0,1,-1};
vector<Dust> prevDusts;
vector<Dust> nextDustsPosis;
vector<bool> inNextDusts( MAX_RC*MAX_RC + MAX_RC , false);

void moveDust(const int r, const int c, const int val, const int dr, const int dc){
    if( GOING2PURIFIER(r + dr, c + dc, purifier.r1, 1) || GOING2PURIFIER(r + dr, c + dc, purifier.r2, 1) ){
        return ;
    } else {
        MAP[r + dr][c + dc] += val; 
        if(inNextDusts[ (r + dr) * MAX_RC + c + dc ] == false){
            nextDustsPosis.push_back(Dust(r + dr, c + dc, -1));
            inNextDusts[ (r + dr) * MAX_RC + c + dc ] = true;
        }
    }
}

void spread_moveDust(const int r, const int c, const int val){
    
    if( ( c == C && r <= purifier.r1 && r != 1) || ( c == 1 && r > purifier.r2 ) ){
        moveDust(r, c, val , -1, 0);
    } else if ( (c == C && r >= purifier.r2 && r != R) || (c == 1 && r < purifier.r1) ){
        moveDust(r, c, val , 1, 0);
    } else if ( (r == 1 && c != 1 ) || ( r == R && c != 1) ){
        moveDust(r, c, val , 0, -1);
    } else if ( (r == purifier.r1 || r == purifier.r2)) {
        moveDust(r, c, val , 0, 1);
    } else {
        moveDust(r, c, val , 0, 0);
    }
    
    MAP[r][c] -= val;
}

void simulate(){
    while(T--){
        inNextDusts = vector<bool>( MAX_RC*MAX_RC + MAX_RC , false);
        
        //spread dust and run air purifier
		int cnt = 0;
        for(auto dust : prevDusts){    
            if(cnt++ > 0) break;
			for(int i = 0 ; i < 4; i++){
                if(MAP[dust.r + dr[i]][dust.c + dc[i]] > -1 && dust.val/5 > 0){
                    // spreaded dust and purifier move dust
                    spread_moveDust(dust.r + dr[i], dust.c + dc[i], dust.val/5);
                    dust.val -= dust.val/5;
                }
            }
            
            // original dust
            spread_moveDust(dust.r, dust.c, dust.val);
        }
        
        
        prevDusts.clear();
        // organize nextDust
        for(auto nextDustPosi : nextDustsPosis){
            prevDusts.push_back( Dust(nextDustPosi.r, nextDustPosi.c, MAP[nextDustPosi.r][nextDustPosi.c]));
        }
        nextDustsPosis.clear();
#ifdef DEBUG_SIMUL
cout<<endl;
for(int i = 1; i <= R; i++){
	for(int j = 1; j <= C; j++){
		cout<<MAP[i][j]<<" ";
	}
	cout<<endl;
}
#endif
    }
}

int main(){
    //pre
    for(int i = 0 ; i < MAX_RC; i++){
        std::fill(MAP[i], MAP[i] + MAX_RC, -2);
    }
    cin>>R>>C>>T;
    
    for(int i = 1 ; i <= R; i++){
        for(int j = 1; j <= C; j++){
            cin>>MAP[i][j];
            if(MAP[i][j] == -1){
                if(purifier.r1 == 0){
                    purifier.r1 = i;
                    purifier.r2 = i+1;
                }
            } else if(MAP[i][j]){
                prevDusts.push_back( Dust( i, j, MAP[i][j]) );
            }
        }
    }
    
    //simulation
    simulate();
    
    int res = 0;
    for(auto dust : prevDusts){
        res += dust.val;
    }
    
    cout<<res<<endl;
    return 0;    
}