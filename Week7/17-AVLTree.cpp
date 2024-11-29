//PREPEND BEGIN
/*some text*/
//PREPEND END

//TEMPLATE BEGIN
#include<bits/stdc++.h>

using namespace std;

template<class T>
class Node
{
	public:
		Node()
		{
			data = new T;
		}
		Node(T d)
		{
			data = new T;
			(*data) = d;
		}
		Node &operator=(T d)
		{
			(*data) = d;
			return *this;
		}
		friend std::ostream &operator<<(std::ostream &out, Node n)
		{
			out<<*(n.data);
			return out;
		}
		friend std::ostream &operator<<(std::ostream &out, Node *n)
		{
			out<<*(n->data);
			return out;
		}
		void setData(T d)
		{
			*data = d;
		}
		T &getData() const
		{
			return *data;
		}
	protected:
		T *data;
};

template<class T>
class BinaryTreeNode : public Node<T>
{
	public:
		BinaryTreeNode() : Node<T>()
		{
			left = NULL;
			right = NULL;
		}
		BinaryTreeNode(T d) : Node<T>(d)
		{
			left = NULL;
			right = NULL;
		}
		BinaryTreeNode(BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>()
		{
			left = l;
			right = r;
		}
		BinaryTreeNode(T d, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>(d)
		{
			left = l;
			right = r;
		}
		void setLeft(BinaryTreeNode<T> *l)
		{
			left = l;
		}
		void setRight(BinaryTreeNode<T> *r)
		{
			right = r;
		}
		BinaryTreeNode<T> *&getLeft()
		{
			return left;
		}
		BinaryTreeNode<T> *&getRight()
		{
			return right;
		}
		bool operator>(BinaryTreeNode<T> n)
		{
			if(*(this->data) > *(n.data))
				return true;
			return false;
		}
		bool operator==(BinaryTreeNode<T> n)
		{
			if(*(this->data) == *(n.data))
				return true;
			return false;
		}
	private:
		BinaryTreeNode<T> *left, *right;
};

template<class T>
class AVLTree
{
	private:
		BinaryTreeNode<T> *root;

		void inorder(BinaryTreeNode<T> *cur, int n)
		{
			if(cur == NULL)
			return;
			inorder(cur->getRight(), n + 1);
			int j;
			for(j = 0;j < n;j ++)
			cout << "  ";
			cout << cur << endl;
			inorder(cur->getLeft(), n + 1);
		}

		int getheight( BinaryTreeNode<T>* cur ) {

            if ( cur == nullptr ) return -1;

            int leftHeight = getheight( cur->getLeft() );
            int rightHeight = getheight( cur->getRight() );

            return 1 + max(leftHeight, rightHeight);

        }
		
		int getBalanceFactor ( BinaryTreeNode<T>* cur ) {
			if ( !cur ) return 0;
			return ( getheight( cur->getLeft() ) - getheight( cur->getRight() ) );
		}

		BinaryTreeNode<T> *rightRotation ( BinaryTreeNode<T>* cur ) {
			if ( !cur || !cur->getLeft() ) return cur;

			BinaryTreeNode<T> *LeftChild = cur->getLeft();
			BinaryTreeNode<T> *temp = LeftChild->getRight();

			LeftChild->setRight( cur );
			cur->setLeft( temp );

			return LeftChild;
		}

		BinaryTreeNode<T> *leftRotation ( BinaryTreeNode<T>* cur ) {
			if ( !cur || !cur->getRight() ) return cur;

			BinaryTreeNode<T> *RightChild = cur->getRight();
			BinaryTreeNode<T> *temp = RightChild->getLeft();

			RightChild->setLeft( cur );
			cur->setRight( temp );

			return RightChild;
		}

		BinaryTreeNode<T> *updateTreeBalance ( BinaryTreeNode<T> *cur ) {

			int BF = getBalanceFactor( cur );
			if ( BF > 1 ) {
				if ( getBalanceFactor( cur->getLeft() ) == 1 ) {
					return rightRotation(cur);
				}
				else {
					cur->setLeft( leftRotation( cur->getLeft() ) );
					return rightRotation(cur);
				}
			}
			else if ( BF < -1 ) {
				if ( getBalanceFactor( cur->getRight() ) == 1 ) {
					return leftRotation(cur);
				}
				else {
					cur->setRight( rightRotation( cur->getRight() ) );
					return leftRotation(cur);
				}
			}
			else 
				return cur;
		}

	public:

		AVLTree() {
			root = nullptr;

		};

		void insert(T d) {
			BinaryTreeNode<T> *newone = new BinaryTreeNode<T>(d);
			
			if ( !root ) {
				root = newone;
				return;
			}

			BinaryTreeNode<T> *cur = root;
			BinaryTreeNode<T> *parent = nullptr;
			stack<BinaryTreeNode<T>*> path;

			while ( cur != nullptr ) {
				
				parent = cur;
				path.push(parent);

				if ( cur->getData() > d ) {
					cur = cur->getLeft();
				}
				else if ( cur->getData() < d ) {
					cur = cur->getRight();
				}
				else {
					delete newone;
					return;
				}

			}

			if ( parent->getData() > d ) {
				parent->setLeft( newone );
			}
			else {
				parent->setRight( newone );
			}

			while ( !path.empty() ) {
				cur = path.top();
				path.pop();
				cur = updateTreeBalance( cur );

				if ( !path.empty() ) {
					parent = path.top();
					if ( parent->getData() > cur->getData() ) parent->setLeft( cur );
					else parent->setRight( cur );
				}
				else {
					root = cur;
				}
			}

		}

		void inorder()
		{
			inorder(root, 0);
		}
};

int main()
{
	AVLTree<int> *tree = new AVLTree<int>();
	srand(0);
	int j, k, i;
	for(j = 0;j < 20;j ++)
	{
		tree->insert(rand() % 100);
		tree->inorder();
		cout << "\n";
	}
}
