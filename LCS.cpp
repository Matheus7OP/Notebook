int lcs(int i, int j, int tam1, int tam2) {
	int k, w;

	for(k=0; k <= tam1; k++) {
		for(w=0; w <= tam2; w++) {
			if( k == 0 or w == 0 ) dp[k][w] = 0;
			else {
				if( ar1[i][k-1] == ar1[j][w-1] ) dp[k][w] = dp[k-1][w-1] + 1;
				else dp[k][w] = max( dp[k-1][w], dp[k][w-1] );
			}
		}
	}

	return dp[tam1][tam2];
}