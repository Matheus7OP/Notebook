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

ll segtree[MAXN*4], elements[MAXN], lazy[MAXN*4];

void build(int id, int left, int right) {
	lazy[id] = 0;

	if(left == right) {
		segtree[id] = elements[left];
		return;
	}

	int mid = (left+right)/2;

	build(id*2, left, mid);
	build(id*2+1, mid+1, right);

	segtree[id] = segtree[id*2] + segtree[id*2+1];
}

void rangeUpdate(int id, int left, int right, int a, int b, ll value) {
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

ll query(int id, int left, int right, int a, int b) {
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