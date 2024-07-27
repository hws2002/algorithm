#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 100'000
// #define DEBUG_INPUT
// #define DEBUG_SEARCH
using namespace std;
typedef long long ll;

ll Answer;
ll  N, Q, X;
vector<ll> presumW;
vector<pair<ll,int> > W;
vector<ll> presumidx2W;

bool compare(pair<ll, int> & a, pair<ll,int> & b){
    if(a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}

bool compare2(pair<ll, int> & a, pair<ll,int> & b){
    return a.second < b.second;
}

bool cmp(ll h, pair<ll, int> const & p){
    return p.first < h;
}

int main(int argc, char** argv)
{
	int T, test_case;

	// freopen("input.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{

		Answer = 0;
		/////////////////////////////////////////////////////////////////////////////////////////////
        
        //input
        cin>>N>>Q;
        W.resize(N);
        ll temp;
        for(int i = 0; i < N; i++){
            cin>>temp;
            W[i] = {temp,i};
        }
        
        //pre
        sort(W.begin(), W.end(), compare);

        ll height = -1;
        ll newheight = 0;
        presumW.push_back(0);
        presumidx2W.push_back(0);
        for(int i = 0 ; i < N; i++){
            if( W[i].first == newheight) continue;
            height = newheight;
            newheight = W[i].first;
            ll area = (newheight - height) * (N-(ll)i);
            if(presumW.empty()) presumW.push_back(area);
            else presumW.push_back(presumW.back() + area);
            presumidx2W.push_back(newheight);
        }
#ifdef DEBUG_INPUT
for(auto e : W){
    printf("(%lld, %d) ",e.first, e.second);
}
cout<<endl;
for(auto e : presumW){
    cout<<e<<" ";
}
cout<<endl;
for(auto e : presumidx2W){
    cout<<e<<" ";
}
cout<<endl;
#endif
        //query
        while(Q--){
            cin>>X;
            //parametric search
            int lo = 0; int hi = presumW.size();
            int mid;
            bool found_exact = false;
            while(lo < hi){
                mid = (lo + hi) >> 1;
                if( presumW[mid] > X) {
                    hi = mid;
                } else if (presumW[mid] < X) {
                    if(lo == mid) break;
                    lo = mid;
                } else { //presum[mid] == X
                    // 바로 살아있는 프로세스들 중, 번호가 가장 큰 프로세스를 출력한다.
                    // TODO : optimize
                    for(int i = N; i >= 0; i--){
                        if( W[i].first >= presumidx2W[mid]){
                            Answer += i;
                            break;
                        }
                    }

                    //
                    found_exact = true;
                    break;
                }
            }
#ifdef DEBUG_SEARCH
printf("mid, height : %d %lld \n", mid, presumidx2W[mid]);
#endif
            if(!found_exact){ // 이제 mid를 잘 활용해야 함.
                ll height = presumidx2W[mid];          

                auto it = upper_bound( W.begin(), W.end(), make_pair(height+1, -1));
                vector<pair<ll,int>> W2(it, W.end());
#ifdef DEBUG_SEARCH
printf("distance(it,W.begin() : %d) \n", it - W.begin());
#endif
                sort(W2.begin(), W2.end(),compare2);
#ifdef DEBUG_SEARCH
for(auto e : W2){
    printf("(%lld, %d) ",e.first, e.second);
}
cout<<endl;
#endif
                ll idx = (X - presumW[mid]) % ((ll)W2.size());
                idx--; if(idx < 0) idx = W2.size()-1;
#ifdef DEBUG_SEARCH
printf("W2[%lld] : %d \n", idx, W2[idx].second+1);
#endif
                Answer += W2[idx].second+1;
            }
        }
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
        presumW.clear();
        W.clear();
        presumidx2W.clear();
	}

	return 0;//Your program should return 0 on normal termination.
}