#include <iostream>
#include <vector>

#define MAX_N 300'000
// #define DEBUG_INPUT
using namespace std;
typedef long long ll;

ll Answer;
vector<bool> Seq;
ll N,S,E;
vector<ll> cache;
// S : 0 to 1
// E : 1 to 0

vector<ll> numofOnefrom;

ll makeAllZerofrom(const ll idx){
    return E * (ll)numofOnefrom[idx];
}

ll makeAllOnefrom(const ll idx){
    return S * (ll)( Seq.size() - idx - numofOnefrom[idx] );
}

ll dp2(const ll here){
    //base
    if(here >= Seq.size()) return 0;
    if(numofOnefrom[here] <= 0) return 0;
    
    // Seq[here] 은 조건 0이다.
    ll & ret = cache[here];
    if (ret > -1) return ret;
    ret = makeAllZerofrom(here);
        
    // 연속된 0을 찾는다
    ll idx = here;
    while(idx < Seq.size() && !Seq[idx]) idx++;
    //위의 기저 조건으로 인해idx가 맨 끝에 도달할 수 없다 
    ll num_0 = idx - here;
    
    // 0이 나올때까지 idx를 증가시킨다
    while(idx < Seq.size() && Seq[idx]) idx++;
    return ret = min( ret , S * num_0 + dp2(idx));
}

ll dp(const ll here){
    // cout<<"here : "<<here<<" ";
    if(here >= Seq.size()) return 0;
    
    // 연속된 1의 길이를 먼저 구한다.
    ll idx = here;
    while(idx < Seq.size() && Seq[idx]) {
        idx++;
    }

    //만약 seq의 끝에 도달했다면 0을 리턴한다
    if(idx >= Seq.size()) return 0;
    ll num_1 = idx - here;
    
    // 1...1 을 유지할 경우
    ll res1 = dp2(idx);
    // cout<<"res1 : "<<res1;
    
    // ll temp = idx;
    //연속된 0의 길이를 구한다
    while(idx < Seq.size() && !Seq[idx]){
        idx++;
    }

    //만약 seq의 끝에 도달했다면 여전히 0을 리턴한다.
    if(idx >= Seq.size()) return 0;
    // ll num_0 = idx - temp;
    
    
    // 1...1을 유지하지 않을 경우
    ll res2 = E * num_1 + dp(idx);
    // cout<<" res2 : "<<res2<<endl;
    
    return min(res1,res2);
}

int main(int argc, char** argv)
{
	int T, test_case;

// 	freopen("input.txt", "r", stdin);
	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{

		Answer = 0;
        
        //input
        cin>>N>>S>>E;
        // Seq.resize(N);

        bool first1appeared = false; 
        int temp;
        ll total_num_1 = 0;
        for(int i = 0; i < N; i++){
            cin>>temp;
            if(temp == 1 && !first1appeared) first1appeared = true;
            if(!first1appeared) continue;
            Seq.push_back(temp);
            if(temp) total_num_1++;
        }

        numofOnefrom.resize(Seq.size());
        cache.resize(Seq.size());
        for(int i = 0; i < Seq.size(); i++){
            if(Seq[i]) numofOnefrom[i] = total_num_1--;
            else numofOnefrom[i] = total_num_1;
            cache[i] = -1;
        }
#ifdef DEBUG_INPUT
for(int i = 0; i < Seq.size();i++){
    cout<<Seq[i]<<" ";
}
cout<<endl;

for(int i = 0; i < numofOnefrom.size(); i++){
    cout<<numofOnefrom[i]<<" ";
}
cout<<endl;
#endif
        //solve
        Answer = dp(0);
		/////////////////////////////////////////////////////////////////////////////////////////////

    	/////////////////////////////////////////////////////////////////////////////////////////////
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
        Seq.clear();
        numofOnefrom.clear();
        cache.clear();
	}

	return 0;//Your program should return 0 on normal termination.
}