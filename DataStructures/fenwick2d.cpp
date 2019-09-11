/*
 * Matheus Oliveira
 * 09/11/2017
 * Fenwick Tree 2d
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 
typedef pair<int, int> pii;

int fenwick2d[MAXN][MAXN];

void update(int i, int j, int v) {
	int r = i, c;
	while(r < MAXN) {
		c = j;
		while(c < MAXN) {
			fenwick2d[r][c] += v;
			c += c & (-c); 
		}
		r += r & (-r);
	}
}

// read(r2, c2) - read(r1-1, c2) - read(r2, c1-1) + read(r1-1, c1-1)
int read(int i, int j) {
	int sum = 0, r = i, c;
	while(r > 0) {
		c = j;
		while(c > 0) {
			sum += fenwick2d[r][c];
			c -= c & (-c); 
		}
		r -= r & (-r);
	}
	return sum;
}