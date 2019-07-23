/*
 * Matheus Oliveira
 * 13/04/2018
 * sparseTable.cpp
 *
 * (Exemplo com SPT de max)
*/

#include <bits/stdc++.h>
using namespace std;

#define INF 2e9
#define MAXL 18
#define MAXN 100010
typedef long long ll;

int lg[MAXN], spt[MAXL][MAXN], elements[MAXN], n;

void build() {
	int aux, val;

	for(int i = 1; i <= n; i++) {
		aux = i;
		val = 0;

		while(aux/2 > 0) val++, aux /= 2;
		lg[i] = val;
	}

	for(int i = 0; i < n; i++) spt[0][i] = elements[i];

	for(int j = 1; j <= lg[n]; j++) {
		for(int i = 0; (i + (1 << (j-1)) ) < n; i++) {
			spt[j][i] = max(spt[j-1][i], spt[j-1][i + (1 << (j-1))]);
		}
	}
}

int query(int l, int r) {
	int elementosNoIntervalo = r-l+1;
	return max( spt[ lg[elementosNoIntervalo] ][l], spt[ lg[elementosNoIntervalo] ][ r - (1 << lg[elementosNoIntervalo]) + 1 ] );
}