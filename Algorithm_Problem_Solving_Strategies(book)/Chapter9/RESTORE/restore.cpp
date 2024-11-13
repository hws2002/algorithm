#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#define MAX_K 15
#define INF 2000000000
#define endl '\n'

// #define DEBUG_INPUT
// #define DEBUG_DP

using namespace std;
pair<int, int> cache[MAX_K][(1<<MAX_K)];
int cost[MAX_K][MAX_K] = {{0}};

vector<string> s;
int k;
int total_num_words;

void deduplicate(){
	sort(s.begin(), s.end(), [](const string & l, const string & r){
		return l.size() < r.size();
	});
	
	bool toremove[MAX_K] = {false};
	
	for(int i = 0; i < s.size(); i++){
		bool found = false;
		for(int j = i+1; j < s.size(); j++){
			if(s[j].find(s[i]) != string::npos){
				found = true;
				break;
			}
		}
		toremove[i] = found;
	}
	
	vector<string> s_copy;
	for(int i = 0; i < s.size(); i++){
		if(!toremove[i]) s_copy.push_back(s[i]);
	}
	s = s_copy;
    return ;
}

#ifdef DEBUG_DP
string de2bi(int avail){
	if(avail == 0) return string(total_num_words,'0');
	string sret;
	while(avail){
		if(avail%2) sret+='1';
		else sret+='0';
		avail>>=1;
	}
	reverse(sret.begin(), sret.end());
	return sret;
}
#endif

pair<int,int> dp(const int i, const int avail){
    auto & ret = cache[i][avail];
    if(ret.first) return ret;
    ret.first = INF;
    for(int j = 0; j < total_num_words; j++){
        if( (avail & (1<<j) ) && i != j){
			auto candid = dp(j, avail & ~(1<<j));
            if( ret.first > s[i].size() - cost[i][j] + candid.first){
				ret = {s[i].size() - cost[i][j] + candid.first,j};
				
			}
        }
    }
	
	if(ret.first >= INF){
		ret = {s[i].size(), i};
	}
	
#ifdef DEBUG_DP
	cout<<"dp("<<i<<","<<de2bi(avail)<<") : "<<ret.first<<endl;
#endif
	return ret;
// printf("dp(%d,%s) : %d \n", i, de2bi(avail), ret);
    // return ret >= INF ? s[i].size() : ret;
}

void solve(){
    cin>>k;
    string temp;
    //reset
    for(int i = 0 ; i < k ;i++){
        fill(cache[i], cache[i] + (1<<MAX_K) , make_pair(0,-1));
    }
    s.clear();
    for(int i = 0; i < k; i++){
        cin>>temp;
		s.push_back(temp);
    }
    
	deduplicate();

    int ret = 400;
    total_num_words = s.size();
    
    //set cost
    for(int i = 0; i < total_num_words; i++){
        for(int j = 0; j < total_num_words; j++){
            if(i == j) cost[i][j] = s[i].size();
            else {
                int c = min<int>(s[i].size(), s[j].size());
				while(c--){
					bool found = true;
					for(int k = 0; k < c; k++){
						if(s[j][k] != s[i][ s[i].size()-c+k] ){
							found = false;
							break;
						}
					}
					if(found){
						cost[i][j]  = c;
						break;
					}
				}
            }
        }
    }

#ifdef DEBUG_INPUT
for(auto w : s){
	cout<<w<<" ";
}
cout<<endl;
	
for(int i = 0; i < total_num_words; i++){
    for(int j = 0; j < total_num_words; j++){
        cout<<cost[i][j]<<" ";
    }
    cout<<endl;
}
#endif
	pair<int,int> h;
	h = {INF,-1};
    string sret; 
	int hidx = -1;
	int avail;
	for(int i = 0; i < total_num_words; i++){
		auto candid = dp(i, (1<<total_num_words) - 1 - (1<<i));
		if( h.first > candid.first){
			h = candid;
			hidx = i;
			avail = (1<<total_num_words) - 1 - (1<<i);
		}
    }
	
	// cout<<h.first<<endl;
	int nxt = h.second;
	sret += string( s[hidx].begin(), s[hidx].begin() + s[hidx].size() - cost[hidx][nxt]);
	
	//recon	
	while(avail){
		hidx = nxt; nxt = cache[hidx][avail-(1<<hidx)].second;
		avail -= (1<<h.second);
		if(!avail) break;
		sret += string(s[hidx].begin(), s[hidx].begin() + s[hidx].size() - cost[hidx][nxt]);
		h = cache[h.second][avail];
	}
	
	sret+=s[hidx];
	cout<<sret<<endl;
}

int main(){
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);
	// cout.tie(NULL);
    int c;
    cin>>c;
    while(c--) solve();
    return 0;
}
