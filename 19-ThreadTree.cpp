#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

template<class T>
class BinaryThreadedTreeNode {
private:
protected:
    T *data;
    BinaryThreadedTreeNode *left, *right;
    bool isThread;
public:
    BinaryThreadedTreeNode(T d) : right(nullptr), left(nullptr), isThread(false) {
        data = new T {d};
    }
    BinaryThreadedTreeNode() : data(nullptr), right(nullptr), left(nullptr), isThread(false) {}

    BinaryThreadedTreeNode* getLeft () {
        return left;
    }
    BinaryThreadedTreeNode* getRight () {
        return right;
    }
    T *getData () {
        return data;
    }
    bool getisThread () {
        return isThread;
    }

    void setLeft ( BinaryThreadedTreeNode<T>* t ) {
        left = t;
    }
    void setRight ( BinaryThreadedTreeNode<T>* t ) {
        right = t;
    }
    void setisThread ( bool t ) {
        isThread = t;
    }

};

template<class T>
class BinarySearchThreadedTree : BinaryThreadedTreeNode<T> {
private:
    void CreateThread() {
        
        CreateThread(this);
        
    }

    void CreateThread( BinaryThreadedTreeNode<T>* node ) {

        if ( !node || !node->getLeft() ) return;

        CreateThread( node->getLeft() );

        BinaryThreadedTreeNode<T>* temp = node->getLeft();
        while ( 1 ) {

            if ( temp->getRight() ) {
                temp = temp->getRight();
            }
            else break;
        }

        if ( !temp->getisThread() ) {
            temp->setRight(node);
            temp->setisThread(true);
        }
        else return;

        CreateThread( node->getRight() );
    }

    void display ( BinaryThreadedTreeNode<T>* n ) {
        if ( n && n->getData() ) {
            cout << *(n->getData()) << " ";
        } 
    }

public:
    BinarySearchThreadedTree() : BinaryThreadedTreeNode<T>() {}
    BinarySearchThreadedTree *insert(T d) {
        if(!this->data) {
            this->data = new T {d};
            this->left = new BinarySearchThreadedTree();
            this->right = new BinarySearchThreadedTree();
            return this;
        }
        else {
            if(*this->data > d)
                return (static_cast<BinarySearchThreadedTree<T> *>(this->left))->insert(d);
            else
                return (static_cast<BinarySearchThreadedTree<T> *>(this->right))->insert(d);
        }
    }
    void print() {
        CreateThread();

        if ( !this )  return;

        BinaryThreadedTreeNode<T>* cur = this;
        while ( cur && cur->getLeft() ) {
            cur = cur->getLeft();
        }

        while ( cur ) {

            display(cur);

            if ( cur->getisThread() ) {
                cur = cur->getRight();
            }
            else {
                cur = cur->getRight();
                while ( cur && cur->getLeft() ) {
                    cur = cur->getLeft();
                }
            }
        }
        
    }
};

int main() {
    int j;
    BinarySearchThreadedTree<int> bstt;
    srand(time(nullptr));
    for(j = 0;j < 10;j ++)
        bstt.insert(rand() % 100);
    bstt.print();
}
