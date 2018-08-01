/*
 * Matheus Oliveira
 * 27/12/2017
 * fastMatrixExpo.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000

typedef long long lli;
lli matrizT[2][2], aux[2][2];

void matrixMultp(lli m[2][2], lli m2[2][2]) {
	lli ans[2][2];

	ans[0][0] = ( ((m[0][0]%MOD) * (m2[0][0]%MOD)) %MOD) + ( ((m[0][1]%MOD) * (m2[1][0]%MOD)) %MOD)%MOD;
	ans[0][1] = ( ((m[0][0]%MOD) * (m2[0][1]%MOD)) %MOD) + ( ((m[0][1]%MOD) * (m2[1][1]%MOD)) %MOD)%MOD;
	ans[1][0] = ( ((m[1][0]%MOD) * (m2[0][0]%MOD)) %MOD) + ( ((m[1][1]%MOD) * (m2[1][0]%MOD)) %MOD)%MOD;
	ans[1][1] = ( ((m[1][0]%MOD) * (m2[0][1]%MOD)) %MOD) + ( ((m[1][1]%MOD) * (m2[1][1]%MOD)) %MOD)%MOD;

	for(int i=0; i < 2; i++) {
		for(int j=0; j < 2; j++) m[i][j] = ans[i][j];
	}
}

void matrixExpo(lli m[2][2], lli e) {
	if(e <= 1) return;

	matrixExpo(m, e/2);
	matrixMultp(m, m);

	if(e % 2 != 0) matrixMultp(m, matrizT);
}

int main() {
	lli x, y, n, a1, a2, ans;
	while( scanf("%lld %lld %lld", &n, &x, &y) != EOF ) {
		matrizT[0][0] = x%MOD;
		matrizT[0][1] = y%MOD;
		matrizT[1][0] = 1;
		matrizT[1][1] = 0;

		a1 = x%MOD;
		a2 = (( (x%MOD) * (x%MOD) )%MOD + y%MOD)%MOD;
		n /= 5; 
 
		for(int i=0; i < 2; i++) {
			for(int j=0; j < 2; j++) aux[i][j] = matrizT[i][j];
		}

		matrixExpo( aux, n-2 );

		if(n == 1) {
			printf("%.6lld\n", a1);
			continue;
		}
		if(n == 2) {
			printf("%.6lld\n", a2);
			continue;
		}

		ans = ( ((aux[0][0]%MOD) * (a2%MOD)) % MOD ) + ( ((aux[0][1]%MOD) * (a1%MOD)) % MOD );
		ans %= MOD;

		printf("%.6lld\n", ans);
	}

	return 0;
}