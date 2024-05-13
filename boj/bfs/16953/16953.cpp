#include <iostream>
#include <queue>
#define MAX 1000000000
using namespace std;

struct Node{
public:
    long long _x;
    int _height;
    Node(const int & x, const int & height):
        _x(x),
        _height(height){};
};

void dfs(const int start, const int target){
    queue<Node> q;
    q.push({start,0});
    while(!q.empty()){
        long long x = q.front()._x;
        int height = q.front()._height;
        q.pop();
        if( x == target){
            cout<<height+1<<endl;
            return ;
        }
        
        if( 2*x <= MAX && 2*x <= target ){
            q.push({2*x, height+1});
        }
        
        if(x*10 + 1 <= MAX &&  x*10 + 1 <= target){
            q.push({x*10 + 1, height+1});
        }
    }
    cout<<-1<<endl;
    return;
}

int main(){
    //input
    int A,B;
    cin>>A>>B;
    // if(A == B) {
    //     cout<<1<<endl;
    //     return 0;
    // }
    // int last = B%10;
    // if( last == 3 || last == 5 || last == 7 || last == 9) {
    //     cout<<-1<<endl;
    //     return 0;
    // }
    // if( last == 0) {
    //     if(A%10 != 0 && A%10 != 5) {
    //         cout<<-1<<endl;
    //         return 0;
    //     }
    // }
    dfs(A,B);
    return 0;
}