/*
 * Matheus Oliveira
 * 23/08/2017
 * 1500.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 100010
typedef long long ll;

ll elements;
ll fenwick[MAXN], ft2[MAXN];

void update(ll fenwick[], ll index, ll value) {
	while(index <= elements+1) {
		fenwick[index] += value;
		index += index & (-index);
	}
}

void range_update(ll l, ll r, ll value) {
	update(fenwick, l, value);
	update(fenwick, r+1, -value);

	update(ft2, l, value*(l-1) );
	update(ft2, r+1, -value*r );
}

ll read(ll fenwick[], ll index) {
	ll sum = 0;

	while(index > 0) {
		sum += fenwick[index];
		index -= index & (-index);
	}

	return sum;
}

ll get_sum(ll index) {
	return ( read(fenwick, index) * index ) - read(ft2, index);
}

ll ans(ll l, ll r) {
	return get_sum(r) - get_sum(l-1);
}