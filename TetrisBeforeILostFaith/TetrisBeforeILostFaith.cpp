// TetrisBeforeILostFaith.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>		
#include <time.h>		
#include <Windows.h>

using namespace std;

// Function Prototypes


int randomizePieces();
bool deleteLine();
bool gameOver();
//int gameScore(int score);
void userInput();
enum { LEFT_ARROW = 37, UP_ARROW = 38, RIGHT_ARROW = 39, DOWN_ARROW = 40 };
int speed = 100;
int score = 0;

void setCursorTo(int x, int y);
const int width = 12;
const int height = 25;
int shapeNumber;



class TetrisShape
{
public:

	int shapeType;
	int shapeTopLeftX = 6;
	int shapeTopLeftY = 0;

	char shapeArray[4][4];

	void createShape(int shapeType)
	{
		switch (shapeType) {
		case 0: //create L shape
			shapeArray[0][0] = ' '; shapeArray[1][0] = 'X'; shapeArray[2][0] = ' '; shapeArray[3][0] = ' ';
			shapeArray[0][1] = ' '; shapeArray[1][1] = 'X'; shapeArray[2][1] = ' '; shapeArray[3][1] = ' ';
			shapeArray[0][2] = ' '; shapeArray[1][2] = 'X'; shapeArray[2][2] = 'X'; shapeArray[3][2] = ' ';
			shapeArray[0][3] = ' '; shapeArray[1][3] = ' '; shapeArray[2][3] = ' '; shapeArray[3][3] = ' ';
			break;
		case 1: //create 7 shape
			shapeArray[0][0] = ' '; shapeArray[1][0] = 'X'; shapeArray[2][0] = 'X'; shapeArray[3][0] = ' ';
			shapeArray[0][1] = ' '; shapeArray[1][1] = ' '; shapeArray[2][1] = 'X'; shapeArray[3][1] = ' ';
			shapeArray[0][2] = ' '; shapeArray[1][2] = ' '; shapeArray[2][2] = 'X'; shapeArray[3][2] = ' ';
			shapeArray[0][3] = ' '; shapeArray[1][3] = ' '; shapeArray[2][3] = ' '; shapeArray[3][3] = ' ';
			break;
		case 2: //create the block shape
			shapeArray[0][0] = ' '; shapeArray[1][0] = 'X'; shapeArray[2][0] = 'X'; shapeArray[3][0] = ' ';
			shapeArray[0][1] = ' '; shapeArray[1][1] = 'X'; shapeArray[2][1] = 'X'; shapeArray[3][1] = ' ';
			shapeArray[0][2] = ' '; shapeArray[1][2] = ' '; shapeArray[2][2] = ' '; shapeArray[3][2] = ' ';
			shapeArray[0][3] = ' '; shapeArray[1][3] = ' '; shapeArray[2][3] = ' '; shapeArray[3][3] = ' ';
			break;
		case 3: //create the I shape
			shapeArray[0][0] = ' '; shapeArray[1][0] = 'X'; shapeArray[2][0] = ' '; shapeArray[3][0] = ' ';
			shapeArray[0][1] = ' '; shapeArray[1][1] = 'X'; shapeArray[2][1] = ' '; shapeArray[3][1] = ' ';
			shapeArray[0][2] = ' '; shapeArray[1][2] = 'X'; shapeArray[2][2] = ' '; shapeArray[3][2] = ' ';
			shapeArray[0][3] = ' '; shapeArray[1][3] = 'X'; shapeArray[2][3] = ' '; shapeArray[3][3] = ' ';
			break;
		case 4: //create the S shape
			shapeArray[0][0] = ' '; shapeArray[1][0] = ' '; shapeArray[2][0] = 'X'; shapeArray[3][0] = ' ';
			shapeArray[0][1] = ' '; shapeArray[1][1] = 'X'; shapeArray[2][1] = 'X'; shapeArray[3][1] = ' ';
			shapeArray[0][2] = ' '; shapeArray[1][2] = 'X'; shapeArray[2][2] = ' '; shapeArray[3][2] = ' ';
			shapeArray[0][3] = ' '; shapeArray[1][3] = ' '; shapeArray[2][3] = ' '; shapeArray[3][3] = ' ';
			break;
		case 5: //create the Z shape
			shapeArray[0][0] = ' '; shapeArray[1][0] = 'X'; shapeArray[2][0] = ' '; shapeArray[3][0] = ' ';
			shapeArray[0][1] = ' '; shapeArray[1][1] = 'X'; shapeArray[2][1] = 'X'; shapeArray[3][1] = ' ';
			shapeArray[0][2] = ' '; shapeArray[1][2] = ' '; shapeArray[2][2] = 'X'; shapeArray[3][2] = ' ';
			shapeArray[0][3] = ' '; shapeArray[1][3] = ' '; shapeArray[2][3] = ' '; shapeArray[3][3] = ' ';
			break;
		case 6: //create the T shape
			shapeArray[0][0] = ' '; shapeArray[1][0] = ' '; shapeArray[2][0] = ' '; shapeArray[3][0] = ' ';
			shapeArray[0][1] = 'X'; shapeArray[1][1] = 'X'; shapeArray[2][1] = 'X'; shapeArray[3][1] = ' ';
			shapeArray[0][2] = ' '; shapeArray[1][2] = 'X'; shapeArray[2][2] = ' '; shapeArray[3][2] = ' ';
			shapeArray[0][3] = ' '; shapeArray[1][3] = ' '; shapeArray[2][3] = ' '; shapeArray[3][3] = ' ';
			break;
		}
	}
};




