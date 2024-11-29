#include<bits/stdc++.h>

using namespace std;

class Trie
{
	private:

		class Node {
			public:
				Node() {
					depth = 0;
					is_word = false;
					child = unordered_map<char , Node*>();
				}

				Node( int d ) : depth(d) {
					
					is_word = false;
					child = unordered_map<char , Node*>();
				}

				~Node() {
					for ( pair<char, Node*> pair : child ) {
						delete pair.second;
					}
				}

				int depth;
				bool is_word;
				unordered_map<char , Node*> child;
		};

		Node *root;

		void doPreoder ( Node *p ) {
			
			if ( !p ) return;
			for ( auto & pair : p->child ) {
				int t = p->depth;
				while ( t ) {
					cout << " ";
					t--;
				}
				cout << pair.first << endl;
				doPreoder( pair.second );
			}

		}

	public:
		/*
		construct a Trie.
		*/
		Trie() {
			root = new Node();
		}
		/*
		search trie for key, return true if exist, false if not.
		*/
		bool search(string key) {
			Node* n = root;
			for (char c : key) {
				if (n->child.find(c) == n->child.end()) {
					return false;
				}
				n = n->child[c];
			}
			return n->is_word;

		}
		/*
		insert value into trie.
		*/
		void insert(string value) {
			Node* n = root;
			for (char c : value) {
				if (n->child.find(c) == n->child.end()) {
					n->child[c] = new Node(n->depth + 1);
				}
				n = n->child[c];
			}
			n->is_word = true;
		}
		/*
		display trie in pre-order, each element in a line, display space befoer element base on the level of the element. level 1 for 2 space, level 2 for 4 space, level 3 for 6 space and so on, root is level 0.
		*/
		void preorder( ) {

			doPreoder( root );

		}

};

int main()
{
	Trie *trie = new Trie();
	string command, key, value;
	while(1)
	{
		cin>>command;
		if(command == "insert")
		{
			cin>>value;
			trie->insert(value);
		}
		else if(command == "search")
		{
			cin>>key;
			if(trie->search(key))
				cout << "exist" << endl;
			else
				cout << "not exist" << endl;
		}
		else if(command == "print")
		{
			trie->preorder();
		}
		else if(command == "exit")
		{
			break;
		}
	}
}
