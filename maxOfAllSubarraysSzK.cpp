/*
 * Matheus Oliveira
 * 16/01/2018
 * 1594.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000010

typedef long long ll;
ll elementos[MAXN];

int main() {
	int casos, p1, p2, i;
	ll n, k, s, ans;
	deque<int> dq;

	scanf("%d", &casos);

	while(casos--) {
		scanf("%lld %lld %lld", &n, &k, &s);

		elementos[0] = s;
		for (i = 1; i < n; ++i) elementos[i] = (1 * elementos[i-1] * 1103515245 + 12345) % (2147483648);

		while(not dq.empty()) dq.pop_back();
		ans = 0;

		for(i=0; i < k; i++) {
			while( (not dq.empty()) and elementos[i] >= ( elementos[dq.back()] ) ) dq.pop_back();
			dq.push_back(i);
		}

		for(; i < n; i++) {
			ans += elementos[dq.front()];

			// removo todos os que não fazem parte dessa janela e que possivelmente seriam envolvidos
			// no somatório (erroneamente) caso não fossem removidos agora
			while( (not dq.empty()) and dq.front() <= (i-k) ) dq.pop_front();

			// removo todos os elementos que inúteis; isso é, quando 'tiverem chance' de ser úteis,
			// o elemento atual que estou a adicionar será usado instead. No point on keeping them, then.
			while( (not dq.empty()) and elementos[i] >= ( elementos[dq.back()] ) ) dq.pop_back();

			dq.push_back(i);
		}

		ans += elementos[dq.front()];
		printf("%lld\n", ans);
	}

	return 0;
}