#include <iostream>
#include <limits.h>
#include <vector>

#define MAX_N 20
using namespace std;

int N;
int S[MAX_N][MAX_N] = {0};

// int total_ability = 0;
int min_diff = INT_MAX;


int calValue(vector<int> & selected, int value, int next){
    int ret = value;
    for(auto i : selected){
        ret += S[i][next];
        ret += S[next][i];
    }
    return ret;
}

// value는 selected 에 의해 유일하게 결정된다
void nchooser(int idx, int tochoose, vector<int> & selected, vector<bool> & visit, int value){
    if(tochoose <=0 ){
		
        vector<int> n_selected;
        for(int i = 0; i < N; i++){
            if(!visit[i]) n_selected.push_back(i);
        }
        
        int value2 = 0;
        for(int i = 0 ; i < N/2; i++){
			int a = n_selected[i];
            for(int j = i + 1; j < N/2; j++){
				int b = n_selected[j];
                value2 += S[a][b];
                value2 += S[b][a];
            }
        }
        
        min_diff = min( min_diff, abs(value2 - value));
        return ;
    }
    
    for(int next = idx; next < N; next++){
        if( !visit[next] ){
            visit[next] = true;
            selected.push_back(next);
            nchooser(next, tochoose-1, selected, visit, calValue(selected, value, next));
            selected.pop_back();
            visit[next] = false;
        }
    }
}

int main(){
    cin>>N;
    
    for(int i = 0 ; i < N; i++){
        for(int j = 0 ; j < N; j++){
            cin>>S[i][j];
            // total_ability += S[i][j];
        }
    }    
    
    //try out all consequences
    vector<int> selected;
    vector<bool> visit(N,false);
    nchooser(0,N/2,selected,visit,0);
    
    cout<<min_diff<<endl;
    return 0;
}