#include <iostream>
#include <cmath>
#include <vector>
#include<queue>

using namespace std;

template<class T>
class TreeInLinkedList {

    private:
        class TreeNode {
            private:

            public:
                TreeNode(T d, TreeNode *p) : data(d), parent(p) {}
                TreeNode *parent;
                T data;
        };

        vector<TreeNode *> *nodeList;

    public:
        TreeInLinkedList() {
            nodeList = new vector<TreeNode *>();
        }

        void addElement(T data) {
            int j, k = nodeList->size();
            if(data == 1) {
                nodeList->clear();
                nodeList = new vector<TreeNode *>();

                TreeNode *newNode = new TreeNode(data, nullptr);
                
                nodeList->push_back(newNode);
            }
            else {

                for(j = 0;j < k;j ++) {
                    if(data % (*nodeList)[j]->data == 0) {
                        TreeNode *newNode = new TreeNode(data, (*nodeList)[j]);
                        nodeList->push_back(newNode);
                    }
                }
            }
        }

        void displayPreorder(int index = 0) {
        
            if ( index >= nodeList->size() ) return;

            cout << (*nodeList)[index]->data << " ";

            for (int i = index + 1; i < nodeList->size(); i++) {
                if ( (*nodeList)[index] == (*nodeList)[i]->parent )  {
                    displayPreorder( i );
                
                }
            }
    
        }

        void displayPostorder(int index = 0) {
    
            if( index >= nodeList->size() ) return;

            for( int i = index + 1 ; i < nodeList->size() ; i++ ) {
                if ( (*nodeList)[index] == (*nodeList)[i]->parent ) {
                    displayPostorder( i );
                }
            }
    
            cout << (*nodeList)[index]->data << " ";
        }

};

int main()
{
    TreeInLinkedList<int> *tree = new TreeInLinkedList<int>();
    int j;
    int n;
    cin >> n;
    
    for(j = 1;j <= n;j ++)
        tree->addElement(j);

    tree->displayPreorder();
    cout << endl;
    tree->displayPostorder();
    cout << endl;

}
