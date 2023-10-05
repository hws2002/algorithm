#include <iostream>
#include <random>
using namespace std;

/***
 * @brief 삽입 정렬 Insertion Sort
 * @param vector<int> &A : a vector of integers
 * @return void
 * @remark A를 오름차순으로 정렬한다.
 * @remark 만약 중복된 값이 있을 경우, 그 중 더 뒤에 위치한 값을 선택한다.
*/
void insertionSort(vector<int> & A){
    for(int i=0; i<A.size(); ++i){
        int j = i;
        while(j>0 && A[j-1] > A[j]){
            swap(A[j-1],A[j]);
            j--;
        }
    }
}
int main(){
    //Create a random vector
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0,100);
    vector<int> A(10);
    for(int i=0; i<A.size();i++){
        A[i] = distr(eng);
    }
    cout<<"BEFORE SORTING"<<endl;
    for(int i=0; i<A.size();i++){
        cout << A[i] << " ";
    }
    printf("\n");
    //sort
    insertionSort(A);
    //print
    cout<<endl<<"AFTER SORTING"<<endl;
    for(int i=0; i<A.size();i++){
        cout << A[i] << " ";
    }
    return 0;
}