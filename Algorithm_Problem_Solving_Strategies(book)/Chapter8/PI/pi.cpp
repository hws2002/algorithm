#include <iostream>
#include <cstring>
#include <fstream>

#define MAX_N 10002
#define endl '\n'
#define INF 2000000000
using namespace std;

int cache[MAX_N] = {0};

string seq;

// seq[idx ~ idx + stp)를 외우는데 필요한 난이도
int cost(int idx, int stp){
    bool d1 = true;
    for(int i = idx+1; i < idx + stp; i++){
        if(seq[i] != seq[idx]) {d1 = false; break;}
    }
    if(d1) return 1;

    bool d2 = true;
    for(int i = idx+2; i < idx + stp; i++){
        if((seq[i] - seq[i-1]) != seq[idx + 1] - seq[idx]) { d2 = false; break;}
    }
    if(d2 && abs(seq[idx+1] - seq[idx]) == 1) return 2;

    bool d4 = true;
    int l = seq[idx];
    int r = seq[idx+1];
    for(int i = 2; i < stp; i++){
        if(i%2){ // 홀수
            if(seq[idx+i] != r) { d4 = false; break;}
        } else { // 짝수
            if(seq[idx+i] != l) { d4 = false; break;}
        }
    }
    if(d4) return 4;
    
    bool d5 = true;
    int dff = seq[idx+1] - seq[idx];
    for(int i = idx+2; i < idx + stp; i++){
        if( seq[i] - seq[i-1] != dff) { d5 = false; break;}
    }
    if(d5) return 5;
    
    return 10;
}


int classify(int a, int b){
	string M = seq.substr(a, b-a+1);
	if( M == string(M.size(), M[0])) return 1;
	bool progressive= true;
	for(int i = 0 ; i < M.size() -1; i++)
		if(M[i+1] -M[i] != M[1] - M[0])
			progressive = false;
	if(progressive && abs(M[1] - M[0])== 1)
		return 2;

	bool alternating = true;
	for(int i = 0 ; i< M.size(); i++){
		if(M[i] != M[i%2])
			alternating = false;
	}
	if(alternating) return 4;
	if(progressive) return 5;
	return 10;
}

// dp(i) : i번쨰 숫자에서부터 외운다고 할때, 최소 난이도
int dp(int idx){
    //base
    if(idx >= seq.size()) return 0;
    int & ret = cache[idx];
    if(ret>-1) return ret;
    ret = INF;
    for(int stp = 3; stp <= 5; stp++){
        // printf("cost(%d, %d) %d \n", idx, stp, cost(idx,stp));
		if( idx + stp <= seq.size())
        	// ret = min(ret, classify(idx, idx+stp-1) + dp(idx + stp));
		    ret = min(ret, cost(idx, stp) + dp(idx + stp));

    }
    return ret;
}

int solve(){
    cin>>seq;
    //reset
    fill(cache, cache+seq.size(), -1);
    cout<<dp(0)<<endl;
	return dp(0);
}

int main(){
	ofstream fl;
	fl.open("output.txt");
    int c;
    cin>>c;
    while(c--) fl<<solve()<<endl;
	fl.close();
    return 0;
}