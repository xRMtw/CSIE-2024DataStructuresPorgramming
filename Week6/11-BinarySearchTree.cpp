#include <iostream>
#include <string>

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
            
            Node* newNode = new Node();
            newNode->data = d;
            newNode->left = nullptr;
            newNode->right = nullptr;

            if (root == nullptr) {
                root = newNode;
                return;
            }

            Node* cur = root;
            Node* parent = nullptr;

            while ( cur != nullptr ) {

                parent = cur;
                if( d < cur->data ) {

                    cur = cur->left;

                } else if( d > cur->data ) {

                    cur = cur->right;

                } else {
                  
                    delete newNode;
                    return;
                    
                }
            }

            if (d < parent->data) {

                parent->left = newNode;

            } else {

                parent->right = newNode;

            }

        }

        void print() {
            inorder(root);
            cout << endl;
        }

        bool search(T d) {
            Node* Searching = root;
            while ( Searching != nullptr ) {
                
                if ( Searching->data == d ) {
                    return true;
                }
                else if ( Searching->data > d ) {
                    Searching = Searching->left;
                }
                else {
                    Searching = Searching->right;
                }

            }
            return false;

        }

        int height( Node* cur = nullptr ) {
            static bool firts = true;
            if ( firts ) {
                cur = root;
                firts = false;
            }

            if ( cur == nullptr ) return -1;

            int leftHeight = height( cur->left );
            int rightHeight = height( cur->right );

            return 1 + max(leftHeight, rightHeight);

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
