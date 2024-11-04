#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Grid
{
public:
	Grid():visited(false)
	{
		Grid(0);
	}
	Grid(int s)
	{	
		visited = false;
		state = s;
		dir[UP] = NULL;
		dir[DOWN] = NULL;
		dir[LEFT] = NULL;
		dir[RIGHT] = NULL;
	}
	Grid *getDir(int d) { return dir[d]; }
	int getState() { return state; }
	void setDir(int d, Grid *g) { dir[d] = g; }
	void setState(int s) { state = s;}

	bool isVisited () const { return visited; }
	void setVisited ( bool k ) { visited = k; }

private:
	Grid *dir[4];
	int state;
	bool visited;
};

struct List
{
public:
	List()
	{
		top = 0;
	}
	/*
	Insert an element from top
	*/
	void addElement(Grid *g)
	{	
	
		data[top] = g;
		top++;

	}
	/*
	remove an element from top and return a pointer point to the element.
	If list is empty, return NULL.
	*/
	Grid *removeElement()
	{
		if ( top > 0 ) {
			Grid *temp = data[ top-1 ];
			top--;
			return temp;
		}
		else { return NULL; }
	}
	void printPath()
	{	
		int j;
		for(j = 1;j < top;j ++)
		{
			if(data[j] == data[j - 1]->getDir(UP))
			{
				cout<<"UP\n";
			}
			else if(data[j] == data[j - 1]->getDir(DOWN))
			{
				cout<<"DOWN\n";
			}
			else if(data[j] == data[j - 1]->getDir(LEFT))
			{
				cout<<"LEFT\n";
			}
			else if(data[j] == data[j - 1]->getDir(RIGHT))
			{
				cout<<"RIGHT\n";
			}
		}
	}
private:
	Grid *data[SIZE * SIZE];
	int top;
};

class Maze
{
public:
	Maze()
	{
		initMaze(SIZE);
	}
	/*
	function initMaze
	Alocate a 2-D link list with s * s sizes as the map of maze.
	Inside the maze enery gird with state 0 represent empty space and 1 represent wall.
	The gird in left top is start point and right bottom is finish point.
	Randomly generate 20% wall in the maze.
	Make sure start point and finish point are 0

	動態配置一個二維的鏈結串列，大小是 s * s，用這個鏈結串列表示迷宮的地圖
	節點中 0 的值表示可以移動的空間， 1 表示牆壁 
	左上角的位置表示起點，右下角的位置表示終點
	請在迷宮中加入 20% 的牆壁 
	然後確定起點跟終點都是可以移動的位置 
	*/
	void initMaze(int s)
	{
		maze = new Grid[s*s];
		for ( int i = 0 ; i < ( s*s ) ; i++ ) {
			
			if ( ( ( i-10 ) >= 0 ) && ( ( i-10 ) < ( s*s ) ) ) {
				maze[i].setDir( UP , &maze[i-10] ); 
			}
			else {
				maze[i].setDir( UP , nullptr );
			}

			if ( ( ( i+10 ) >= 0 ) && ( ( i+10 ) < ( s*s ) ) ) {
				maze[i].setDir( DOWN , &maze[i+10] );
			}
			else { 
				maze[i].setDir( DOWN , nullptr );
			}

			if ( ( ( i-1 ) >= 0 ) && ( ( i-1 ) < ( s*s ) ) && !( i % s == 0 ) ) {
				maze[i].setDir( LEFT , &maze[i-1] );
			}
			else { 
				maze[i].setDir( LEFT , nullptr );
			}

			if ( ( ( i+1 ) >= 0 ) && ( ( i+1 ) < ( s*s ) ) && !( ( i+1 ) % s == 0 ) ) {
				maze[i].setDir( RIGHT , &maze[i+1] ); 
			}
			else { 
				maze[i].setDir( RIGHT , nullptr );
			}
			
		}

		for ( int i = 0 ; i < ( s*s ) ; i++ ) {
			maze[i].setState(0);
		}

		srand( time(NULL) );

  		int min = 0;
  		int max = (s*s)-1;

		int count = s*s/5;

		while ( count ) {

			int k = rand() % ( max - min + 1 );

			if ( maze[k].getState() == 0 && !( k == 0 ) && !( k == ( (s*s)-1 ) ) ) {

				maze[k].setState(1);
				count --;
				
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
		
		if ( findPath ( &maze[0] , Path ) ) { return Path; }
		else {
			delete Path;

			return NULL; 
		}
			
	}

	bool findPath( Grid *temp, List *path ) {

		if ( temp->getState() == 1 || temp->isVisited() ) {
			return false;
		}
		
		path->addElement( temp );
		temp->setVisited( true ); 
		
		if ( temp == &maze[ SIZE*SIZE-1 ] ) {
			return true;
		}

		if ( ( ( temp->getDir( UP ) != nullptr ) && findPath( temp->getDir( UP ) , path ) ) || 	 
		     ( ( temp->getDir( DOWN ) != nullptr ) && findPath( temp->getDir( DOWN ) , path ) ) ||  
		     ( ( temp->getDir( LEFT ) != nullptr ) && findPath( temp->getDir( LEFT ) , path ) ) || 
		     ( ( temp->getDir( RIGHT ) != nullptr ) && findPath( temp->getDir( RIGHT ) , path ) ) ) {  
			return true;
		}
		
		path->removeElement();
		temp->setVisited( false );
		return false;
	}


	void printMaze()
	{
		Grid *j = maze, *k;
		while(j != NULL)
		{
			k = j;
			while(k != NULL)
			{
				cout<<k->getState();
				k = k->getDir(RIGHT); 
			}
			cout<<endl;
			j = j->getDir(DOWN);
		}
	}
private:
	Grid *maze;
};

int main()
{
	Maze *maze = new Maze();
	maze->printMaze();
	List *Path = maze->getPath();
	if ( Path != NULL ) {
		Path->printPath();
	}
}
