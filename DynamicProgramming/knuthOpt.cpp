/*
 * Matheus Oliveira
 * 13:48:57 14/05/2019
 * knuthOpt.cpp
 *
 * Knuth Optimization for Dynamic Programming. Overall it reduces time complexity from O(k^3) to O(k^2)
 * It is applicable in the case where recurrence is in the form: dp[i][j] = mini < k < j{dp[i][k] + dp[k][j]} + C[i][j]
 * The sufficient condition for applicability is: A[i, j - 1] ≤ A[i, j] ≤ A[i + 1, j]
 * Where: A[i][j] — the smallest k that gives optimal answer, for example in:
 * dp[i][j] = dp[i - 1][k] + C[k][j]
 * C[i][j] — given cost function
 * Also, it's important to note that Knuth Optimization is applicable if: C[i][j] satisfies the following 2 conditions:
 * quadrangle inequality, monotonicity:
*/
 
#include <bits/stdc++.h>
using namespace std;
 
#define INF 
#define MAXN 
 
typedef long long ll;
typedef pair<int, int> pii;
 
ll dp[MAXN][MAXN];
int n, m, bp[MAXN], opt[MAXN][MAXN];

int main() {
	ll cost, cl, cr;
	int l, r, optl, optr;

	while( scanf("%d %d", &n, &m) != EOF ) {
		for(int i = 0; i <= m; i++) {
			for(int j = 0; j <= m; j++) dp[i][j] = INF;
		}
		for(int i = 0; i < m; i++) scanf("%d", &bp[i]);
 		
 		// example problem: breaking strings. Cost of breaking: size of actual string. 
		// what is the minimal cost to make all of the breaking bp[i]?
		for(int g = 1; g <= m; g++) {
			for(int i = 0; i < m; i++) {
				l = i, r = i + g - 1;
				if(r >= m) break;
 
				cost = n;
				if(r < m-1) cost -= ((ll) n - bp[r+1]);
				if(l > 0) cost -= ((ll) bp[l-1]);
 
				if( g == 1 ) dp[l][r] = cost, opt[l][r] = l;
				else {
					optl = opt[l][r-1];
					optr = opt[l+1][r];
 
					for(int j = optl; j <= optr; j++) {
						cl = cr = 0LL;
 
						if(j-1 >= l) cl = dp[l][j-1];
						if(j+1 <= r) cr = dp[j+1][r];
 
						if( cl + cost + cr < dp[l][r] ) {
							opt[l][r] = j;
							dp[l][r] = cl + cost + cr;
						}
					}
				}
			}
		}
		
		printf("%lld\n", dp[0][m-1]);
	}
 
	return 0;
}