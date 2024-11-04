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
					
					//set the necessary Node
					Node *swap = temp2->getNext();
					Node *pre2 = temp2->getPre();
					Node *next2 = temp2->getNext()->getNext();
					
					//check if is the first one
					if ( pre2 != nullptr ) {

                    	pre2->setNext(swap);

                	} else {
                    	list = swap;
                	}
					
					//check if is the last one
					if ( next2 != nullptr ) {
						next2->setPre(temp2);
					}

					//swap Node
					swap->setPre( pre2 );
					swap->setNext( temp2 );
					temp2->setPre( swap );
					temp2->setNext( next2 );

					temp2 = swap;
				}

				

			}	
		} 
	}
	
	void selectionSort()
	{
		Node *temp1 = nullptr;
		Node *temp2 = nullptr;

		for ( temp1 = list ; temp1 != nullptr && temp1->getNext() != nullptr ; temp1 = temp1->getNext() ) {

			Node *min_locate = temp1;
			int min_data = temp1->getData();

			for ( temp2 = temp1->getNext() ; temp2 != nullptr ; temp2 = temp2->getNext() ) {
				
				//find the min data and locate
				if ( temp2->getData() < min_data  ) {
					min_data = temp2 ->getData();
					min_locate = temp2;
				}
				
			}

			//check if min_locate equal temp1
			if ( min_locate != temp1 ) {

				Node *pre1 = temp1->getPre();
				Node *next1 = temp1->getNext();
				Node *pre2 = min_locate->getPre();
				Node *next2 = min_locate->getNext();

				//temp1 next to min_locate 
				if ( min_locate == next1 ) {
					
					if ( pre1 != nullptr ) {
						pre1->setNext( min_locate );
					}
					else {
						list = min_locate;
					}

					if ( next2 != nullptr ) {
						next2->setPre( temp1 );
					}

					min_locate->setNext( temp1 );
					min_locate->setPre( pre1 );
					temp1->setNext( next2 );
					temp1->setPre( min_locate );

				}
				//temp1 is not next to min_locate 
				else {
					if ( pre1 != nullptr ) {
						pre1->setNext( min_locate );
					}
					else {
						list = min_locate;
					}

					if ( next1 != nullptr ) {
						next1->setPre( min_locate );
					}

					if ( pre2 != nullptr ) {
						pre2->setNext( temp1 );
					}

					if ( next2 != nullptr ) {
						next2->setPre( temp1 );
					}

					temp1->setPre( pre2 );
					temp1->setNext( next2 );
					min_locate->setPre( pre1 );
					min_locate->setNext( next1 );
					
				}
				temp1 = min_locate;
			}
			
		} 
	}
	
	void insertionSort()
	{

		Node *temp1 = nullptr;
		
		for ( temp1 = list->getNext() ; temp1 != nullptr  ; temp1 = temp1->getNext() ) {
			
			int key = temp1->getData();
			Node *temp2 = temp1 ->getPre();
			
			//From temp1->getPre() start find the insertion place
			while ( temp2 != nullptr && temp2->getData() > key ) {
            	temp2 = temp2->getPre();
        	}

			//if temp1 need to move =>temp2 not temp1->getPre() now
			if ( temp2 != temp1->getPre() ) {
				
				//take the temp1 from list ,and connected the list
				Node *next1 = temp1->getNext();
				temp1->getPre()->setNext(next1);
				if ( next1 != nullptr ) {
					next1->setPre( temp1->getPre() );
				}

				//if the temp1 is the small one ,and insert at firts one
				if ( temp2 == nullptr ) {
				
					temp1->setNext( list );
					temp1->setPre( nullptr );
					list->setPre( temp1 );
					list = temp1;

				}
				//inser at the right place 
				else {

					Node *next2 = temp2->getNext();
					temp2->setNext( temp1 );
					temp1->setPre( temp2 );
					temp1->setNext( next2 );
					if ( next2 != nullptr ) {
						next2->setPre( temp1 );
					}

				}
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
