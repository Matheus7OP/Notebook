/*
 * Matheus Oliveira
 * 08/01/2018
 * trie2.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 100000

struct TrieNode {
	map<char, TrieNode> children;
	bool endOfWord;
};

TrieNode root;

void inicialize(TrieNode& node) {
	node.endOfWord = false;
	node.children.clear();
}

void insertWord(TrieNode& actual, string word, int index) {
	if( index == word.size() ) {
		actual.endOfWord = true;
		return;
	}

	char c = word[index];
	TrieNode node;

	if( actual.children.count(c) == 0 ) {
		inicialize(node);
		actual.children[c] = node;
	}
	
	insertWord( actual.children[c], word, index+1 );
}

bool wordInTrie(TrieNode& actual, string word, int index) {
	if( index == word.size() ) return actual.endOfWord;

	char c = word[index];
	if( actual.children.count(c) == 0 ) return false;
	
	return wordInTrie( actual.children[c], word, index + 1 );
}

int main() {
	inicialize(root);

	int n;
	char op;
	string word;

	cin >> n;

	for(int i = 0; i < n; i++) {
		cin >> op;

		if(toupper(op) == 'I') {
			cin >> word;
			insertWord(root, word, 0);

			cout << "Word >" << word << "< inserted in the Trie structure." << endl;
		}
		else {
			cin >> word;
			if( wordInTrie(root, word, 0) ) cout << ">" << word << "< is in our Trie!" << endl;
			else cout << "The word >" << word << "< is not in our Trie." << endl; 
		}
	}

	return 0;
}