#include <iostream>
#include <cstring>

using namespace std;
typedef int Rank;
#define DEFAULT_CAPACITY 10000

template <typename T> class Vector{
protected:
    Rank _size; int _capacity; T* _elem;
public:
    //Constructor
    Vector (int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
    { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v);}
    // Deconstructor
    ~Vector() {delete []_elem;}
    
    // read only
    Rrank size() const {return _size;}
    bool empty() const {return !_size;}
    
    // write only
    T& operator[] (Rank r) const;
    T remove( Rank r);
	int remove (Rank lo, Rank hi);
    Rank insert( Rank r, T const& e);
    Rank insert( T const& e ) { return insert (_size, e);}
    
}; //Vector

