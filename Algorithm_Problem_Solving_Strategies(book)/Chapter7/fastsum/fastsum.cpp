//1부터 n까지의 합을 구하는 분할 정복 알고리즘

//필수 조건 : n은 자연수
// 1+2+...+n을 반환한다.

int fastSum(int n){
	//base
	if(n == 1) return 1;
	if(n % 2) return n + fastSum(n-1);
	return 2 * fastSum(n/2) + (n/2) * (n/2);
}