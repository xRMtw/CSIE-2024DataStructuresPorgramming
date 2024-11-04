#include<iostream>
#include<cstdlib>
#include<ctime>

#define SIZE 10

using namespace std;

class Node
{
public:
	Node()
	{
		Node(0, 0);
	}
	Node(int r, int c)
	{
		row = r;
		col = c;
	}
	int getRow() { return row; }
	int getCol() { return col; }
	void setRow(int r)
	{
		if(r >= 0 && r < SIZE)
			row = r;
	}
	void setCol(int c)
	{
		if(c >= 0 && c < SIZE)
			col = c;
	}
private:
	int col, row;
};

class List
{
public:
	List()
	{
		top = 0;
	}
	/*
	function addElement
	Insert an element from list
	*/
	void addElement(int r, int c)
	{
		data[top].setRow( r );
		data[top].setCol( c );
		top++;
	}
	/*
	function removeElement
	remove an element from list and return a pointer point to the element.
	If list is empty, return NULL.
	*/
	Node *removeElement()
	{
		if ( top > 0 ) {

			Node *temp = &data[ top - 1 ];
			top --;
			return temp;

		}
		else { return NULL; }

	}
	void printList()
	{
		int j;
		for(j = 0;j < top;j ++)
		{
			cout<<"("<<data[j].getRow()<<", "<<data[j].getCol()<<")"<<endl;
		}
	}
private:
	Node data[SIZE * SIZE];
	int top;
};

class Maze
{
public:
	Maze()
	{
		initMaze(SIZE);
	}
	~Maze () {
		
		delete maze[0];
		delete maze;
		delete visited[0];
		delete visited;
		
	}	
	/*
	function initMaze
	Alocate a 2-D array with s * s sizes as the map of maze.
	Inside the maze where 0 represent empty space and 1 represent wall.
	[0][0] is start point and [s - 1][s - 1] is finish point.
	Randomly generate 20% wall in the maze.
	Make sure [0][0] and [s - 1][s - 1] are 0

	動態配置一個二維的陣列，大小是 s * s ，用這個陣列表示迷宮的地圖
	陣列中 0 的值表示可以移動的空間， 1 表示牆壁 
	[0][0] 的位置表示起點 [s - 1][s - 1] 的位置表示終點
	請在迷宮中加入 20% 的牆壁 
	然後確定起點跟終點都是可以移動的位置 
	*/
	void initMaze(int s)
	{

		maze = (int**)malloc( s*sizeof( int* ) );
		maze[0] = (int*)malloc( s*s*sizeof(int) );
		
		for ( int i = 1 ; i < s ; i++ ) {
			maze[i] = maze[i-1] + s;
		}

		for (int i = 0; i < s; i++) {
			for (int j = 0; j < s; j++) {
				maze[i][j] = 0;
			}
		}

		srand( time(NULL) );

  		int min = 0;
  		int max = s-1;

		int count = s*s/5;

		while ( count ) {

			int x = rand() % ( max - min + 1 );
			int y = rand() % ( max - min + 1 );

			if ( maze[x][y] == 0 && !( x == 0 && y == 0 ) && !( x == (s-1) && y == (s-1) )) {

				maze[x][y] = 1;
				count --;
				
			}

		}

		visited = (int**)malloc( s*sizeof( int* ) );
		visited[0] = (int*)malloc( s*s*sizeof(int) );
		
		for ( int i = 1 ; i < s ; i++ ) {
			visited[i] = visited[i-1] + s;
		}

		for ( int i = 0 ; i < s ; i++ ) {
			for ( int k = 0 ; k < s ; k++ ) {
				visited[i][k] = maze[i][k];
			}
		}
		
	}
	/*
	function getPath
	This function will find a path between start point and finish point.
	Return a list content the path information inside.
	If there is no path between two point then the list will be empty.

	這個函數會找到起點到終點間的一條路徑
	回傳一個 list 包含著路徑的資訊
	如果找不到路徑的話 list 就會是空的 
	*/
	List *getPath()
	{	
		List *Path = new List();
		
		findPath( 0 , 0 , Path );

		if ( Path != NULL ) { return Path; }
		else { return NULL; }
			
			
	}

	bool findPath( int x, int y, List *path ) {

		if ( x < 0 || x >= SIZE || y < 0 || y >= SIZE || maze[x][y] == 1 || visited[x][y] ) {
			return false;
		}
		
		path->addElement(x, y);
		visited[x][y] = true; 
		
		if ( x == ( SIZE-1 ) && y == ( SIZE-1 ) ) {
			return true;
		}

		if ( findPath( x + 1, y, path ) || findPath( x - 1, y, path ) ||  findPath( x, y + 1, path ) || findPath( x, y - 1, path ) ) {  
			return true;
		}
		
		path->removeElement();
		return false;
	}


	void printMaze()
	{
		int j, k;
		for(j = 0;j < SIZE;j ++)
		{
			for(k = 0;k < SIZE;k ++)
			{
				if(maze[j][k] == 0)
					cout<<" ";
				else if(maze[j][k] == 1)
					cout<<"*";
			}
			cout<<"\n";
		}
	}

private:

	int **visited;
	int **maze;
};

int main()
{
	Maze *maze = new Maze();
	maze->printMaze();
	maze->getPath()->printList();
}
