#include <iostream>
#include <vector>
#include <cassert>

#define MOD 1'000
typedef long long ll;

using namespace std;

class SquareMatrix{
public:
    int _dim; // 2d matrix
    int _size;
    vector< vector<int> > _matrix;
	
	// SquareMatrix(const int size, const int dim = 2);
	// SquareMatrix identity(const int size);
	// void printMatrix();
	// SquareMatrix operator * (const SquareMatrix &rhs) const;
	// SquareMatrix pow(const ll b);
	// int * operator[] (const int idx);
	
	SquareMatrix identity(const int size){
		SquareMatrix ret = SquareMatrix(size);
		for(int i = 0; i < size; i++){
			ret._matrix[i][i] = 1;
		}
		return ret;
	}
	
    // functions
    SquareMatrix pow(const ll b){
        if(b == 0) return SquareMatrix::identity(_size);
        if(b%2) return (*this) * (this->pow(b-1));
        SquareMatrix half = this->pow((b>>1));
        return half*half;
    }
	
	void printMatrix(){
		for(int i = 0 ; i < _size; i++){
			for(int j = 0 ; j < _size; j++){
				cout<<_matrix[i][j]<<" ";
			}
			cout<<endl;
		}
	}
    
    // constructor
    SquareMatrix(const int size, const int dim = 2):
        _size(size),_dim(dim){
            //initialize with 0 values
            _matrix.resize(size, vector<int>(size, 0)); 
        };
    //operator
    SquareMatrix operator * (const SquareMatrix & rhs) const {
        assert(_size == rhs._size);
        SquareMatrix ret = SquareMatrix(_size);
        
        for(int i = 0 ; i < _size; i++){
            for(int j = 0; j < _size; j++){
                for(int k = 0; k < _size; k++){
                    ret._matrix[i][j] = (ret._matrix[i][j] + (_matrix[i][k] * rhs._matrix[k][j]) % MOD) % MOD;
                }
            }
        }
        return ret;
    };
    
    int * operator[](const int idx) {
        return &_matrix[idx][0];
    }
};

int main(){
    int N;
    ll B;
    cin>>N>>B;
    SquareMatrix Matrix = SquareMatrix(N,2);
    
    for(int i = 0 ; i <N; i++){
        for(int j = 0 ; j < N; j++){
            cin>>Matrix[i][j];
        }
    }
    
    SquareMatrix ret = Matrix.pow(B);
    ret.printMatrix();
	return 0;
}