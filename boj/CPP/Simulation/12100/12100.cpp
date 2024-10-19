#include <iostream>
#include <vector>
#include <cmath>

#define all(v) v.begin(), v.end()
#define FOR(i,s,e) for(int i = s; i < e; i++)
#define MAX_N 20

// #define DEBUG_DFS
// #define DEBUG_MOVE
using namespace std;
typedef long long ll;


int N;
int MAP[MAX_N][MAX_N] = {0};
int res = 0;

int maxMap(int (&map)[MAX_N][MAX_N]){
    int ret = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            ret = max(ret, map[i][j]);
        }
    }
    return ret;
}

void dfs(int (&map)[MAX_N][MAX_N], int depth, string path){
#ifdef DEBUG_DFS
    printf("dfs with depth, path : %d, ", depth);
	cout<<path<<endl;
for(int i = 0 ; i < N; i++){
	for(int j =0 ; j < N; j++){
		cout<<map[i][j]<<" ";
	}
	cout<<endl;
}
#endif
	
    if( depth >= 5) {
        res = max(res, maxMap(map));
		// printf("end dfs \n");
        return;
    }
    
    // printf("%p \n", &map); 
    // printf("%p \n", &original_map);
    for(int i = 0; i < 4; i++){
        vector<int> arr;
        int new_map[MAX_N][MAX_N] = {0};
		for(int j = 0; j < N; j++){
			for(int k = 0; k < N; k++)
				new_map[j][k] = 0;
		}
        if(i == 0) { //up
            for(int c = 0; c < N; c++){
                // runner
                arr.clear();
                for(int r = 0; r < N; r++){
                    if(map[r][c])
                        arr.push_back(map[r][c]);
                }
                if (arr.empty()) continue;
                
                int slow = 0; int fast = 0;
                while( fast+1 < arr.size()){
                    if( arr[fast] == arr[fast+1]){
                        new_map[slow][c] = arr[fast]+1;
                        fast+=2; 
                    } else {
                        new_map[slow][c] = arr[fast];
                        fast+=1;
                    }
                    slow+=1;
                }
				if( fast < arr.size())
                	new_map[slow][c] = arr[fast];
            }
				path+=string("u");
        } else if( i==1) { //right
            for(int r = 0; r < N; r++){
                arr.clear();
                for(int c = N-1; c>=0; c--){
                    if(map[r][c])
                        arr.push_back(map[r][c]);
                }
                
                if (arr.empty()) continue;
                int slow = 0; int fast = 0;
                while( fast + 1 < arr.size()){
                    if( arr[fast] == arr[fast+1]){
                        new_map[r][N-1-slow] = arr[fast]+1;
                        fast += 2;
                    } else {
                        new_map[r][N-1-slow] = arr[fast];
                        fast+=1;
                    }
                    slow+=1;
                }
				if( fast < arr.size())
                	new_map[r][N-1-slow] = arr[fast];
            }
			path+=string("->");

        } else if( i==2) { //down
            for(int c = 0; c < N; c++){
                arr.clear();
                for(int r = N-1; r >= 0; r--){
                    if(map[r][c]) arr.push_back(map[r][c]);
                }
                
                if (arr.empty()) continue;
                int slow = 0; int fast = 0;
                while( fast + 1 < arr.size()){
                    if( arr[fast] == arr[fast+1]){
                        new_map[N-1-slow][c] = arr[fast]+1;
                        fast+=2;
                    } else {
                        new_map[N-1-slow][c] = arr[fast];
                        fast+=1;
                    }
                    slow+=1;
                }
				if( fast < arr.size())
                	new_map[N-1-slow][c] = arr[fast];
            }
			path+=string("d");
        } else { //left
            for(int r = 0; r < N; r++){
                arr.clear();
                for(int c = 0; c < N; c++){
                    if(map[r][c]) arr.push_back(map[r][c]);
                }
                if (arr.empty()) continue;
                int slow = 0; int fast = 0;
                while (fast + 1 < arr.size()){
                    if(arr[fast] == arr[fast+1]){
                        new_map[r][slow] = arr[fast]+1;
                        fast += 2;
                    } else {
                        new_map[r][slow] = arr[fast];
                        fast += 1;
                    }
                    slow+= 1;
                }
				if( fast < arr.size())
					new_map[r][slow] = arr[fast];
	        }
			path+=string("<-");
        }
#ifdef DEBUG_MOVE

printf("new_map when i = %d : \n", i);
for(int j = 0 ; j < N; j++){
    for(int k = 0 ; k < N; k++){
        cout<<new_map[j][k]<<" ";
    }
    cout<<endl;
}
#endif
        dfs(new_map, depth+1,path);
		path.pop_back();
		if(i == 1 || i == 3) path.pop_back();
    }
}

int main(){
    cin>>N;
    FOR(i,0,N){
        FOR(j,0,N){
            cin>>MAP[i][j];
            if(MAP[i][j])
                MAP[i][j] = log2(MAP[i][j]);
        }
    }

    //dfs
    // printf("%p \n", &MAP);
    dfs(MAP,0, "");

    cout<<ll(1<<res)<<endl;
    return 0;
}