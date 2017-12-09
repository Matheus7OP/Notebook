/*
 * Matheus Oliveira
 * 23/08/2017
 * 1500.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 100010
long long int elements;
long long int fenwick[MAXN], ft2[MAXN];

void update(long long int fenwick[], long long int index, long long int value) {

	while(index <= elements+1) {
		fenwick[index] += value;
		index += index & (-index);
	}
}

void range_update(long long int l, long long int r, long long int value) {

	update(fenwick, l, value);
	update(fenwick, r+1, -value);

	update(ft2, l, value*(l-1) );
	update(ft2, r+1, -value*r );
}

long long int read(long long int fenwick[], long long int index) {

	long long int sum = 0;

	while(index > 0) {

		sum += fenwick[index];
		index -= index & (-index);
	}

	return sum;
}

long long int get_sum(long long int index) {

	return ( read(fenwick, index) * index ) - read(ft2, index);
}

long long int ans(long long int l, long long int r) {

	return get_sum(r) - get_sum(l-1);
}

int main () {

	int casos, i, j, o, ops;
	long long int value, p, q, l, r;

	scanf("%d", &casos);

	for(i=0; i < casos; i++) {

		scanf("%lld %d", &elements, &ops);

		memset(fenwick, 0, sizeof(fenwick));
		memset(ft2, 0, sizeof(ft2));

		for(j=0; j < ops; j++) {

			scanf("%d %lld %lld", &o, &p, &q);

			l = min(p, q);
			r = max(p, q);

			if(o == 0) {
				scanf("%lld", &value);
				range_update(l, r, value);
			}

			else {
				// ler valor em range
				printf("%lld\n", ans(l, r));
			}
		}
	}

	return 0;
}