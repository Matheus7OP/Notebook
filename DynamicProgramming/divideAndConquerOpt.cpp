/*
 * Matheus Oliveira
 * 11:00:19 16/05/2019
 * divideAndConquerOpt.cpp
 *
 * We can apply the divide and conquer optimization in cases we find a recurrence of this form: 
 * dp(i,j) = min(dp(i−1, k) + C(k, j)), k <= j and C(k, j) is some cost function
 * Straightforward evaluation of the above recurrence would be O(n * m^2).
 * We optimize it to be O(n * m * logn)
 * The greatest difficulty with Divide and Conquer DP problems is proving the monotonicity of opt, so remember
 * to build opt table for some cases previously, if possible, and check for monotonicity before coding the full solution
*/

#include <bits/stdc++.h>
using namespace std;

#define INF 
#define MAXK 
#define MAXN 

typedef long long ll;
typedef pair<int, int> pii;

int val[MAXN], n, g, opt[MAXK][MAXN];
double dp[MAXK][MAXN], prefixAns[MAXN], prefixSum[MAXN], prefixSumInv[MAXN];

// returns the cost of a given interval (normally in O(1))
double cost(int i, int j) {
	assert(j >= i);

	double ret = prefixAns[j];
	if(i > 0) ret -= prefixAns[i-1] + prefixSum[i-1] * (prefixSumInv[j] - prefixSumInv[i-1]);
	
	return ret;
}

// example problem: dividing N levels into K regions and getting min cost/time by doing this
void solve(int k, int l, int r, int optl, int optr) {
	if(l > r) return;

	double ans = INF;
	int mid = (l + r) >> 1;

	if(k == 1) ans = cost(mid, n-1);
	else {
		for(int i = max(mid, optl); i <= optr; i++) {
			if(ans > dp[k-1][i+1] + cost(mid, i) ) {
				opt[k][mid] = i;
				ans = dp[k-1][i+1] + cost(mid, i);
			}	
		}
	}

	dp[k][mid] = ans;
	solve(k, l, mid-1, optl, opt[k][mid]);
	solve(k, mid+1, r, opt[k][mid], optr);
}

int main() {
	double acc = 0.0;
	scanf("%d %d", &n, &g);

	for(int i = 0; i < n; i++) {
		scanf("%d", &val[i]);

		prefixSum[i] = val[i];
		prefixSumInv[i] = 1.0/((double) val[i]);

		if(i > 0) {
			prefixSum[i] += prefixSum[i-1];
			prefixSumInv[i] += prefixSumInv[i-1];
		}
	}

	acc = val[0], prefixAns[0] = 1.0;
	for(int i = 1; i < n; i++) {
		prefixAns[i] = prefixAns[i-1];
		
		prefixAns[i] += acc / ((double) val[i]) + 1.0;
		acc += (double) val[i];
	}

	for(int k = 1; k <= g; k++) solve(k, 0, n-1, 0, n-1);
	printf("%.17f\n", dp[g][0]);
	
	return 0;
}