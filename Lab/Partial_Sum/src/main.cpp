#include <iostream>
#include "Brute_force.hpp"
#include "Brute_force_improved.hpp"
#include "Divide_and_Conquer.hpp"
#include "constants.hpp"
// 1sec = 1e6 microsec
int main(){
    //Create a random vector
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(-100,100);
    vector<int> A(1000);
    printf("Given Vector : ");
    for(int i=0; i<A.size();i++){
        A[i] = distr(eng);
        printf("%d ",A[i]);
    }
    printf("\n");
    /*-----Brute Force----*/
    //Get the start time
    auto start = std::chrono::high_resolution_clock::now();
    //Run the algorithm
    if(Brute_force_MaxSum(A) != MIN)
        printf("Largest sum of contiguous subarray : %d . Start index : %d, End index : %d\n",Brute_force_MaxSum(A),s,e);
    //Get the end time
    auto end = std::chrono::high_resolution_clock::now();
    //Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    std::cout<<"The algorithm took "<<duration<<" microseconds"<<std::endl;
    
    /* ----- Improved Brute Force-----*/
    s = -1,e = -1;
    start = std::chrono::high_resolution_clock::now();
    if(Improved_Brute_force_MaxSum(A) != MIN)
        printf("Largest sum of contiguous subarray : %d . Start index : %d, End index : %d\n",Improved_Brute_force_MaxSum(A),s,e);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    std::cout<<"The algorithm took "<<duration<<" microseconds"<<std::endl;

    /*-------Divide and Conquer----------*/
    start = std::chrono::high_resolution_clock::now();
    if(Divide_and_Conquer_MaxSum(A,0,A.size()-1)!=MIN)
        printf("Largest sum of contiguous subarray : %d. Cannot provide index for this algorithm now \n",Divide_and_Conquer_MaxSum(A,0,A.size()-1));
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    std::cout<<"The algorithm took "<<duration<<" microseconds"<<std::endl;


    /**/
    return 0;
}