#include <iostream>

#define MOD 1000000007
using namespace std;
typedef long long ll;

int powM(int a,int p){
	ll res = 1;
	ll tomul = a;
	while(p){
		if(p&1){
			res *= tomul;
			res %= MOD;
			printf("res : %lld \n", res);
		}
		tomul *= tomul;
		tomul %= MOD;
		p >>= 1;
	}
	return res;
}

int main(){
	int a = 5;
	int p = 3;
	cout<<powM(a,p)<<endl;
	
	return 0;
}