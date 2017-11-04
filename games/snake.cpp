#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool gameOver;
const int width = 24;
const int height = 24;
int x, y, fruitX, fruitY, obsX, obsY, score;
int speed = 200;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup(){
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	obsX = rand() % width;
	obsY = rand() % height;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw(){
	system("cls");
	for (int i = 0; i < width+2; i++) cout << "#";
	cout << endl;


	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			if (j == 0) cout << "#";
			if (i == y && j == x) cout << "O";
			else if (i == fruitX && j == fruitY) cout << "F";
			else if (i == obsX && j == obsY) cout << "X";
			else{
				bool print = false;
				for (int k = 0; k < nTail; k++){
					if (tailX[k] == j && tailY[k] == i){
						print = true;
						cout << "o";
					}
				}
				if (!print)
					cout << " ";
			}
				
			if (j == width - 1) cout << "#";
		}
		cout << endl;
	}


	for (int i = 0; i < width+2; i++) cout << "#";
	cout << endl;
	cout << endl << "Score: " << score << endl;
}

void Input(){
	if (_kbhit()){
		switch (_getch()){
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic(){
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++){
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}


	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	if (x == obsY && y == obsX){
		score -= 20;
		nTail--;
		obsX = rand() % width;
		obsY = rand() % height;
	}
	if (x == fruitY && y == fruitX){
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
		speed -= 10;
	}
	if (score < 0)
		gameOver = true;
}

int main(){
	Setup();
	while (!gameOver){
		Draw();
		Input();
		Logic();
		Sleep(speed);
	}
	cout << "GAME OVER" << endl;
	cin.get();
	return 0;
}