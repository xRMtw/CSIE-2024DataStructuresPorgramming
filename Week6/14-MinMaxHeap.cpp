#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>

template<class T>
class MinMaxHeap {
  public:
      MinMaxHeap() :elements() {}

      //The insert function in a Min-Max Heap adds a new element to the heap while maintaining its unique properties.
      void insert(T value) {

        elements.push_back(value);
        int index = (int)elements.size()-1;
         
        int parent = (index-1)/2;

        if ( MinorMax(index) ) { //index is Min level
          
          if ( elements[parent] < elements[index] ) {

            std::swap( elements[parent],elements[index] );

            MaxlevelUP( parent );

          }
          else {

            MinlevelUP( index );
          
          }

        }
        else { //index is Max level

          if ( elements[parent] > elements[index] ) {

            std::swap( elements[parent],elements[index] );

            MinlevelUP( parent );
          
          }
          else {

            MaxlevelUP( index );

          }
          
        }

      }

      // Retrieve the minimum element in the heap, throw an exception when heap is empty
      T getMin() const {
        if ( elements.empty() ) throw std::out_of_range( "Heap is empty" );
        return elements[0];
      }

      // Retrieve the maximum element in the heap, throw an exception when heap is empty
      T getMax() const {
        if ( elements.empty() ) throw std::out_of_range( "Heap is empty" );
        if ( elements.size() == 1 ) return elements[0];
        return std::max( elements[1],elements[2] );
       
      }

      // Delete the minimum element in the heap, throw an exception when heap is empty
      void deleteMin() {

        if ( elements.empty() ) throw std::out_of_range( "Heap is empty" );
        elements[0] = elements.back();
        elements.pop_back();

        if ( !elements.empty() ) { 
          
          MinSortDown(0);
          
        }

      }

      // Delete the maximum element in the heap, throw an exception when heap is empty
      void deleteMax() {
         if ( elements.empty() ) throw std::out_of_range( "Heap is empty" );
         int maxindex = findMaxone();
         elements[maxindex] = elements.back();
         elements.pop_back();

        if ( !elements.empty() ) { 
          
          MaxSortDown(maxindex);
          
        }
      }

  private:
      //create any member you need to complete MinMaxHap
      std::vector<T> elements;

      int findMaxone () {

        if( elements.size() == 1 ) return 0;
        if( elements.size() == 2 ) return 1;
        return ( ( elements[1] > elements[2] )? 1:2 );
      
      }

      bool MinorMax ( int index ) {

        int temp = std::floor( log2( index+1 ) );
        return ( temp % 2 == 0 );
      
      }

      void MinlevelUP ( int index ) {

        while ( index > 0 ) {

          int grandparent = ( index-3 )/4;

          if ( elements[index] < elements[grandparent] && grandparent >=0 ) {

            std::swap( elements[grandparent] , elements[index] );

            index = grandparent;
          }

          else break;

        }

      }

      void MaxlevelUP ( int index ) {

        while ( index > 0 ) {

          int grandparent = ( index-3 )/4;

          if ( elements[index] > elements[grandparent] && grandparent >0 ) {
            
            std::swap( elements[grandparent] , elements[index] );

            index = grandparent;
          
          }
          else break;

        }
        
      }
      
      void MinSortDown ( int index ) {

        while ( index < elements.size() ) {

          int left = 2*index + 1;
          int right = 2*index + 2;
          int smallest = index;

          if ( left < elements.size() && elements[smallest] > elements[left] ) {
            smallest = left;
          }
          if ( right < elements.size() && elements[smallest] > elements[right] ) {
            smallest = right;
          }

          //more node compare
          int leftLeft = 2 * left + 1;
          int leftRight = 2 * left + 2;
          int rightLeft = 2 * right + 1;
          int rightRight = 2 * right + 2;

          if (leftLeft < elements.size() && elements[leftLeft] < elements[smallest]) {
              smallest = leftLeft;
          }
          if (leftRight < elements.size() && elements[leftRight] < elements[smallest]) {
              smallest = leftRight;
          }
          if (rightLeft < elements.size() && elements[rightLeft] < elements[smallest]) {
              smallest = rightLeft;
          }
          if (rightRight < elements.size() && elements[rightRight] < elements[smallest]) {
              smallest = rightRight;
          }

          if ( smallest == index ) break;

          std::swap( elements[smallest],elements[index] );

          index = smallest;

        }
      
      }

      void MaxSortDown ( int index ) {

        while ( index < elements.size() ) {

          int left = 2*index + 1;
          int right = 2*index + 2;
          int largest = index;

          if ( left < elements.size() && elements[largest] < elements[left] ) {
            largest = left;
          }
          if ( right < elements.size() && elements[largest] < elements[right] ) {
            largest = right;
          }

          //more node compare
          int leftLeft = 2 * left + 1;
          int leftRight = 2 * left + 2;
          int rightLeft = 2 * right + 1;
          int rightRight = 2 * right + 2;

          if (leftLeft < elements.size() && elements[leftLeft] > elements[largest]) {
              largest = leftLeft;
          }
          if (leftRight < elements.size() && elements[leftRight] > elements[largest]) {
              largest = leftRight;
          }
          if (rightLeft < elements.size() && elements[rightLeft] > elements[largest]) {
              largest = rightLeft;
          }
          if (rightRight < elements.size() && elements[rightRight] > elements[largest]) {
              largest = rightRight;
          }

          if ( largest == index ) break;

          std::swap( elements[largest],elements[index] );

          index = largest;

        }
        
      }

};
int main() {
    MinMaxHeap<int> mmHeap;
    int j;
    srand(time(NULL));
    for(j = 0;j < 10;j ++)
      mmHeap.insert(rand() % 100);

    while(true) {
      try {
        std::cout << mmHeap.getMin() << " ";
        mmHeap.deleteMin();
      }
      catch(std::exception) {
        break;
      }
    }
    std::cout << std::endl;
    
    for(j = 0;j < 10;j ++)
      mmHeap.insert(rand() % 100);

    while(true) {
      try {
        std::cout << mmHeap.getMax() << " ";
        mmHeap.deleteMax();
      }
      catch(std::exception) {
        break;
      }
    }

    return 0;
}
