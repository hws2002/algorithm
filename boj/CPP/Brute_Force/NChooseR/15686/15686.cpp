#include <iostream>
#include <vector>
#include <limits.h>
#include <cmath>

#define MAX 51
#define DIST(r1,c1,r2,c2) ( abs(r1 - r2) + abs(c1-c2) )

using namespace std;
int N,M;
int MAP[51][51] = {0}; 
vector<int> houses;
vector<int> bbqs;
int res = INT_MAX;

void calDists(vector<int> & chosen_bbqs){
    int dist = 0;
    for(auto house : houses){
        int dist_hb = INT_MAX;
        int house_x = house / MAX;
        int house_y = house % MAX;
        for(auto bbq : chosen_bbqs){
            int bbq_x = bbq / MAX;
            int bbq_y = bbq % MAX;
            dist_hb = min(dist_hb, DIST(house_x,house_y,bbq_x,bbq_y));
        }
        dist += dist_hb;
        if( dist > res ) break;
    }
    res = min(res, dist);
}

void nChoosem(const int last, vector<int> & chosen_bbqs, vector<bool> & viist ,int remaining){
    if(remaining <=0 ) {
        calDist(chosen_bbqs);
        return ;
    }
    
    for(int next = last + 1; next < bbqs.size(); next++){
        if(!visit[next]){
            visit[next] = true;
            chosen_bbqs.push_back(bbq[next]);
            nChoosem(next, chosen_bbqs, visit, remaining-1);
            chosen_bbqs.pop_back();
            visit[next] = false;
        }
    }
}
    
int main(){
    cin>>N>>M;
    for(int i = 1 ; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin>>MAP[i][j];
            if(MAP[i][j] == 1) houses.push_back( i * 51 + j);
            else if (MAP[i][j] == 2) bbqs.push_back( i * 51 + j);
            else{}
        }
    }
    
    // choose and calculate
    vector<int> chosen_bbqs;
    vector<bool> visit(bbqs.size(), false);
    nChoosem(-1, chosen_bbqs, visit,M);
    
    //output
    cout<<res<<endl;
    return 0;
}