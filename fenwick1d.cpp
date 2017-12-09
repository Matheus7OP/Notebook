/*
 * Matheus Oliveira
 * 07/11/2017
 * 1804.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 100010
int fenwick[MAXN], n;

void update(int index, int val) {
	while(index <= n) {
		fenwick[index] += val;
		index += index & (-index);
	}
}

int getSum(int index) {
	int sum = 0;

	while(index > 0) {
		sum += fenwick[index];
		index -= index & (-index);
	}

	return sum;
}

int main() {
	int i, aux, index, elementos[MAXN];
	char op;

	scanf("%d", &n);
	getchar();

	for(i=1; i <= n; i++) {
		scanf("%d", &elementos[i]);
		getchar();
	}

	for(i=1; i <= n; i++) update(i, elementos[i]);

	while(scanf("%c %d", &op, &index) != EOF) {
		getchar();
		if(op == '?') {
			printf("%d\n", getSum(index-1));
		}
		else {
			update(index, -elementos[index]);
			elementos[index] = 0;
		}
	}

	return 0;
}