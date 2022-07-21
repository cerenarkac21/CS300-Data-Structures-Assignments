// Ceren Arkac ,28269, CS 300, HW1

#include <iostream>
#include "LinkedListStack.h"
#include <string>
#include <fstream>
#include <vector>
#include "randgen.h"
#include "strutils.h"
using namespace std;

struct Cell
{
		bool l, r, u, d;
		bool visited;
		int x_coor, y_coor;
		Cell()
		{
			l = true;
			r = true;
			u = true;
			d = true;
			visited = false;
		}
		Cell(int x, int y, bool l_ = true, bool r_ = true, bool u_ = true, bool d_ = true, bool visited_ = false): x_coor(x), y_coor(y), l(l_), r(r_), u(u_), d(d_), visited(visited_) {}

};

/*
I aimed to use this struct when I determined the suitable (unvisited) walls and randomize between these walls. 
The object of this struct will be created with the suitable walls and according to the random integer coming from the randgen object (say n),
in ChooseUnvisitedWall functions, the inputn property of the struct object will be returned.
*/
struct Options
{
	char input1;
	char input2;
	char input3; 
	char input4;

	Options (char in1 = '0', char in2 = '0', char in3 = '0', char in4 = '0'):input1(in1), input2(in2), input3(in3), input4(in4){}
};

		
void createMazeMatrix(vector <vector<Cell>> & mat, int numOfRows, int numOfCols){

	int j = 0;
	while( j < mat[0].size()){
		int i = mat.size()-1;
		while (i >= 0)
		{
			mat[i][j].x_coor = j;
			mat[i][j].y_coor = numOfRows - 1 - i;
			i--;
		}
		j ++;
	}

}

/*the properties of Options object op will be filled with L or u or r or d after the checks vector is filled with unvisited sides.
according to the random integer coming from the randgen object (say n), the inputn property of the struct object will be returned.
Below function is for the cells which are not on the edges or corners.
For each side, there is another function: chooseUnvisitedWallL, chooseUnvisitedWallU, chooseUnvisitedWallR, chooseUnvisitedWallB*/
char chooseUnvisitedWall(const Cell & left, const Cell & upper, const Cell & right, const Cell & down){ // for the middle ones
	int inputs = 0;
	vector <char> checks;
	if (!left.visited){
		checks.push_back('L');
		inputs += 1;}
	if (!upper.visited){
		checks.push_back('u');
		inputs += 1;}
	if (!right.visited){
		checks.push_back('r');
		inputs += 1;}
	if (!down.visited){
		checks.push_back('d');
		inputs += 1;}
	RandGen gen; int rand; Options op;
	if (inputs == 1){
		op.input1 = checks[0];
		return op.input1;}

	else if (inputs == 2){
		op.input1 = checks[0];
		op.input2 = checks[1];
		rand = gen.RandInt(1,2);  
		if (rand == 1){return op.input1;}
		else{return op.input2;}}

	else if (inputs == 3){
		op.input1 = checks[0];
		op.input2 = checks[1];
		op.input3 = checks[2];
		rand = gen.RandInt(1,3);
		if (rand == 1){return op.input1;}
		else if (rand == 2){return op.input2;}
		else{return op.input3;}}

	else if (inputs == 4){
		op.input1 = checks[0];
		op.input2 = checks[1];
		op.input3 = checks[2];
		op.input4 = checks[3];
		rand = gen.RandInt(1,4);
		if (rand == 1){return op.input1;}
		else if (rand == 2){return op.input2;}
		else if (rand == 3){return op.input3;}
		else{return op.input4;}
	}
}

 char chooseUnvisitedWallL(const Cell & upper, const Cell & right, const Cell & down){  // for the left side
	int inputs = 0;
	vector <char> checks;
	if (!upper.visited){
		checks.push_back('u');
		inputs += 1;}
	if (!right.visited){
		checks.push_back('r');
		inputs += 1;}
	if (!down.visited){
		checks.push_back('d');
		inputs += 1;}
	RandGen gen; int rand; Options op;
	if (inputs == 1){
		op.input1 = checks[0];
		return op.input1;}

	else if (inputs == 2){
		op.input1 = checks[0];
		op.input2 = checks[1];
		rand = gen.RandInt(1,2);  
		if (rand == 1){return op.input1;}
		else{return op.input2;}}

	else if (inputs == 3){
		op.input1 = checks[0];
		op.input2 = checks[1];
		op.input3 = checks[2];
		rand = gen.RandInt(1,3);
		if (rand == 1){return op.input1;}
		else if (rand == 2){return op.input2;}
		else{return op.input3;}}
}

