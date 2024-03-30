#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
vector< pair<int, int> > Vector_Pair_Endday_index;
int N;
int res_dp[16];

bool compare(const pair<int, int>& a, const pair<int, int> & b){
    return a.first < b.first;
}

int dp(int end_day, int m_index){
    if(res_dp[end_day] >= 0) return dp[end_day];
    
    int smallest_start_day = Vector_Pair_Endday_index[m_index].second / 1001;
    int pay = Vector_Pair_Endday_index[m_index].second % 1001;
    int sub_index = m_index;
    while(Vector_Pair_Endday_index[sub_index].first > smallest_start_day){
        sub_index--;
    }
    smallest_start_day = Vector_Pair_Endday_index[sub_index].first;
    res = pay + dp(smallest_start_day, sub_index);
    while(Vector_Pair_Endday_index[m_index] == end_day){
        start_day = Vector_Pair_Endday_index[m_index].second / 1001;
        pay =  Vector_Pair_Endday_index[m_index].second % 1001
        if(start_day <= smallest_start_day) continue;
        while(Vector_Pair_Endday_index[sub_index].first <= start_day){
            sub_index++;
        }
        sub_index--;
        start_day = Vector_Pair_Endday_index[sub_index];
        res = max(res, pay + dp(start_day, sub_index));
    }
    res_dp[end_day] = res;
    return res;
}

int main(){
    //input
    for(int i = 1; i <=N; i++){
        cin>>T[i]>>P[i];
        Vector_Pair_Endday_index.push_back({i+T[i],1001*i + P[i]});
    }
    
    std::fill(dp, dp+16, -1);
    dp[0] = 0;
    //sort
    std::sort(Vector_Pair_Endday_index.begin(), Vector_Pair_Endday_index.end(), compare);
    
    int m_index = Vector_Pair_Endday_index.size()-1;
    end_day = N;
    
    while(Vector_Pair_Endday_index[m_index].first > end_day){
        m_index--;
    }
    end_day = Vector_Pair_Endday_index[m_index].first;
    
    //solve
    int r_res = 0;
    while(end_day >=1){
        r_res = max(r_res, dp(end_day, m_index)>>endl; 
        while(Vector_Pair_Endday_index[m_index].first > end_day){
            m_index--;
        }
        end_day = Vector_Pair_Endday_index[m_index].first;
        end_day--;
    }
    
    cout<<r_res<<endl;
    return 0;
}