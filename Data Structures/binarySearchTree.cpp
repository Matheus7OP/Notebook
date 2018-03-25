/*
 * Matheus Oliveira
 * 25/03/2018
 * binarySearchTree.cpp
 *
 * Implementação de BST simples. Possível realizar percursos
 * prefixo, infixo, posfixo, inserir elementos e pesquisar elementos. 
*/
 
#include <bits/stdc++.h>
using namespace std;

struct Node {
	char valor;
	map<int, Node> filhos;

	bool operator==(Node &node) {
		return (this->valor == node.valor);
	}
};

Node vazio, root;
string ans;

bool isNull(Node &node) {
	return (node.valor == '!');
}

void inicializar(Node &node, char val) {
	node.valor = val;
	node.filhos[1] = vazio;
	node.filhos[2] = vazio;
}

void insere(Node &nodeAtual, char val) {
	if(nodeAtual.valor == '!') {
		nodeAtual.valor = val;
		return;
	}

	bool isGreater = val > nodeAtual.valor;

	if(isGreater) {
		if( isNull(nodeAtual.filhos[2]) ) {
			inicializar(nodeAtual.filhos[2], val);
			return;
		}
		else {
			insere(nodeAtual.filhos[2], val);
			return;
		}
	}
	else {
		if( isNull(nodeAtual.filhos[1]) ) {
			inicializar(nodeAtual.filhos[1], val);
			return;
		}
		else {
			insere(nodeAtual.filhos[1], val);
			return;
		}
	}
}

void prefixa(Node &node) {
	ans += node.valor;
	if( !( isNull(node.filhos[1]) ) ) prefixa(node.filhos[1]);
	if( !( isNull(node.filhos[2]) ) ) prefixa(node.filhos[2]);
}

void infixa(Node &node) {
	if( !( isNull(node.filhos[1]) ) ) infixa(node.filhos[1]);
	ans += node.valor;
	if( !( isNull(node.filhos[2]) ) ) infixa(node.filhos[2]);
}

void posfixa(Node &node) {
	if( !( isNull(node.filhos[1]) ) ) posfixa(node.filhos[1]);
	if( !( isNull(node.filhos[2]) ) ) posfixa(node.filhos[2]);
	ans += node.valor;
}

bool isInTree(Node &node, char val) {
	if(node == vazio) return false;
	if(val == node.valor) return true;

	bool isGreater = val > node.valor;

	if(isGreater) return isInTree(node.filhos[2], val);
	else return isInTree(node.filhos[1], val);
}

int main() {
	ios::sync_with_stdio(false);
	string operacao;
	char c;

	vazio.valor = '!';
	inicializar(root, '!');

	while(cin >> operacao) {
		if(operacao == "I") {
			cin >> c;
			insere(root, c);
		}

		if(operacao == "P") {
			cin >> c;
			if( isInTree(root, c) ) cout << c << " existe" << endl;
			else cout << c << " nao existe" << endl;
		}

		if(operacao == "PREFIXA") {
			ans = "";
			prefixa(root);

			for(int i = 0; i < ((int) ans.size()); i++) {
				if(i == 0) cout << ans[i];
				else cout << " " << ans[i];
			}
			
			cout << endl;
		}

		if(operacao == "INFIXA") {
			ans = "";
			infixa(root);

			for(int i = 0; i < ((int) ans.size()); i++) {
				if(i == 0) cout << ans[i];
				else cout << " " << ans[i];
			}
			
			cout << endl;
		}

		if(operacao == "POSFIXA") {
			ans = "";
			posfixa(root);

			for(int i = 0; i < ((int) ans.size()); i++) {
				if(i == 0) cout << ans[i];
				else cout << " " << ans[i];
			}
			
			cout << endl;
		}
	}

	return 0;
}