char chooseUnvisitedWallU(const Cell & left, const Cell & right, const Cell & down){  // for the upper side
	int inputs = 0;
	vector <char> checks;
	if (!left.visited){
		checks.push_back('L');
		inputs += 1;}
	if (!right.visited){
		checks.push_back('r');
		inputs += 1;}
	if (!down.visited){
		checks.push_back('d');
		inputs += 1;}
	RandGen gen; int rand; Options op;
	if (inputs == 1){
		op.input1 = checks[0];
		return op.input1;}

	else if (inputs == 2){
		op.input1 = checks[0];
		op.input2 = checks[1];
		rand = gen.RandInt(1,2);  
		if (rand == 1){return op.input1;}
		else{return op.input2;}}

	else if (inputs == 3){
		op.input1 = checks[0];
		op.input2 = checks[1];
		op.input3 = checks[2];
		rand = gen.RandInt(1,3);
		if (rand == 1){return op.input1;}
		else if (rand == 2){return op.input2;}
		else{return op.input3;}}
}


char chooseUnvisitedWallR(const Cell & left, const Cell & upper, const Cell & down){  // for the right side
	int inputs = 0;
	vector <char> checks;
	if (!left.visited){
		checks.push_back('L');
		inputs += 1;}
	if (!upper.visited){
		checks.push_back('u');
		inputs += 1;}
	if (!down.visited){
		checks.push_back('d');
		inputs += 1;}
	RandGen gen; int rand; Options op;
	if (inputs == 1){
		op.input1 = checks[0];
		return op.input1;}

	else if (inputs == 2){
		op.input1 = checks[0];
		op.input2 = checks[1];
		rand = gen.RandInt(1,2);  
		if (rand == 1){return op.input1;}
		else{return op.input2;}}

	else if (inputs == 3){
		op.input1 = checks[0];
		op.input2 = checks[1];
		op.input3 = checks[2];
		rand = gen.RandInt(1,3);
		if (rand == 1){return op.input1;}
		else if (rand == 2){return op.input2;}
		else{return op.input3;}}
}


char chooseUnvisitedWallB(const Cell & left, const Cell & upper, const Cell & right){  // for the bottom side
	int inputs = 0;
	vector <char> checks;
	if (!left.visited){
		checks.push_back('L');
		inputs += 1;}
	if (!upper.visited){
		checks.push_back('u');
		inputs += 1;}
	if (!right.visited){
		checks.push_back('r');
		inputs += 1;}
	RandGen gen; int rand; Options op;
	if (inputs == 1){
		op.input1 = checks[0];
		return op.input1;}

	else if (inputs == 2){
		op.input1 = checks[0];
		op.input2 = checks[1];
		rand = gen.RandInt(1,2);  
		if (rand == 1){return op.input1;}
		else{return op.input2;}}

	else if (inputs == 3){
		op.input1 = checks[0];
		op.input2 = checks[1];
		op.input3 = checks[2];
		rand = gen.RandInt(1,3);
		if (rand == 1){return op.input1;}
		else if (rand == 2){return op.input2;}
		else{return op.input3;}}
}

