/*
 * Matheus Oliveira
 * 01:06:49 22/06/2019
 * Fast Matrix Exponentiation (more general and clean version)   =)
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;

struct Matrix {
	vector< vector<ll> > m;

	Matrix(int _r, int _c) {
		this->m.resize(_r);
		for(int i = 0; i < _r; i++) {
			this->m[i].resize(_c);
			for(int j = 0; j < _c; j++) this->m[i][j] = 0;
		}
	}
};

ll add(ll a, ll b) {
	return ((a%mod) + (b%mod))%mod;
}

ll mul(ll a, ll b) {
	return ((a%mod) * (b%mod))%mod;
}

Matrix makeIden(int n) {
	Matrix res = Matrix(n, n);
	for(int i = 0; i < n; i++) res.m[i][i] = 1;
	return res;
}

Matrix matMul(Matrix a, Matrix b) {
	int r1 = a.m.size(), c1 = a.m[0].size(), ra;
	int r2 = b.m.size(), c2 = b.m[0].size(), cb;

	// (r1.c1) x (r2.c2) -> (r1.c2)
	assert(c1 == r2);	
	Matrix res = Matrix(r1, c2);

	for(int i = 0; i < r1; i++) {
		for(int j = 0; j < c2; j++) {
			ra = i, cb = j;
			for(int k = 0; k < c1; k++) res.m[i][j] = add(res.m[i][j], mul(a.m[ra][k], b.m[k][cb]));
		}
	}

	return res;
}

Matrix fastExpo(Matrix a, ll e) {
	if(e == 0LL) return makeIden(a.m.size());
	if(e == 1LL) return a;
	if(e&1LL) return matMul(a, fastExpo(a, e-1LL));
	Matrix aux = fastExpo(a, e >> 1LL);
	return matMul(aux, aux);
}
