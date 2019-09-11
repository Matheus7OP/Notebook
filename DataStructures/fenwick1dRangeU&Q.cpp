/*
 * Matheus Oliveira
 * 23/08/2017
 * Fenwick Tree 1d (trick to do range update and query)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN
typedef long long ll;

ll ft[MAXN], ft2[MAXN];

void update(ll ft[], ll index, ll value) {
	while(index < MAXN) {
		ft[index] += value;
		index += index & (-index);
	}
}

void range_update(ll l, ll r, ll value) {
	update(ft, l, value);
	update(ft, r+1, -value);

	update(ft2, l, value*(l-1) );
	update(ft2, r+1, -value*r );
}

ll read(ll ft[], ll index) {
	ll sum = 0;
	while(index > 0) {
		sum += ft[index];
		index -= index & (-index);
	}
	return sum;
}

ll get_sum(ll index) { return ( read(ft, index) * index ) - read(ft2, index); }
ll ans(ll l, ll r) { return get_sum(r) - get_sum(l-1); }