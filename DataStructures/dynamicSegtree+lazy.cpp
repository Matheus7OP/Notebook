/*
 * Matheus Oliveira
 * 19:34:19 20/02/2019
 * dynamicsegtree.cpp
 * 
 * Does everything that a normal segment tree does, but allocates memory dynamically; that way
 * we can represent and operate in very large intervals, up to ~[-1e18, 1e18]
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000000000000000000
typedef long long ll;
typedef pair<int, int> pii;

struct Node {
	ll sum, lazy;
	Node *left, *right;
	Node() : sum(0), lazy(0), left(NULL), right(NULL) {}
	// REMEMBER to deallocate nodes to avoid memory leak in problems with more than one test case
} *root; // root = new Node();

void doLazy(Node *node, ll l, ll r) {
	node->sum += (r - l + 1LL) * node->lazy;

	if(node->left == NULL) node->left = new Node();
	if(node->right == NULL) node->right = new Node();

	(node->left)->lazy += node->lazy;
	(node->right)->lazy += node->lazy;

	node->lazy = 0LL;
}

void update(Node *node, ll l, ll r, ll a, ll b, ll val) {
	if( node->lazy != 0 ) doLazy(node, l, r);
	if( b < l or a > r ) return;

	if( l >= a and r <= b ) {
		node->sum += (r - l + 1LL) * val;

		if(l != r) {
			if(node->left == NULL) node->left = new Node();
			if(node->right == NULL) node->right = new Node();

			(node->left)->lazy += val;
			(node->right)->lazy += val;
		}

		return;
	}

	ll mid = l + ((r - l) >> 1);
	
	if( node->left == NULL ) node->left = new Node();
	update(node->left, l, mid, a, b, val);

	if( node->right == NULL ) node->right = new Node();
	update(node->right, mid+1, r, a, b, val);	

	ll s1, s2;
	s1 = s2 = 0;

	if( node->left ) s1 = (node->left)->sum;
	if( node->right ) s2 = (node->right)->sum;

	node->sum = s1 + s2;
}

ll query(Node *node, ll l, ll r, ll a, ll b) {
	if( node->lazy != 0 ) doLazy(node, l, r);
	
	if( b < l or a > r ) return 0;
	if( l >= a and r <= b ) return node->sum;

	ll mid = l + ((r-l) >> 1), s1, s2;
	s1 = s2 = 0;

	if( node->left ) s1 = query(node->left, l, mid, a, b);
	if( node->right ) s2 = query(node->right, mid+1, r, a, b);

	return (s1 + s2);
}