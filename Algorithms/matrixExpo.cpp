/*
 * Matheus Oliveira
 * 27/12/2017
 * 1474.cpp
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