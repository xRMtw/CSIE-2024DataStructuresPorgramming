#include <iostream>
#include <cstdlib>
#include <ctime>

#define SIZE 100

using namespace std;

class Node
{
public:
	Node()
	{
		next = NULL;
		pre = NULL;
	}
	Node(int n)
	{
		data = n;
		next = NULL;
		pre = NULL;
	}
	int getData() { return data; }
	Node *getNext() { return next; }
	Node *getPre() { return pre; }
	void setData(int d) { data = d; }
	void setNext(Node *n) { next = n; }
	void setPre(Node *p) { pre = p; }
private:
	int data;
	Node *next, *pre; 
};

class List
{
public:
	List() { list = NULL; }
	List(int n) { generate(n); }
	
	void generate(int n)
	{
		int j;
		list = NULL;
		for(j = 0;j < n;j ++)
			generate();
	}
	
	void generate()
	{
		Node *buf = new Node(rand());
		buf->setNext(list);
		if(list != NULL)
			list->setPre(buf);
		list = buf;
	}
	
	void bubbleSort()
	{	
		Node *temp1 = nullptr;
		Node *temp2 = nullptr;

		for ( temp1 = list ; temp1->getNext() != NULL ; temp1 = temp1->getNext() ) {
			for ( temp2 = list ; temp2->getNext() != NULL ; temp2 = temp2->getNext() ) {
				if ( temp2->getData() > temp2->getNext()->getData() ) {
					
					//swap two data
					int tempdata;
					tempdata = temp2->getData();
					temp2->setData( temp2->getNext()->getData() );
					temp2->getNext()->setData( tempdata );

				}
			}	
		} 
	}
	
	void selectionSort()
	{
		Node *temp1 = nullptr;
		Node *temp2 = nullptr;

		for ( temp1 = list ; temp1->getNext() != NULL ; temp1 = temp1->getNext() ) {

			Node *min_locate = nullptr;
			int min_data = temp1->getData();

			for ( temp2 = temp1->getNext() ; temp2 != NULL ; temp2 = temp2->getNext() ) {
				
				//find the min of data
				if ( temp2->getData() < min_data  ) {
					min_data = temp2 ->getData();
					min_locate = temp2;
				}
				
			}

			//if min data is temp1 or not
			if ( min_locate != temp1 ) {

				int tempdata = temp1->getData(); 
				temp1->setData( min_data );
				min_locate->setData( tempdata );
			
			}
		} 
	}
	
	void insertionSort()
	{

		Node *temp1 = nullptr;
		
		for ( temp1 = list->getNext() ; temp1 != nullptr  ; temp1 = temp1->getNext() ) {
			
			//set key
			int key = temp1->getData();
			Node *temp2 = nullptr;
			temp2 = temp1 ->getPre();

			//swap if temp2 > key
			while ( temp2 != nullptr && temp2->getData() > key ) {
				
				temp2 ->getNext()->setData( temp2->getData() );
				
				temp2 = temp2->getPre();
				
			}

			//insert the key
			if ( temp2 ==  nullptr ) {
				list->setData( key );
			}
			else {	
				temp2->getNext()->setData( key );
			}
			
		} 

		
	} 
	
	void print()
	{
		Node *cur = list;
		while(cur != NULL)
		{
			cout<<cur->getData()<<" ";
			cur = cur->getNext();
		}
		cout<<endl;
	}
private:
	Node *list;
};

int main()
{
	srand(time(NULL));
	List *l = new List(10);
	l->print();
	l->bubbleSort();
	l->print();
	
	l = new List(10);
	l->print();
	l->insertionSort();
	l->print();
	
	l = new List(10);
	l->print();
	l->selectionSort();
	l->print();
}
