//vector implementation of minimum heap
#include <iostream>
#include <vector>

#define endl '\n'
using namespace std;

void push_heap(vector<int> & heap, const int x){
    heap.push_back(x);
    int here = heap.size()-1;
    while(here > 0 && heap[ (here-1)/2 ] > heap[here]){
        swap(heap[ (here-1)/2], heap[here]);
        here = (here-1)/2;
    }
}


void pop_heap(vector<int> & heap){
    heap[0] = heap.back();
    heap.pop_back();
    int here = 0;
    while(true){
        int left = here * 2 + 1, right = here * 2 + 2;
        if( left >= heap.size()) break;
        int next = here;
        if( heap[next] > heap[left]) 
            next = left;
        if( right < heap.size () && heap[next] > heap[right])
            next = right;
        if (next == here) break;
        swap( heap[here], heap[next]);
        here = next;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    cin>>N;
    int x;
    vector<int> heap;
    for(int i = 0 ; i < N; i++){
        cin>>x;
        if( x > 0 ) push_heap(heap, x);
        else {
            if(heap.empty()) cout<<0<<endl;
            else {
                cout<<heap.front()<<endl;
                pop_heap(heap);
            }
        }
    }
    
    return 0;
}