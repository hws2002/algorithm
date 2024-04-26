#include <SquareMatrix.h>


pow(const SquareMatrix&A, int m){
	//base
	if(m==0) return identity(A.size());
	if( m % 2 > 0) return pow(A,m-1) * A;
	SquareMatrix half = pow(A, m/2);
	return half * half;
}