/*
In this function, because of the efficiency purposes, I am testing the situations one by one instead of creating a special function.
For each cell 
	if it is suitable to think, 
		the  left  cell is signed as:  1
		the  upper cell is signed as:  2
		the  right cell is signed as:  3
		the  down  cell is signed as:  4
	if not,
		the situation is considered as special condition. and this is explained in comments.
	

If it is available, the upper, left, right and down cells are copied to a Cell object 
so that writing will be shorter while I need to check whether they are visited or not.
(I didn't update the u,r,l,d properties of these Cell objects and the currentCell and newCell because I only need the visitance information.)

After the wall which will be removed, the updates are done on the mat matrix. (to do this, it is passed by reference and non-const)

The logic of the steps for each situation (if else if's) are same.


*/

void generateMaze(Stack <Cell> & mazeStack, int numOfRows, int numOfCols, vector <vector<Cell>> & mat){
	int visitedCells = 0;
	while (visitedCells != (numOfRows*numOfCols))
	{
		RandGen gen;
		int rand;

		Cell currentCell = mazeStack.top();

		if (currentCell.x_coor == 0 && currentCell.y_coor == 0) // left bottom corner
		{
			if (!(mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited))
			{
				mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited = true;
				visitedCells += 1;
			}
			Cell right = mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor+1];
			Cell upper = mat[numOfRows-1-currentCell.y_coor-1][currentCell.x_coor];
			if (upper.visited && right.visited) // backtracking
			{
				mazeStack.pop();
			}
			else
			{
				rand = gen.RandInt(2,3); 
				if (rand == 2){
					Cell newCell(currentCell.x_coor,currentCell.y_coor+1);
					mazeStack.push(newCell);
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].u = 0; 
					mat[numOfRows-1-currentCell.y_coor-1][currentCell.x_coor].d = 0; // update each cell for the change
				}
				else{
					Cell newCell(currentCell.x_coor+1,currentCell.y_coor); 
					mazeStack.push(newCell); 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].r = 0; 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor+1].l = 0;
				}
			}
			
		}


		else if (currentCell.x_coor == 0 && currentCell.y_coor == numOfRows-1) // left upper corner
		{
			Cell down  = mat[numOfRows-1-currentCell.y_coor+1][currentCell.x_coor];  
			Cell right = mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor+1];

			if (!(mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited))
			{
				mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited = true;
				visitedCells += 1;
			}
			rand = gen.RandInt(3,4);
			if (right.visited && down.visited) // backtracking
			{
				mazeStack.pop();
			}
			else{  // there is exactly one unvisited side but which one?
				if (rand == 3){ 

					if (right.visited == false) // add 3 (right)
					{
						Cell newCell(currentCell.x_coor+1,currentCell.y_coor); 
						mazeStack.push(newCell);
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].r = 0;
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor+1].l = 0;

					}
					else // I understand that the unvisited one is the down.
					{
						Cell newCell(currentCell.x_coor,currentCell.y_coor-1); 
						mazeStack.push(newCell); 
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].d = 0;
						mat[numOfRows-1-currentCell.y_coor+1][currentCell.x_coor].u = 0;
					}
				}
				if (rand == 4) // add 4 (down)
				{
					if (down.visited == false)
					{
						Cell newCell(currentCell.x_coor,currentCell.y_coor-1); 
						mazeStack.push(newCell);
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].d = 0;
						mat[numOfRows-1-currentCell.y_coor+1][currentCell.x_coor].u = 0;
					}
					else // I understand that the unvisited one is the right.
					{
						Cell newCell(currentCell.x_coor+1,currentCell.y_coor); 
						mazeStack.push(newCell);
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].r = 0;
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor+1].l = 0;
					}
				}
			}
		}
		else if (currentCell.x_coor == numOfCols-1 && currentCell.y_coor == numOfRows-1) // right upper corner
		{
			Cell down  = mat[numOfRows-1-currentCell.y_coor+1][currentCell.x_coor]; 
			Cell left  = mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor-1];

			rand = gen.RandInt(1,2); // special condition -> 1: left, 2: down 
			if (!(mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited))
			{
				mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited = true;
				visitedCells += 1;
			}
			if (left.visited && down.visited) // backtracking
			{
				mazeStack.pop();
			}
			else{
				if (rand == 1)
				{

					if (left.visited == false)
					{
						Cell newCell(currentCell.x_coor-1, currentCell.y_coor); 
						mazeStack.push(newCell); 
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].l = 0;
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor-1].r = 0;
					}
					else
					{
						Cell newCell(currentCell.x_coor,currentCell.y_coor-1); 
						mazeStack.push(newCell); 
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].d = 0;
						mat[numOfRows-1-currentCell.y_coor+1][currentCell.x_coor].u = 0;
					}
				}
				if (rand == 2)
				{
					if (down.visited == false)
					{
						Cell newCell(currentCell.x_coor,currentCell.y_coor-1); 
						mazeStack.push(newCell); 
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].d = 0;
						mat[numOfRows-1-currentCell.y_coor+1][currentCell.x_coor].u = 0;
					}
					else
					{
						Cell newCell(currentCell.x_coor-1, currentCell.y_coor); 
						mazeStack.push(newCell); 
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].l = 0;
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor-1].r = 0;
					}
				}
			}
		}
		else if (currentCell.x_coor == numOfCols-1 && currentCell.y_coor == 0) // right bottom corner
		{
			Cell left  = mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor-1];
			Cell upper = mat[numOfRows-1-currentCell.y_coor-1][currentCell.x_coor];
			
			rand = gen.RandInt(1,2);
			if (!(mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited))
			{
				mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited = true;
				visitedCells += 1;
			}
			if (left.visited && upper.visited)
			{
				mazeStack.pop();
			}
			else
			{
				if (rand == 1)
				{
					if (left.visited == false)
					{
						Cell newCell(currentCell.x_coor-1, currentCell.y_coor); 
						mazeStack.push(newCell); 
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].l = 0;
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor-1].r = 0;
					}
					else
					{
						Cell newCell(currentCell.x_coor,currentCell.y_coor+1); 
						mazeStack.push(newCell); 
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].u = 0;
						mat[numOfRows-1-currentCell.y_coor-1][currentCell.x_coor].d = 0;
					}
				}
				if (rand == 2)
				{
					if (upper.visited == false)
					{
						Cell newCell(currentCell.x_coor,currentCell.y_coor+1); 
						mazeStack.push(newCell); 
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].u = 0;
						mat[numOfRows-1-currentCell.y_coor-1][currentCell.x_coor].d = 0;
					}
					else
					{
						Cell newCell(currentCell.x_coor-1, currentCell.y_coor); 
						mazeStack.push(newCell); 
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].l = 0;
						mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor-1].r = 0;
					}
				}
			}
		}
		else if (currentCell.x_coor == 0 && (currentCell.y_coor != numOfRows-1 && currentCell.y_coor != 0)) // left edge of the matrix except the corners on that edge.
		{
			Cell upper = mat[numOfRows-1-currentCell.y_coor-1][currentCell.x_coor];
			Cell down  = mat[numOfRows-1-currentCell.y_coor+1][currentCell.x_coor]; 
			Cell right = mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor+1];
		
			if (!(mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited))
			{
				mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited = true;
				visitedCells += 1;
			}
			if (upper.visited && right.visited && down.visited)
			{
				mazeStack.pop();
			}
			else
			{
				char result = chooseUnvisitedWallL(upper, right, down); // randomize between the unvisited cells
				if (result == 'u')
				{
					Cell newCell(currentCell.x_coor,currentCell.y_coor+1); 
					mazeStack.push(newCell); 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].u = 0;
					mat[numOfRows-1-currentCell.y_coor-1][currentCell.x_coor].d = 0;
				}
				else if (result == 'r')
				{
					Cell newCell(currentCell.x_coor+1,currentCell.y_coor); 
					mazeStack.push(newCell); 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].r = 0;
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor+1].l = 0;
				}
				else if (result == 'd')
				{
					Cell newCell(currentCell.x_coor,currentCell.y_coor-1); 
					mazeStack.push(newCell); 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].d = 0;
					mat[numOfRows-1-currentCell.y_coor+1][currentCell.x_coor].u = 0;
				}
			}
		}	
		else if (currentCell.y_coor == numOfRows-1 && (currentCell.x_coor != 0 && currentCell.x_coor != numOfCols-1)) // upper edge of the matrix except the corners on that edge.
		{
			if (!(mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited))
			{
				mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited = true;
				visitedCells += 1;
			}
			Cell down  = mat[numOfRows-1-currentCell.y_coor+1][currentCell.x_coor]; 
			Cell right = mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor+1];
			Cell left = mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor-1];

			if (left.visited && down.visited && right.visited)
			{
				mazeStack.pop();
			}
			else
			{
				char result = chooseUnvisitedWallU(left, right, down);
				if (result == 'L')
				{
					Cell newCell(currentCell.x_coor-1,currentCell.y_coor); 
					mazeStack.push(newCell); 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].l = 0;
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor-1].r = 0;
				}
				else if (result == 'r')
				{
					Cell newCell(currentCell.x_coor+1,currentCell.y_coor); 
					mazeStack.push(newCell); 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].r = 0;
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor+1].l = 0;
				}
				else if (result == 'd')
				{
					Cell newCell(currentCell.x_coor,currentCell.y_coor-1); 
					mazeStack.push(newCell); 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].d = 0;
					mat[numOfRows-1-currentCell.y_coor+1][currentCell.x_coor].u = 0;
				}
			}
		}
		else if (currentCell.x_coor == numOfCols-1 && (currentCell.y_coor != numOfRows-1 && currentCell.y_coor != 0)) // right edge of the matrix except the corners on that edge.
		{
			Cell upper = mat[numOfRows-1-currentCell.y_coor-1][currentCell.x_coor];
			Cell down  = mat[numOfRows-1-currentCell.y_coor+1][currentCell.x_coor]; 
			Cell left  = mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor-1];

			if (!(mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited))
			{
				mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited = true;
				visitedCells += 1;
			}

			if (upper.visited && left.visited && down.visited)
			{
				mazeStack.pop();
			}
			else
			{
				char result = chooseUnvisitedWallR(left, upper, down);
				if (result == 'L')
				{
					Cell newCell(currentCell.x_coor-1,currentCell.y_coor); 
					mazeStack.push(newCell); 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].l = 0;
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor-1].r = 0;
				}
				else if (result == 'u')
				{
					Cell newCell(currentCell.x_coor,currentCell.y_coor+1); 
					mazeStack.push(newCell); 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].u = 0;
					mat[numOfRows-1-currentCell.y_coor-1][currentCell.x_coor].d = 0;
				}
				else if (result == 'd')
				{
					Cell newCell(currentCell.x_coor,currentCell.y_coor-1); 
					mazeStack.push(newCell); 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].d = 0;
					mat[numOfRows-1-currentCell.y_coor+1][currentCell.x_coor].u = 0;
				}
			}
		}
		else if (currentCell.y_coor == 0 && (currentCell.x_coor != 0 && currentCell.x_coor != numOfCols-1)) // bottom edge of the matrix except the corners on that edge.
		{
			Cell right = mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor+1];
			Cell left = mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor-1];
			Cell upper = mat[numOfRows-1-currentCell.y_coor-1][currentCell.x_coor];

			if (!(mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited))
			{
				mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited = true;
				visitedCells += 1;
			}
			if (left.visited && upper.visited && right.visited)
			{
				mazeStack.pop();
			}
			else
			{
				char result = chooseUnvisitedWallB(left, upper, right);
				if (result == 'L')
				{
					Cell newCell(currentCell.x_coor-1,currentCell.y_coor); 
					mazeStack.push(newCell); 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].l = 0;
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor-1].r = 0;
				}
				else if (result == 'u')
				{
					Cell newCell(currentCell.x_coor,currentCell.y_coor+1); 
					mazeStack.push(newCell); 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].u = 0;
					mat[numOfRows-1-currentCell.y_coor-1][currentCell.x_coor].d = 0;
				}
				else if (result == 'r')
				{
					Cell newCell(currentCell.x_coor+1,currentCell.y_coor); 
					mazeStack.push(newCell);
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].r = 0;
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor+1].l = 0;
				}
			}
		}
		else // if the cell is neither on the corner or the edges
		{
			if (!(mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited))
			{
				mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited = true;
				visitedCells += 1;
			}
			Cell down  = mat[numOfRows-1-currentCell.y_coor+1][currentCell.x_coor]; 
			Cell right = mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor+1];
			Cell left = mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor-1];
			Cell upper = mat[numOfRows-1-currentCell.y_coor-1][currentCell.x_coor];

			Cell newCell;
			if (left.visited && upper.visited && right.visited && down.visited)
			{
				mazeStack.pop();
			}
			else
			{
				char result = chooseUnvisitedWall(left, upper, right, down);
				if (result == 'L')
				{
					Cell newCell(currentCell.x_coor-1,currentCell.y_coor); 
					mazeStack.push(newCell); 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].l = 0;
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor-1].r = 0;
				}
				else if (result == 'u')
				{
					Cell newCell(currentCell.x_coor,currentCell.y_coor+1); 
					mazeStack.push(newCell); 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].u = 0;
					mat[numOfRows-1-currentCell.y_coor-1][currentCell.x_coor].d = 0;
				}
				else if (result == 'r')
				{
					Cell newCell(currentCell.x_coor+1,currentCell.y_coor); 
					mazeStack.push(newCell); 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].r = 0;
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor+1].l = 0;
				}
				else if (result == 'd')
				{
					Cell newCell(currentCell.x_coor,currentCell.y_coor-1);
					mazeStack.push(newCell); 
					mat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].d = 0;
					mat[numOfRows-1-currentCell.y_coor+1][currentCell.x_coor].u = 0;
				}
			}
		}
	}
}

