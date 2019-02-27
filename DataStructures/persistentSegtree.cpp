/*
 * Matheus Oliveira
 * 17:26:07 27/02/2019
 * persistentSegtree.cpp
 * 
 * Does everything that a normal segment tree does, but allocates memory dynamically; that way
 * we can represent and operate in very large intervals, up to ~[-1e18, 1e18] AND is persistent
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXR 20000000
#define MAXN 1000000000000000000

typedef long long ll;
typedef pair<int, int> pii;

struct Node {
	ll sum, lazy;
	Node *left, *right;
	Node() : sum(0), lazy(0), left(NULL), right(NULL) {}
	// REMEMBER to deallocate nodes to avoid memory leak in problems with more than one test case
} *roots[MAXR];

int version;

void checkSons(Node *node) {
	if( node->left == NULL ) node->left = new Node();
	if( node->right == NULL ) node->right = new Node();
}

int getSum(Node *node) {
	if(node == NULL) return 0;
	return node->sum;
}

void update(Node *lastVersion, Node *node, ll l, ll r, ll idx, ll val) {
	if( l == r and idx == r ) {
		node->sum += val;
		return;
	}

	ll mid = l + ((r - l) >> 1);
	
	checkSons(lastVersion);
	checkSons(node);

	if(idx <= mid) {
		node->right = lastVersion->right;

		node->left = new Node();
		(node->left)->sum = getSum(lastVersion->left);

		update(lastVersion->left, node->left, l, mid, idx, val);
	}
	else {
		node->left = lastVersion->left;

		node->right = new Node();
		(node->right)->sum = getSum(lastVersion->right);

		update(lastVersion->right, node->right, mid+1, r, idx, val);	
	}

	node->sum = getSum(node->left) + getSum(node->right);
}

ll query(Node *node, ll l, ll r, ll a, ll b) {
	if( b < l or a > r ) return 0;
	if( l >= a and r <= b ) return node->sum;

	ll mid = l + ((r-l) >> 1), s1, s2;
	s1 = s2 = 0;

	if( node->left ) s1 = query(node->left, l, mid, a, b);
	if( node->right ) s2 = query(node->right, mid+1, r, a, b);

	return (s1 + s2);
}

int main() {
	roots[version++] = new Node();
	
	ll l, r, val, idx;
	int queriedTime, op;

	while(true) {
		// 1 -> add
		// 2 -> query

		scanf("%d", &op);
		if(op == 1) {
			scanf("%lld %lld", &idx, &val);

			roots[version] = new Node();
			roots[version]->sum = roots[version-1]->sum;

			update(roots[version-1], roots[version], 1, MAXN, idx, val);
			version++;
		}
		else {
			scanf("%lld %lld %d", &l, &r, &queriedTime);
			printf("%lld\n", query(roots[queriedTime], 1, MAXN, l, r));
		}
	}

	return 0;
}