int _tmain(int argc, _TCHAR* argv[])
{

	//do {
	char bucket[width][height];
	TetrisShape shape;
	bool lowerShape(TetrisShape& shape, char bucket[width][height]);
	void updateBucket(TetrisShape localTetrisShape, char bucket[width][height]);
	void displaybucket(char bucket[width][height]);
	int deleteLines(char bucket[width][height], int y);
	void createBucket(char bucket[width][height]);
	void clearShape(TetrisShape localTetrisShape, char bucket[width][height]);
	int movePiece(int input, TetrisShape& shape, char bucket[width][height]);
	int getInput();
	bool gameOver = false;
	bool descend = false;
	int input;

	createBucket(bucket);
	randomizePieces();
	shape.createShape(shapeNumber);
	updateBucket(shape, bucket);
	displaybucket(bucket);
	while (!gameOver) {
		Sleep(speed);
		speed = 100;
		displaybucket(bucket);
		clearShape(shape, bucket);
		for (int x = 1; x < width; x++) {//Checks to see if game is over.
			if (bucket[x][1] == 'X') {
				gameOver = true;
			}
		}

		input = getInput();
		if (input) movePiece(input, shape, bucket);

		if (!lowerShape(shape, bucket)) {
			updateBucket(shape, bucket);
			//linesCleared += clearLines(bucket, shape.shapeTopLeftY);
			randomizePieces();
			shape.createShape(shapeNumber);
			updateBucket(shape, bucket);
		}
		else {
			if (descend) {
				shape.shapeTopLeftY = shape.shapeTopLeftY + 1;
				descend = false;
			}
			else descend = true;
		}
		updateBucket(shape, bucket);
		Sleep(speed);
		cout << score << endl; //Score is always displayed.
	}
	cout << "Game Over, your score is: " << score << endl;

	//} while (gameOver);//Game will continue until gameOver returns True.

	system("pause");
	return 0;
}

void createBucket(char bucket[width][height]) {
	// Create another 2D array that will become the playing field.
	

	for (int i = 0; i < height; i++) {		
		bucket[0][i] = '|';
		for (int j = 1; j < 11; j++) {
			bucket[j][i] = ' ';
		}
		bucket[11][i] = '|';
	}
	for (int j = 0; j < width; j++) {
		bucket[j][24] = '-';
	}
}

//int deleteLines(char bucket[width][height], int y) {	//Clears completed lines and adds points.	
//	bool clearedLines[4] = { true, true, true, true };// Checks for completed lines.
//
//	for (int j = 0; j < 4; j++) {
//		for (int i = 1; i < 11; i++) {
//			if (bucket[i][y + j] != 'X') {
//				clearedLines[j] = false;
//				break;
//			}
//		}
//	}
//
//	if (clearedLines[0] == true || clearedLines[1] == true ||
//		clearedLines[2] == true || clearedLines[3] == true) {
//		for (int j = 0; j < 4; j++) {
//			if (clearedLines[j] == true) {
//				for (int i = 1; i < 11; i++) bucket[i][y + j] = ' ';
//				score = score + 100; // Score 100 points per line cleared.
//			}
//		}
//		displaybucket(bucket);
//		Sleep(100);
//
//		for (int j = 0; j < 4; j++) {
//			if (clearedLines[j] == true) {
//				for (int i = 1; i < 11; i++) bucket[i][y + j] = 'X';
//			}
//		}
//		displaybucket(bucket);
//		Sleep(100);
//
//		for (int j = 0; j < 4; j++) {
//			if (clearedLines[j] == true) {
//				for (int i = 1; i < 11; i++) bucket[i][y + j] = ' ';
//			}
//		}
//		displaybucket(bucket);
//		Sleep(100);
//		int n = 0;
//		for (int l = 3; l >= 0; l--) {
//			if (clearedLines[l] == true) {
//				n++;
//				for (int j = y + l + n - 1; j > 0; j--) {
//					for (int i = 1; i < 11; i++) bucket[i][j] = bucket[i][j - 1];
//				}
//			}
//		}
//		displaybucket(bucket);
//		Sleep(100);
//
//		return n;
//	}
//	else return 0;
//}

