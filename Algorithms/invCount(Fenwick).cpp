/*
 * Matheus Oliveira
 * 14/04/2018
 * invCount(Fenwick).cpp
 * Contando número de inversões usando Fenwick Tree (BIT)
*/

#include <bits/stdc++.h>
using namespace std;

#define INF 2e9
#define MAXN 200010
#define MAXVAL 10000010
typedef long long ll;

int elements[MAXN];

ll read(ll fenwick[], int index) {
	ll qtdElem = 0;
	while(index > 0) {
		qtdElem += fenwick[index];
		index -= index & (-index);
	}
	return qtdElem;
}

void update(ll fenwick[], int index, int val, int maxElem) {
	while(index <= maxElem) {
		fenwick[index] += val;
		index += index & (-index);
	}
}

ll solve(int n, int maxElem) {
	ll fenwick[maxElem+5], counter = 0;
	memset(fenwick, 0, sizeof fenwick);

	for(int i = n; i >= 1; i--) {
		counter += read(fenwick, elements[i]-1);
		update(fenwick, elements[i], 1, maxElem);
	}

	return counter;
}

int main() {
	int noCases, maxElem, n;
	scanf("%d", &noCases);

	while(noCases--) {
		scanf("%d", &n);

		maxElem = -INF;
		for(int i = 1; i <= n; i++) {
			scanf("%d", &elements[i]);
			maxElem = max(maxElem, elements[i]);
		}

		printf("%lld\n", solve(n, maxElem));
	}

	return 0;
}