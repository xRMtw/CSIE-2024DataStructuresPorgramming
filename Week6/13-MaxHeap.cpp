#include<bits/stdc++.h>

using namespace std;

template<class T>
class MaxHeap {
  public:
      //Constructing a empty heap.
      MaxHeap() : elements() {}

      //To add an element to the heap.
      void insert(T d) {
        elements.push_back(d);
        SortUp( (int)elements.size()-1 );

      }

      //To remove the root element in the heap and return it.
      T extract() {
        if ( elements.empty() ) { throw out_of_range("Heap is Empty"); }
        
        T temp = elements[0];
        elements[0] = elements.back();
        elements.pop_back();
        
        if ( !elements.empty() ) {
          SortDown(0);
        }

        return temp;
      }

      //Return the number of element int the heap.
      int count() {
        return elements.size();
      }

  private:
    vector<T> elements;

    void SortUp ( int index ) {

      while ( index > 0 ) {

        int parent = (index-1) / 2;

        if ( elements[index] <= elements[parent] ) break;

        else {

          swap(elements[parent],elements[index]);
         
          index = parent;
        
        } 
      
      }
    
    }

    void SortDown ( int index ) {

      while ( index < elements.size() ) {

        int left = 2*index + 1;
        int right = 2*index + 2;
        int largeone = index;

        if ( left < elements.size() && elements[index] < elements[left] ) {
          largeone = left;
        }
        if ( right < elements.size() && elements[index] < elements[right] ) {
          largeone = right;
        }

        if ( largeone == index ) break;

        swap(elements[largeone],elements[index]);
        index = largeone;

      }
      
    }
    
};

// int main () {
//   MaxHeap<int> m;
//   m.insert(1);
//   m.insert(5);
//   m.insert(4);
//   m.insert(3);
//   m.insert(2);
//   cout << m.extract() << endl;
//   cout << m.count() << endl;
// }