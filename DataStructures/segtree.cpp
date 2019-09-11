/*
 * Matheus Oliveira
 * 23/08/2018
 * segtree.cpp
 *
 * Using segment tree of maximum (value in a given interval) as an example
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN
typedef long long ll;

ll v[MAXN], stree[4*MAXN];

void build(int id, int l, int r) {
	if(l == r) {
		stree[id] = v[l];
		return;
	}

	int m = (l+r) >> 1;
	
	build(id*2, l, m);
	build(id*2+1, m+1, r);

	stree[id] = max(stree[id*2], stree[id*2+1]);
}

void update(int id, int l, int r, int index) {
	if(l == r) {
		stree[id] = v[l];
		return;
	}

	int m = (l+r) >> 1;

	if(index <= m) update(id*2, l, m, index);
	else update(id*2+1, m+1, r, index);

	stree[id] = max(stree[id*2], stree[id*2+1]);
}

ll query(int id, int l, int r, int a, int b) {
	if(l >= a and r <= b) return stree[id];
	if(r < a or l > b) return ((ll) -1);

	int m = (l+r) >> 1;
	return max( query(id*2, l, m, a, b), query(id*2+1, m+1, r, a, b) );
}