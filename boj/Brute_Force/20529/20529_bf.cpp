//memoization

#include <iostream>
#include <cstring>
#include <vector>
#include <limits.h>

using namespace std;

int res;
vector<int> MBTIs;
char estj[5] = "ESTJ";

//memoization
int CACHE[16][16] = {0};

void parseMBTI(const string & temp){
    int num = 0; int toadd = 1;
    for(int i = 0 ; i < 4; i++){
        if(temp[i] == estj[i]){
           num += toadd; 
        }
        toadd *= 2;
    }
    MBTIs.push_back(num);
}

int calDistance(const vector<int> & picked){
    int dist = 0;
    int A = MBTIs[picked[0]];
    int B = MBTIs[picked[1]];
    int C = MBTIs[picked[2]];
    //A <-> B
    if(CACHE[A][B] || CACHE[B][A]) dist += CACHE[A][B];
    else if (A==B) dist += 0;
    else {
        int toadd = 0;
        while(A > 0 || B > 0){
            if(A%2 != B%2) toadd++;
            A>>=1;
            B>>=1;
        }
        A = MBTIs[picked[0]]; B = MBTIs[picked[1]];
        CACHE[A][B] = toadd; CACHE[B][A] = toadd;
        dist += toadd;
    }
    //B <-> C
    if(CACHE[B][C] || CACHE[C][B]) dist += CACHE[B][C];
    else if( B == C) dist +=0;
    else {
        int toadd = 0;
        while(B > 0 || C > 0){
            if(B%2 != C%2) toadd++;
            B>>=1;
            C>>=1;
        }
        B = MBTIs[picked[1]]; C = MBTIs[picked[2]];
        CACHE[B][C] = toadd; CACHE[C][B] = toadd;
        dist += toadd;
    }
    
    //A <-> C
    if(CACHE[A][C] || CACHE[C][A]) dist += CACHE[A][C];
    else if( A == C) dist +=0;
    else {
        int toadd = 0;
        while(A > 0 || C > 0){
            if(A%2 != C%2) toadd++;
            A>>=1;
            C>>=1;
        }
        A = MBTIs[picked[0]]; C = MBTIs[picked[2]];
        CACHE[A][C] = toadd; CACHE[C][A] = toadd;
        dist += toadd;
    }
    return dist;
}

bool stop = false;
void pick(const int & n, vector<int> & picked, int toPick){
    //base
    if(toPick == 0) {
        res = min(res, calDistance(picked));
		if(res == 0)  stop = true;
        return ;
    }
    
    int smallest = picked.empty() ? 0 : picked.back() + 1;
    for(int next = smallest; next < n; next++){
        picked.push_back(next);
        pick(n, picked, toPick-1);
		if(stop) return ;
        picked.pop_back();
    }
}

void solve(){
    //input
    int N;
    cin>>N; 

    string temp;
    
    for(int i = 0; i < N; i++){
        cin>>temp;
        parseMBTI(temp);
    }
    
	//trivial case
    if( N >= 33) {
        cout<<0<<endl;
        return;
    }
    //solve
    res = INT_MAX; stop = false;
    vector<int> picked;
    pick(N, picked, 3);
    cout<<res<<endl;
    MBTIs.clear();

    return ;
}

int main(){
    //input
    int T;
    cin>>T;
    for(int i = 0 ; i < T; i++){
        solve();
    }
    return 0;
}