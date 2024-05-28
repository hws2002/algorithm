#include <iostream>
#include <map>
#include <vector>

typedef int KeyType;
typedef long long ll;

using namespace std;

ll res = 1;
int N;
map<int,int> key2height;

int largest = 0;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N;
    
    vector<bool> hasLeftChild(N, false);
    
    int p;
    cin>>p;
    key2height[p] = 1;
    largest = p;
    
    int height = 0;
    for(int i = 0; i < N-1; i++){
        cin>>p;
        if(p > largest){
            height = (--(key2height.end()))->second+1;
            res += height;
            key2height[p] = height;
            largest = p;
        } else {
            auto itup = key2height.upper_bound(p);
            if(hasLeftChild[ itup->first -1]){
                itup--;
                height = itup->second+1;
                res += height;
                key2height[p] = height;
            } else {
                hasLeftChild[ itup->first -1] = true;
                height = itup->second + 1;
                res += height;
                key2height[p] = height;
            }
            
        }
    }

    //output
    cout<<res<<endl;
    return 0;
}