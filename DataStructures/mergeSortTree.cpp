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

#define MAXN 100100

int elements[MAXN];
vector<int> mstree[MAXN * 4];

void build(int id, int left, int right) {
	if(left == right) mstree[id].pb( elements[left] );
	else {
		int mid = (left + right) >> 1;

		build(id*2, left, mid);
		build(id*2+1, mid+1, right);

		merge(mstree[id*2].begin(), mstree[id*2].end(),
			mstree[id*2+1].begin(), mstree[id*2+1].end(),
			back_inserter(mstree[id]));
	}
}

// returns how many elements are less than or equal to 'val'
int query(int id, int left, int right, int a, int b, int val) {
	if(b < left or a > right) return 0;
	if(left >= a and right <= b) {
		return upper_bound(mstree[id].begin(), mstree[id].end(), val) - mstree[id].begin();
	}

	int mid = (left + right) >> 1;
	return query(id*2, left, mid, a, b, val) + query(id*2 + 1, mid+1, right, a, b, val);
}
