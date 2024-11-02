#include <iostream>
#include <vector>
#include <cstring>
#include <math.h>

#define MAX_N 105
#define MAX_M 505

#define all(v) v.begin(), v.end()
#define endl '\n'
// #define DEBUG_INPUT
// #define DEBUG_IDX
// #define DEBUG_RECON
using namespace std;

int m,q;

vector<string> dict;
double B[MAX_M] = {0};
double T[MAX_M][MAX_M] = {0};
double M[MAX_M][MAX_M] = {0};

double cache[MAX_N][MAX_M] = {0};
int choice[MAX_N][MAX_M] = {0};
vector<int> prev2didx;
int n;

// sidx : sequence idx, prev : previous word idx(dict)
double dp(int sidx, int prev){
    if( sidx >= n ) return 0.0;
    double & ret = cache[sidx][prev];
    if(ret != 1) return ret;
    ret = -1e200;
    for(int i = 0 ; i < m ; i++){
        double candid = T[prev][i] + M[i][prev2didx[sidx]] + dp(sidx+1, i);
        if( ret < candid) {
            ret = candid;
            choice[sidx][prev] = i;
        }
    }
    return ret;
}

int findidx(string & tof){
	for(int i = 0; i < dict.size();i++){
		if(dict[i] == tof) return i;
	}
	cout<<"sth went wrong"<<endl;
	return -1;
}

void infer(){
    cin>>n;

    //reset & input
    vector<string> pred(n);
    prev2didx.resize(n);
    for(int i = 0; i < n; i++){
        fill(cache[i], cache[i] + m, 1);
        cin>>pred[i];
        // TODO : pred[i]의 index를 찾는다
        prev2didx[i] = findidx(pred[i]);
	}
#ifdef DEBUG_IDX
for(int i = 0; i < n; i++){
	cout<<prev2didx[i]<<" ";
}
	cout<<endl;
#endif
    double ret = -1e200;
	int choice_f = -1;
    for(int i = 0 ; i < m; i++){
        if( ret < B[i] + M[i][prev2didx[0]] + dp(1,i)){
            ret = B[i] + M[i][prev2didx[0]] + dp(1,i);
            choice_f = i;
        }
    }

    // recon
#ifdef DEBUG_RECON
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cout<<choice[i][j]<<" ";
		}
		cout<<endl;
	}
#endif
	
	cout<<dict[choice_f]<<" ";
    for(int i = 1; i < n;i++){
        cout<<dict[choice[i][choice_f]]<<" ";
		choice_f = choice[i][choice_f];
    }
    cout<<endl;
}

int main(){
    cin>>m>>q;
    dict.resize(m);
	
    for(int i = 0 ; i < m; i++){
        cin>>dict[i];
    }
    
    for(int i = 0; i < m; i++){
        cin>>B[i];
		B[i] = log(B[i]);
    }
    
    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            cin>>T[i][j];
			T[i][j] = log(T[i][j]);
        }
    }
    
    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            cin>>M[i][j];
			M[i][j] = log(M[i][j]);
        }
    }
	
#ifdef DEBUG_INPUT
cout<<"B : ";
for(int j = 0; j < m; j++)
		cout<<B[j]<<" ";
cout<<endl;
	cout<<"T: ";
for(int i = 0; i < m; i++){
	for(int j = 0; j < m; j++){
		cout<<T[i][j]<<" ";
	}
	cout<<endl;
}
	cout<<"M  ";
for(int i = 0; i < m; i++){
	for(int j = 0; j < m; j++){
		cout<<M[i][j]<<" ";
	}
	cout<<endl;
}

#endif

    while(q--) infer();
    
    return 0;
}
