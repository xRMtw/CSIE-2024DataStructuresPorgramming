#include <iostream>
#include <string>
#include<queue>

using namespace std;

template<class T>
class BinarySearchTree {
    
    private:

        struct Node {
            T data;
            Node *left, *right;
        };
        
        void inorder(Node *cur) {
            if(!cur) return;

            inorder(cur->left);
            cout << cur->data << " ";
            inorder(cur->right);

        }

        Node *root;

    public:

        BinarySearchTree() : root(nullptr) {}

        void insertElement(T d) {
            
            Node *newNode = new Node();
            newNode->data = d;

            if( root == nullptr ) {
                root = newNode;
                return;
            }

            queue<Node*> save;
            save.push( root );
            
            while ( !save.empty() ) {

                Node* temp = save.front();
                save.pop();
                
                if( temp->left == nullptr ) {
                    temp->left = newNode;
                    return;
                }
                else {
                    save.push( temp->left );
                }

                if( temp->right == nullptr ) {
                    temp->right = newNode;
                    return;
                }
                else {
                    save.push( temp->right );
                }

            }
            
        }

        void print() {
            inorder(root);
            cout << endl;
        }

        bool search(T d) {
            Node* Searching = root;
            while ( Searching != nullptr ) {
                if ()
            }

        }

        int height() {
        }

};

int main() {

    int data;
    string command;
    BinarySearchTree<int> *bst = new BinarySearchTree<int>();
    
    while(true) {
        cin >> command;

        if(command == "insert") {
            cin >> data;
            bst->insertElement(data);
        }

        else if(command == "search") {
            cin >> data;

            if(bst->search(data))
                cout << "true" << endl;
            else
                cout << "false" << endl;
        }

        else if(command == "height") {
            cout << bst->height() << endl;
        }

        else if(command == "print") {
            bst->print();
        }

        else if(command == "exit") {
            break;
        }

    }
}