/*
This function will take a copy of the generated matrix but with a special change.
In this copy, all of the cells are signed as unvisited 
so that I can keep track of I visit that cell during the path finding process.
mazeStack will keep the cells which will be used finding the destination coordinate.

the order of the conditions was chosen randomly. 
Every time, it will find an unvisited way and at the end, the destination will be cathced.

after I push a cell to the stack, always check if it has the destination coordinates.

*/

void findPath(Stack <Cell> & mazeStack, vector<vector<Cell>> & copyMat, int entryX, int entryY, int exitX, int exitY){
	int numOfRows = copyMat.size();
	Cell currentCell = mazeStack.top();
	bool isNotFound = true; // check if I reached the destination coordinate
	while (isNotFound)
	{
		currentCell = mazeStack.top();
		Cell newCell;
		if (!(copyMat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited))
			{
				copyMat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].visited = true;
			}
		
		if (copyMat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].l == 0 && copyMat[numOfRows-1-currentCell.y_coor][currentCell.x_coor-1].visited == false)
		{
			// turn left
			newCell.x_coor = currentCell.x_coor-1;
			newCell.y_coor = currentCell.y_coor;
			mazeStack.push(newCell);
			if (mazeStack.top().x_coor == exitX && mazeStack.top().y_coor == exitY)
			{
				isNotFound = false;
			}
		}
		else if(copyMat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].r == 0 && copyMat[numOfRows-1-currentCell.y_coor][currentCell.x_coor+1].visited == false) 
		{
			// turn right
			newCell.x_coor = currentCell.x_coor+1; 
			newCell.y_coor = currentCell.y_coor; 
			mazeStack.push(newCell);
			if (mazeStack.top().x_coor == exitX && mazeStack.top().y_coor == exitY)
			{
				isNotFound = false;
			}
		}
		else if (copyMat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].u == 0 && copyMat[numOfRows-1-currentCell.y_coor-1][currentCell.x_coor].visited == false) 
		{
			// go up
			newCell.x_coor = currentCell.x_coor; 
			newCell.y_coor = currentCell.y_coor+1; 
			mazeStack.push(newCell);
			if (mazeStack.top().x_coor == exitX && mazeStack.top().y_coor == exitY)
			{
				isNotFound = false;
			}
		}
		else if (copyMat[numOfRows-1-currentCell.y_coor][currentCell.x_coor].d == 0 && copyMat[numOfRows-1-currentCell.y_coor+1][currentCell.x_coor].visited == false)
		{
			// go down
			newCell.x_coor = currentCell.x_coor;  
			newCell.y_coor = currentCell.y_coor-1; 
			mazeStack.push(newCell);
			if (mazeStack.top().x_coor == exitX && mazeStack.top().y_coor == exitY)
			{
				isNotFound = false;
			}
		}
		else // there is no unvisited cell. backtrack.
		{
			mazeStack.pop(); 
		}
	}
}
	
