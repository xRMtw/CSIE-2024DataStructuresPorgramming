#include <iostream>
#include <cstdlib>

using namespace std;

template<class T>
class Memory  {
public:
  static T **allocArray(int m, int n)
  {
    T **p = new T*[m];
    p[0] = new T[ m*n ];
    for ( int i = 1 ; i < m ; i++ ) {
        p[i] = p[i-1] + n;
    }
    
    return p;
  }

};

int main()
{
  int **array;
  array = Memory<int>::allocArray(5, 10);
  int j, k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      array[j][k] = j * 10 + k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      cout<<array[j][k]<<" ";
  
  delete[] array[0];
  delete[] array;
  
}