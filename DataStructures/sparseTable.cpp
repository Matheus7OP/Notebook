/*
 * Matheus Oliveira
 * 13/04/2018
 * sparseTable.cpp
 *
 * As an example, sparse table of maximum element in a given range
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXL 
#define MAXN 
typedef long long ll;

int lg[MAXN], spt[MAXL][MAXN], v[MAXN], n;

void build() {
	int aux, val;

	for(int i = 1; i <= n; i++) {
		aux = i;
		val = 0;

		while(aux/2 > 0) val++, aux /= 2;
		lg[i] = val;
	}

	for(int i = 0; i < n; i++) spt[0][i] = v[i];

	for(int j = 1; j <= lg[n]; j++) {
		for(int i = 0; (i + (1 << (j-1)) ) < n; i++) {
			spt[j][i] = max(spt[j-1][i], spt[j-1][i + (1 << (j-1))]);
		}
	}
}

int query(int l, int r) {
	int qtdElements = r-l+1;
	return max( spt[ lg[qtdElements] ][l], spt[ lg[qtdElements] ][ r - (1 << lg[qtdElements]) + 1 ] );
}