int main(){
	int numOfMazes, numOfRows, numOfCols, entryX, entryY, exitX, exitY;
	int mazeID;
	string maze_ID;
	cout << "Enter the number of mazes: ";
	cin >> numOfMazes;
	cout << "Enter the number of rows and columns (M and N): ";
	cin >> numOfRows >> numOfCols;
	
	vector <vector<vector<Cell>>> mazes;
	ofstream out;
	string mazeFile;
	for (int a = 0; a < numOfMazes; a++)
	{
		vector <vector<Cell>> maze(numOfRows, vector<Cell>(numOfCols));
		createMazeMatrix(maze, numOfRows, numOfCols);
		Stack <Cell> MazeStack;
		Cell zeroCell(0,0);
		MazeStack.push(zeroCell);
		maze_ID = itoa(a+1);
		generateMaze(MazeStack, numOfRows, numOfCols, maze);
		mazes.push_back(maze);
		mazeFile = "maze_" + maze_ID + ".txt";
		out.open(mazeFile.c_str());
		out << numOfRows << " " << numOfCols << endl;
		int i = maze.size()-1;
		while( i >= 0){
			int j = 0;
			while (j < maze[0].size())
			{
				out << "x=" << maze[i][j].x_coor << " y=" << maze[i][j].y_coor << " l=" <<  maze[i][j].l << " r=" <<  maze[i][j].r << " u=" <<  maze[i][j].u << " d=" <<  maze[i][j].d << endl;
				j++;
			
			}
			i--;
		}
		out.close();

	}
	cout << "All mazes are generated." << endl;
	cout << endl;
	cout << "Enter a maze ID between 1 to " << numOfMazes << " inclusive to find a path: ";
	cin >> mazeID;
	vector <vector<Cell>> copyMaze = mazes[mazeID-1];
	for (int i = 0; i < copyMaze.size(); i++)  // set all cells as unvisited to use in path finding function.
	{
		for (int j = 0; j < copyMaze[0].size(); j++)
		{
			copyMaze[i][j].visited = false;
		}
	}
	Stack <Cell> PathStack;
	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> entryX >> entryY;
	Cell starting(entryX, entryY);
	PathStack.push(starting);
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin >> exitX >> exitY;
	findPath(PathStack, copyMaze, entryX, entryY, exitX, exitY);
	ofstream out2;
	string path_txt = "maze_" + itoa(mazeID) + "_path_" + itoa(entryX) + "_" + itoa(entryY) + "_" + itoa(exitX) + "_" + itoa(exitY) + ".txt";
	out2.open(path_txt.c_str());
	Stack <Cell> TempStack;
	while (!PathStack.isEmpty())
	{
		Cell element = PathStack.topAndPop();
		TempStack.push(element);

	}
	while (!TempStack.isEmpty())
	{
		out2 << TempStack.top().x_coor << " " << TempStack.top().y_coor << endl;
		TempStack.pop();
	}
	out2.close();
	return 0;
}
