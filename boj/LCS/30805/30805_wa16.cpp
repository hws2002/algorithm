#include <iostream>
#include <vector>
#include <algorithm>

// #define DEBUG_LCS
// #define DEBUG_SOLVE
#define MAX_N 105
#define MAX_A 101
using namespace std;

int N,M;
int A[MAX_N] = {0};
int B[MAX_N] = {0};
struct Node{
public:
    int x;
    int y;
    Node(const int _x, const int _y):
        x(_x),
        y(_y){};
};

vector<Node> num2Node[MAX_A];

bool compare(const Node & a , const Node & b){
    if(a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}


//sliding-window
void LCS(){
    int table[3][MAX_N] = {0};
    
    //base
    int lcs = 0;
    for(int i = 0; i < M; i++){
        if(A[0] == B[i]) {
            if(lcs == 0) num2Node[B[i]].push_back(Node(0,i));
            lcs = 1;
        }
        table[0][i] = lcs;
    }
#ifdef DEBUG_LCS
for(int i = 0 ; i < M ; i++){
    cout<<table[0][i]<<" ";
}
cout<<endl;
#endif
    for(int r = 1 ; r < N; r++){
        
        // c == 0 case
        if(A[r] == B[0] && table[(r+1)%2][0] == 0) {
            table[r%2][0] = 1;
            num2Node[A[r]].push_back(Node(r,0));
        } else {
            table[r%2][0] = table[(r+1)%2][0];
        }
        
        for(int c = 1; c < M; c++){
            if(A[r] == B[c]){
                table[r%2][c] = table[(r+1)%2][c-1] + 1;
                if( table[r%2][c-1] < table[r%2][c] && table[(r+1)%2][c] < table[r%2][c])
                    num2Node[A[r]].push_back(Node(r,c));
            }
            else {
                table[r%2][c] = max(table[r%2][c-1] , table[(r+1)%2][c]);
            }
        }
#ifdef DEBUG_LCS
for(int i = 0 ; i < M; i++){
    cout<<table[r%2][i]<<" ";
}
cout<<endl;
#endif
    }
}



vector<int> solve(){
    vector<int> res;
    int x = -1 ; int y = -1;
    for(int digit = MAX_A - 1; digit >= 1 ; digit--){
#ifdef DEBUG_SOLVE
        cout<<"start investigate num2Node["<<digit<<"]"<<endl;
#endif
        if(num2Node[digit].empty()) continue;
        std::sort(num2Node[digit].begin(), num2Node[digit].end(), compare);
#ifdef DEBUG_SOLVE
        cout<<"num2Node["<<digit<<"] survived. x,y ; "<<x<<","<<y<<endl;
#endif
        // auto iter = upper_bound(num2Node[digit].begin(), num2Node[digit].end(), x);
        auto iter = num2Node[digit].begin();
        while(iter != num2Node[digit].end()){
            while( iter != num2Node[digit].end() && (iter->x <= x || iter->y <= y)) iter++;
            if(iter == num2Node[digit].end()) continue;
            res.push_back(digit);
            x = iter->x; y = iter->y;
#ifdef DEBUG_SOLVE
            cout<<"pushing back "<<x<<","<<y<<endl;
#endif
        }
    }
    return res;
}

int main(){
    cin>>N;
    for(int i = 0 ; i < N; i++){
        cin>>A[i];
    }
    
    cin>>M;    
    for(int i = 0 ; i < M; i++){
        cin>>B[i];
    }
    
    // dp
    LCS(); // build Vector
#ifdef DEBUG_LCS
for(int i = 1 ; i < MAX_A; i++){
    cout<<"printing out num2Node["<<i<<"] : ";
    for(auto node : num2Node[i]){
        cout<<"("<<node.x<<","<<node.y<<") ";
    }
    cout<<endl;
}

#endif
    vector<int> res = solve();
    cout<<res.size()<<endl;
    if(!res.empty()){
        for(auto itm : res)
            cout<<itm<<" ";
    }
    cout<<endl;
    return 0;
}