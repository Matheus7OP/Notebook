/*
 * Matheus Oliveira
 * 07/11/2017
 * segtree+lazy.cpp
 *
 * Using segment tree to store and update (using 'lazy' technique) sum of intervals
 * Range update is done in O(logn) 
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN
typedef long long ll;

ll stree[MAXN*4], v[MAXN], lazy[MAXN*4];

void build(int id, int l, int r) {
	lazy[id] = 0;

	if(l == r) {
		stree[id] = v[l];
		return;
	}

	int m = (l+r) >> 1;

	build(id*2, l, m);
	build(id*2+1, m+1, r);

	stree[id] = stree[id*2] + stree[id*2+1];
}

void doLazy(int id, int l, int r) {
	stree[id] += (r-l+1) * lazy[id];

	if(l != r) {
		lazy[id*2] += lazy[id];
		lazy[id*2+1] += lazy[id];
	}
	
	lazy[id] = 0;
}

void update(int id, int l, int r, int a, int b, ll val) {
	if(lazy[id] != 0) doLazy(id, l, r);
	if(r < a or l > b) return;

	if(l >= a and r <= b) {
		stree[id] += (r-l+1) * val;

		if(l != r) {
			lazy[id*2] += val;
			lazy[id*2+1] += val;
		}

		return;
	}

	int m = (l+r) >> 1;

	update(id*2, l, m, a, b, val);
	update(id*2+1, m+1, r, a, b, val);

	stree[id] = stree[id*2] + stree[id*2+1];
}

ll query(int id, int l, int r, int a, int b) {
	if(r < a or l > b) return 0;
	if(lazy[id] != 0) doLazy(id, l, r);
	if(l >= a and r <= b) return stree[id];

	int m = (l+r) >> 1;
	return query(id*2, l, m, a, b) + query(id*2+1, m+1, r, a, b);
}