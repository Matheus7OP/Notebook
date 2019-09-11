/*
 * Matheus Oliveira
 * 07/11/2017
 * Fenwick Tree (Binary Indexed Tree) 1d
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN
int fenwick[MAXN];

void update(int idx, int val) {
	while(idx < MAXN) {
		fenwick[idx] += val;
		idx += idx & (-idx);
	}
}

int read(int idx) {
	int sum = 0;
	while(idx > 0) {
		sum += fenwick[idx];
		idx -= idx & (-idx);
	}
	return sum;
}