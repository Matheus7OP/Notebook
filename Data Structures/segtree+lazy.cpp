/*
 * Matheus Oliveira
 * 07/11/2017
 * 1500_st.cpp
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long int lli;
#define MAXN 100010

long long int segtree[MAXN*4], elementos[MAXN], lazy[MAXN*4];

void build(int id, lli left, lli right) {
	lazy[id] = 0;

	if(left == right) {
		segtree[id] = elementos[left];
		return;
	}

	lli mid = (left+right)/2;

	build(id*2, left, mid);
	build(id*2+1, mid+1, right);

	segtree[id] = segtree[id*2] + segtree[id*2+1];
}

void rangeUpdate(int id, int left, int right, lli a, lli b, lli value) {
	if(lazy[id] != 0) {
		segtree[id] += (right-left+1) * lazy[id];

		if(left != right) {
			lazy[id*2] += lazy[id];
			lazy[id*2+1] += lazy[id];
		}
		
		lazy[id] = 0;
	}

	if(right < a or left > b) return;

	if(left >= a and right <= b) {
		segtree[id] += (right-left+1) * value;

		if(left != right) {
			lazy[id*2] += value;
			lazy[id*2+1] += value;
		}

		return;
	}

	int mid = (left+right)/2;

	rangeUpdate(id*2, left, mid, a, b, value);
	rangeUpdate(id*2+1, mid+1, right, a, b, value);

	segtree[id] = segtree[id*2] + segtree[id*2+1];
}

lli query(int id, int left, int right, lli a, lli b) {
	if(right < a or left > b) return 0;

	if(lazy[id] != 0) {
		segtree[id] += (right-left+1) * lazy[id];

		if(left != right) {
			lazy[id*2] += lazy[id];
			lazy[id*2+1] += lazy[id];
		}

		lazy[id] = 0;
	}

	if(left >= a and right <= b) return segtree[id];

	int mid = (left+right)/2;
	return query(id*2, left, mid, a, b) + query(id*2+1, mid+1, right, a, b);
}

int main() {
	int casos, queries, i, numeros, op;
	lli left, right, value, a1, a2;

	scanf("%d", &casos);

	while(casos--) {
		scanf("%d %d", &numeros, &queries);

		for(i=1; i <= numeros; i++) elementos[i] = 0;
		build(1, 1, numeros);

		for(i=0; i < queries; i++) {
			scanf("%d %lld %lld", &op, &a1, &a2);

			left = min(a1, a2);
			right = max(a1, a2);

			if(op == 0) {
				scanf("%lld", &value);
				rangeUpdate(1, 1, numeros, left, right, value);
			}
			else printf("%lld\n", query(1, 1, numeros, left, right));
		}
	}

	return 0;
}