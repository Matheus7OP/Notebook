/*
 * Matheus Oliveira
 * 13:15:18 17/02/2019
 * mergeSortTree.cpp
 *
 * Answers in O(log²n) queries of type "how many elements are less than or equal to k" in a given interval
 * Takes O(n) time to build.
 *
 * P.S.: It is possible to make point updates =)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN

int elements[MAXN];
vector<int> mstree[MAXN * 4];

void build(int id, int l, int r) {
	if(l == r) mstree[id].pb( elements[l] );
	else {
		int mid = (l + r) >> 1;

		build(id*2, l, mid);
		build(id*2+1, mid+1, r);

		merge(mstree[id*2].begin(), mstree[id*2].end(),
			mstree[id*2+1].begin(), mstree[id*2+1].end(),
			back_inserter(mstree[id]));
	}
}

// returns how many elements are less than or equal to 'val'
int query(int id, int l, int r, int a, int b, int val) {
	if(b < l or a > r) return 0;
	if(l >= a and r <= b) {
		return upper_bound(mstree[id].begin(), mstree[id].end(), val) - mstree[id].begin();
	}

	int mid = (l + r) >> 1;
	return query(id*2, l, mid, a, b, val) + query(id*2 + 1, mid+1, r, a, b, val);
}
