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

#define MAXN 100010
typedef long long ll;

ll stree[MAXN*4], v[MAXN], lazy[MAXN*4];

void build(int id, int l, int r) {
	lazy[id] = 0;

	if(l == r) {
		stree[id] = v[l];
		return;
	}

	int mid = (l+r) >> 1;

	build(id*2, l, mid);
	build(id*2+1, mid+1, r);

	stree[id] = stree[id*2] + stree[id*2+1];
}

void rangeUpdate(int id, int l, int r, int a, int b, ll value) {
	if(lazy[id] != 0) {
		stree[id] += (r-l+1) * lazy[id];

		if(l != r) {
			lazy[id*2] += lazy[id];
			lazy[id*2+1] += lazy[id];
		}
		
		lazy[id] = 0;
	}

	if(r < a or l > b) return;

	if(l >= a and r <= b) {
		stree[id] += (r-l+1) * value;

		if(l != r) {
			lazy[id*2] += value;
			lazy[id*2+1] += value;
		}

		return;
	}

	int mid = (l+r) >> 1;

	rangeUpdate(id*2, l, mid, a, b, value);
	rangeUpdate(id*2+1, mid+1, r, a, b, value);

	stree[id] = stree[id*2] + stree[id*2+1];
}

ll query(int id, int l, int r, int a, int b) {
	if(r < a or l > b) return 0;

	if(lazy[id] != 0) {
		stree[id] += (r-l+1) * lazy[id];

		if(l != r) {
			lazy[id*2] += lazy[id];
			lazy[id*2+1] += lazy[id];
		}

		lazy[id] = 0;
	}

	if(l >= a and r <= b) return stree[id];

	int mid = (l+r) >> 1;
	return query(id*2, l, mid, a, b) + query(id*2+1, mid+1, r, a, b);
}