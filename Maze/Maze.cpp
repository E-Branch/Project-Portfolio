#include <cstring>
#include <iostream>
#include <stack>
#include <stdio.h>

#define N 4

#define M 5

using std::cout;
using std::stack;

class node {
public:
	int x, y;
	
	node(int i, int j){
		x = i;
		y = j;
	}
};

bool isReachable(int maze[N][M], int fx, int fy){
	stack<node> s; //stack of  nodes to go through
	int i, j; //current location
	
	//initialy staring at (0, 0)
	s.push(node(0,0));
	
	//initialize an array to keep track of visited potitions
	bool visited[N][M] = {false};
	
	node node_s = node(0,0);
	while(!(s.empty()) && !(i==fx && j== fy)){
		//takes the top node in the stack 
		node_s = s.top();
		i = node_s.x;
		j = node_s.y;
		
		// check neighbor nodes, the first one to be viable and unvisited is pushed
		// otherwise the current node is removed from the stack, and the algorithm moves
		// onto the one below it
		if (i+1<N && (visited[i+1][j] == false) && maze[i+1][j] == 1){
			s.push(node(i+1,j));
			visited[i+1][j] = true;
		}
		else if (j+1<M && (visited[i][j+1] == false) && maze[i][j+1] == 1){
			s.push(node(i,j+1));
			visited[i][j+1] = true;
		}
		else if (i-1>=0 && (visited[i-1][j] == false) && maze[i-1][j] == 1){
			s.push(node(i-1,j));
			visited[i-1][j] = true;
		}
		else if (j-1>=0 && (visited[i][j-1] == false) && maze[i][j-1] == 1){
			s.push(node(i,j-1));
			visited[i][j-1] = true;
		}
		else{
			s.pop();	
		}
		
	}
	// if s has no nodes in it by then end, then no path exists
	if(s.empty()) return false;
	// otherwise, a path exists
	return true;
}



int main(){
	
	int maze[N][M] = {	
		{1 ,0 ,1 ,1 ,1} ,
		{1 ,1 ,1 ,0 ,1} ,
		{0 ,0 ,0 ,0 ,1} ,
		{1 ,1 ,1 ,0 ,1}
	};
	
	int fx = 3; int fy = 4;
	
	
	if (isReachable(maze,fx,fy)){
		cout << "Path Found!" << '\n';
	}
	else {
		cout << "No Path Found!" << '\n';
	}
	
	return 0;
}
