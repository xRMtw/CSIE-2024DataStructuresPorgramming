#include <iostream>
#include <cmath>
#include<queue>

using namespace std;

template<class T>
class BinaryTreeInArray {
    private:

        T *array;
        int height;
        int numOfElement;

        void resize(int size) {

            T *temp = new T[numOfElement];
            int j;
            for(j = 0;j < numOfElement;j ++)
                temp[j] = array[j];
            
            delete array;
            array = new T[static_cast<int>(pow(2, height + 1)) - 1];

            for(j = 0;j < numOfElement;j ++)
                array[j] = temp[j];

            height ++;
            delete temp;

        }

    public:
        BinaryTreeInArray() : array(nullptr), height(0), numOfElement(0) {}

        void addElementAsCompleteTree(T data) {

            int cap = pow(2, height) - 1;

            if(numOfElement + 1 > cap)
                resize((cap + 1) * 2 - 1);

            array[numOfElement] = data;
            numOfElement ++;
            
        }

        void displayInorder( int index = 0 ) {
            if (index >= numOfElement) return;

            displayInorder( 2 * index + 1 );
            
            cout << array[index] << " ";
     
            displayInorder( 2 * index + 2 );
        }

        void displayPreorder( int index = 0 ) {
            if (index >= numOfElement) return;


            cout << array[index] << " ";

            displayPreorder( 2 * index + 1 );
            
     
            displayPreorder( 2 * index + 2 );
        }

        void displayPostorder( int index = 0 ) {
            if (index >= numOfElement) return;

            displayPostorder( 2 * index + 1 );
     
            displayPostorder( 2 * index + 2 );

            cout << array[index] << " ";

        }

};

template<class T>
class BinaryTreeInLinkedList {
    private:

        class TreeNode {
            private:
            public:
                TreeNode(T d) : data(d), left(nullptr), right(nullptr) {}
                TreeNode *left, *right;
                T data;
        };

        TreeNode *root;
        int numOfElement;

    public:

        BinaryTreeInLinkedList() : root(nullptr), numOfElement(0) {}

        void addElementAsCompleteTree(T data) {

            TreeNode *temp = new TreeNode( data );
            if ( root == nullptr ) {
                root = temp;
                numOfElement++;
                return;
            }

            queue< TreeNode* > save;
            save.push( root );
            
            while ( !save.empty() ) {

                TreeNode* cur = save.front();
                save.pop();
                
                if ( cur->left == nullptr ) {
                    cur->left = temp;
                    numOfElement++;
                    return;
                }
                else {
                    save.push(cur->left);
                }
                
                if ( cur->right == nullptr ) {
                    cur->right = temp;
                    numOfElement++;
                    return;
                }
                else {
                    save.push(cur->right);
                }

            }
        }

        void displayInorder( TreeNode *in = nullptr ) {
            static bool first = true;
            if ( in == nullptr ) {

                if ( first ) {
                    in = root;
                    first = false;
                }
                else{ return; }
            }

            displayInorder( in->left );

            cout << in->data << " ";

            displayInorder( in->right );
        }

        void displayPreorder( TreeNode *in = nullptr ) {
            static bool first = true;
            if ( in == nullptr ) {
                
                if ( first ) {
                    in = root;
                    first = false;
                }
                else{ return; }
            }
            
            cout << in->data << " ";

            displayPreorder( in->left );

            displayPreorder( in->right );

        }

        void displayPostorder( TreeNode *in = nullptr ) {

            static bool first = true;
            if ( in == nullptr ) {
                
                if ( first ) {
                    in = root;
                    first = false;
                }
                else{ return; }
            }

            displayPostorder( in->left );

            displayPostorder( in->right );

            cout << in->data << " ";

        }

};

int main() {
    BinaryTreeInArray<int> *b = new BinaryTreeInArray<int>;
    BinaryTreeInLinkedList<int> *tree = new BinaryTreeInLinkedList<int>;
    int j, n;
    cin >> n;
    for(j = 0;j < n;j ++) {
        b->addElementAsCompleteTree(j);
        tree->addElementAsCompleteTree(j);
    }

    b->displayInorder();
    cout << endl;
    tree->displayInorder();
    cout << endl;
    b->displayPreorder();
    cout << endl;
    tree->displayPreorder();
    cout << endl;
    b->displayPostorder();
    cout << endl;
    tree->displayPostorder();
    cout << endl;
    return 0;
}
