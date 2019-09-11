/*
 * Matheus Oliveira
 * 13:17:44 02/05/2019
 * lagrangeOpt.cpp
 *
 * See if there is a way to fix a value for some of the variables, then checking the answer
 * for the other one would be done by a simple dp. Depending on this value, (the function needs to be monotonic),
 * see if it is better to increase or decrease the value of the first mentioned variable (use binary search).
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 
#define EPS 1e-9
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double, int> pdi;

int n;
bool vis[MAXN][MAXN];

pdi dp[MAXN][MAXN];
double pa[MAXN], pb[MAXN], pab[MAXN], cost;

pdi solve2(int pos, int a) {
	if(pos >= n) return mp(0.0, 0);
	if(vis[pos][a]) return dp[pos][a];

	double ans = solve2(pos+1, a).first;
	int qtdB = solve2(pos+1, a).second;

	if( (solve2(pos+1, a).first + pb[pos] - cost) > ans ) {
		ans = solve2(pos+1, a).first + pb[pos] - cost;
		qtdB = solve2(pos+1, a).second + 1;
	}

	if(a > 0) {
		if( (solve2(pos+1, a-1).first + pa[pos]) > ans ) {
			ans = solve2(pos+1, a-1).first + pa[pos];
			qtdB = solve2(pos+1, a-1).second;
		}

		if( (solve2(pos+1, a-1).first + pab[pos] - cost) > ans ) {
			ans = solve2(pos+1, a-1).first + pab[pos] - cost;
			qtdB = solve2(pos+1, a-1).second + 1;
		}
	}

	vis[pos][a] = true;
	return dp[pos][a] = mp(ans, qtdB);
}

double solve(int a, int b) {
	register int i, j;
	int limit = 31, qtdB;
	double left = 0.0, mid, right = 1.0, ans;

	while(limit--) {
		mid = (left + right) / 2.0;
		
		for(i = 0; i <= n; i++) {
			for(j = 0; j <= a; j++) vis[i][j] = false;
		}

		cost = mid;
		qtdB = solve2(0, a).second;

		if(qtdB <= b) right = mid;
		else left = mid;
	}

	for(i = 0; i <= n; i++) {
		for(j = 0; j <= a; j++) vis[i][j] = false;
	}

	cost = right;
	ans = solve2(0, a).first + ((double) solve2(0, a).second) * cost;
	return ans;
}

int main() {
	int a, b;

	scanf("%d %d %d", &n, &a, &b);
	for(int i = 0; i < n; i++) scanf("%lf", &pa[i]);
	
	for(int i = 0; i < n; i++) {
		scanf("%lf", &pb[i]);
		pb[i] -= EPS * ((double) i);
	}

	for(int i = 0; i < n; i++) pab[i] = pa[i] + (1.0 - pa[i]) * pb[i];
	printf("%.17f\n", solve(a, b));
	
	return 0;
}