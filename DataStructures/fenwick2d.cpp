/*
 * Matheus Oliveira
 * 09/11/2017
 * 1112.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 1010
typedef pair<int, int> P;

int fenwick2d[MAXN][MAXN], linhas, colunas, limite;

void update(int i, int j, int v) {
	int r = i, c;

	while(r <= limite) {
		c = j;
		while(c <= limite) {
			fenwick2d[r][c] += v;
			c += c & (-c); 
		}

		r += r & (-r);
	}
}

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

int main() {
	int preco, i, j, queries, r, c, v, c1, r1, ans, c2, r2;
	char op;

	P upleft, upright, boleft, boright;
	
	while( scanf("%d %d %d", &colunas, &linhas, &preco) ) {
		getchar();

		if(linhas == 0 and colunas == 0 and preco == 0) break;
		memset(fenwick2d, 0, sizeof(fenwick2d));

		scanf("%d", &queries);
		getchar();

		limite = max(linhas, colunas);

		for(i=0; i < queries; i++) {
			scanf("%c", &op);
			getchar();

			if(op == 'A') {
				scanf("%d %d %d", &v, &r, &c);
				getchar();

				r++, c++;

				update(r, c, v*preco);
			}
			else {
				scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
				getchar();

				r1++, c1++, r2++, c2++;

				if(r1 > r2) swap(r1, r2);
				if(c1 > c2) swap(c1, c2);

				ans = read(r2, c2) - read(r1-1, c2) - read(r2, c1-1) + read(r1-1, c1-1);
				printf("%d\n", ans);
			}
		}

		printf("\n");
	}

	return 0;
}