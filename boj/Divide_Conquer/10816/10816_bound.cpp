#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<int> v;
    int N,M,count;
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>count;
        v.push_back(count);
    }
    sort(v.begin(), v.end());
    cin>>M;
    for(int i=0;i<M;i++){
        cin>>count;
        cout<<upper_bound(v.begin(), v.end(), count)-lower_bound(v.begin(), v.end(), count)<<' ';
    }
}