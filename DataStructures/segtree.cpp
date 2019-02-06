/*
 * Matheus Oliveira
 * 23/08/2018
 * segtree.cpp
 *
 * Using segment tree of maximum value in the interval as an example
*/

#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-9
#define INF 2e10
#define MAXN 201110
#define pb(a) push_back(a)
#define mp(a, b) make_pair(a, b)
#define debug(x) printf("%s: %d\n", #x, x);
#define debugarr(x, ini, fim) printf("%s: ", #x); for(int i = ini; i <= fim; i++) printf("%d%c", x[i], i == fim ? '\n' : ' ');
typedef long long ll;
typedef pair<int, int> P;

ll elements[MAXN], segtree[4*MAXN];

void build(int id, int left, int right) {
	if(left == right) {
		segtree[id] = elements[left];
		return;
	}

	int mid = (left + right)/2;
	
	build(id*2, left, mid);
	build(id*2+1, mid+1, right);

	segtree[id] = max(segtree[id*2], segtree[id*2+1]);
}

void update(int id, int left, int right, int index) {
	if(left == right) {
		segtree[id] = elements[left];
		return;
	}

	int mid = (left + right)/2;

	if(index <= mid) update(id*2, left, mid, index);
	else update(id*2+1, mid+1, right, index);

	segtree[id] = max(segtree[id*2], segtree[id*2+1]);
}

ll query(int id, int left, int right, int a, int b) {
	if(left >= a and right <= b) return segtree[id];
	if(right < a or left > b) return ((ll) -1);

	int mid = (left+right)/2;
	return max( query(id*2, left, mid, a, b), query(id*2+1, mid+1, right, a, b) );
}