int randomizePieces() {

	srand((unsigned int)time(0));
	shapeNumber = rand() % 7;
	return shapeNumber;
}
void updateBucket(TetrisShape localTetrisShape, char bucket[width][height]) { // Redraws the bucket.
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (localTetrisShape.shapeArray[i][j] == 'X') {
				bucket[i + localTetrisShape.shapeTopLeftX][j + localTetrisShape.shapeTopLeftY] = localTetrisShape.shapeArray[i][j];
			}
		}
	}
}

void clearShape(TetrisShape localTetrisShape, char bucket[width][height]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (localTetrisShape.shapeArray[i][j] == 'X') {
				bucket[i + localTetrisShape.shapeTopLeftX][j + localTetrisShape.shapeTopLeftY] = ' ';
			}
		}
	}
}

int getInput() { // Recieves key input.
	if (GetAsyncKeyState(LEFT_ARROW)) return LEFT_ARROW;
	else if (GetAsyncKeyState(RIGHT_ARROW)) return RIGHT_ARROW;
	else if (GetAsyncKeyState(UP_ARROW)) return UP_ARROW;
	else if (GetAsyncKeyState(DOWN_ARROW)) return DOWN_ARROW;
	else return 0;
}

bool lowerShape(TetrisShape& shape, char bucket[width][height]) { //Makes the Piece descend.
	int x = shape.shapeTopLeftX, y = shape.shapeTopLeftY;

	for (int i = 0; i < 4; i++) {
		for (int j = 3; j >= 0; j--) {
			if (shape.shapeArray[i][j] == 'X') {
				if (bucket[i + x][j + y + 1] != ' ') return 0;
				else break;
			}
		}
	}

	return 1;
}

int movePiece(int input, TetrisShape& shape, char bucket[width][height]) { //Allows for Piece movement
	int x = shape.shapeTopLeftX;
	int y = shape.shapeTopLeftY;
	switch (input) {
	case DOWN_ARROW: //Just decreases sleep time.
		speed = speed / 8;
		break;
	case RIGHT_ARROW: // Redraws the piece further to the right.
		for (int j = 0; j < 4; j++) {
			for (int i = 3; i >= 0; i--) {
				if (shape.shapeArray[i][j] == 'X') {
					if (bucket[i + x + 1][j + y] != ' ') return 0;
					else break;
				}
			}
		}
		shape.shapeTopLeftX++;
		break;
	case LEFT_ARROW: // Redraws the piece to the left
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 4; i++) {
				if (shape.shapeArray[i][j] == 'X') {
					if (bucket[i + x - 1][j + y] != ' ') return 0;
					else break;
				}
			}
		}
		shape.shapeTopLeftX--;
		break;
	case UP_ARROW: // Rotates the piece
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 4; i++) {
				if (shape.shapeArray[i][j] == 'X') {
					if (bucket[(3 - j) + x][i + y] != ' ') return 0;

				}
			}
		}

			char temp = shape.shapeArray[0][1];
		shape.shapeArray[0][1] = shape.shapeArray[1][3];
		shape.shapeArray[1][3] = shape.shapeArray[3][2];
		shape.shapeArray[3][2] = shape.shapeArray[2][0];
		shape.shapeArray[2][0] = temp;

		temp = shape.shapeArray[0][2];
		shape.shapeArray[0][2] = shape.shapeArray[2][3];
		shape.shapeArray[2][3] = shape.shapeArray[3][1];
		shape.shapeArray[3][1] = shape.shapeArray[1][0];
		shape.shapeArray[1][0] = temp;

		temp = shape.shapeArray[1][1];
		shape.shapeArray[1][1] = shape.shapeArray[1][2];
		shape.shapeArray[1][2] = shape.shapeArray[2][2];
		shape.shapeArray[2][2] = shape.shapeArray[2][1];
		shape.shapeArray[2][1] = temp;
		break;
	}
}

bool gameOver() {
	// Determine if the player has lost and return True when the game is lost.
	char again;
	cout << "Inside the gameOver function" << endl;
	cout << "Do you want to keep going?(Y/N): ";
	cin >> again;
	if ((again = 'Y') || (again = 'y')) {
		return true;
	}
	else {
		return false;
	}
}
void displaybucket(char bucket[width][height]) {
	for (int i = 0; i < height; i++) {
		setCursorTo(30, i);
		for (int j = 0; j < width; j++) {
			cout << bucket[j][i];
		}
		cout << endl;
	}
	cout << endl;
}
void setCursorTo(int x, int y)
{
	HANDLE handle;
	COORD position;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(handle, position);
}


