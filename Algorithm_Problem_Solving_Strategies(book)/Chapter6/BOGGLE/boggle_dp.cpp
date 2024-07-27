//https://www.algospot.com/judge/problem/read/BOGGLE
#include <iostream>
#include <cstring>

#define MAX_W 6
#define endl '\n'
// #define DEBUG_INPUT
// #define DEBUG_DP
using namespace std;

int dx[8] = {-1,-1,-1,0,0,1,1,1};
int dy[8] = {-1,0,1,-1,1,-1,0,1};

char MAP[MAX_W][MAX_W] = {" "};

int canfind[5][5][10] = {0};

// dp(x,y,s) : MAP[x][y] 부터 시작하여 s를 찾을 수 있는가?
bool dp(int x, int y, string s){

    // base
    if( s.length() <= 1 && MAP[x][y] == s[0] ) return true;
    if( MAP[x][y] != s[0]) return false;
    
    // MAP[x][y] == s[0] , s.length() >= 2
#ifdef DEBUG_DP
    printf("dp(%d,%d,%s) \n", x, y, s.c_str());    
#endif
	int & ret = canfind[x][y][s.length()-1];
    if(ret > -1) return ret;
    
    ret = 0;
    // try all directions
    for(int i = 0; i < 8; i++){
        if( !(0 <= x + dx[i] && x + dx[i] < 5 &&  0 <= y + dy[i] && y + dy[i] < 5) ) continue;
        if( dp(x + dx[i], y + dy[i], s.substr(1)) ){
#ifdef DEBUG_DP
    printf("dp(%d,%d,%s) \n", x + dx[i], y + dy[i], s.substr(1).c_str());  
#endif
			return ret = 1;
        }
    }
    
    return ret;
}

void solve(){
    
    //pre
    for(int i = 0; i < 5; i++){
        memset(MAP[i], ' ', MAX_W);
        MAP[i][MAX_W] = '\0';
    }
    
    
    for(int i = 0; i < 5; i++){
        string temp;
        cin>>temp;
        for(int j = 0 ; j < 5; j++){
            MAP[i][j] = temp[j];
        }
    }
#ifdef DEBUG_INPUT
for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
        cout<<MAP[i][j]<<" ";
    }
    cout<<endl;
}
#endif
    int N;
    cin>>N;
    string s;
    for(int i = 0; i < N; i++){
        cin>>s;
        //pre
        for(int j = 0; j < 5; j++){
            for(int k = 0 ; k < 5; k++){
                fill(canfind[j][k], canfind[j][k] + s.length(), -1);
            }
        }
        
        bool found = false;
        for(int j = 0 ; j < 5; j++){
            for(int k = 0; k < 5; k++){
                if(MAP[j][k] == s[0]){
                    if(dp(j,k,s)){
                        cout<<s<<" YES"<<endl;
                        found = true;
                        break;
                    }
                }
            }
            if(found) break;
        }
        if(!found) cout<<s<<" NO"<<endl;
    }
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    int C;
    cin>>C;
    while(C--){
        solve();
    }
    return 0;
}
