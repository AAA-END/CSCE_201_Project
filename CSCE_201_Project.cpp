#include <iostream>
#include <cstdlib> //for rand() 
#include <ctime> // for time
#include <conio.h> //input handling

#define KEY_UP    72 
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80

using namespace std;

int intCheck(char check_num[]);

void showMenu();

int getAnswer();

int setSpeed();

void playGame();




int main()
{
	int menu_mode = 0;
	int game_speed = 20;

	while (menu_mode != 3) {
		showMenu();
		menu_mode = getAnswer();

		if (menu_mode == 1) {
			playGame();
		}
		else if (menu_mode == 2) {
			game_speed = setSpeed();
		}
	}
}





int intCheck(char check_num[])
{
	bool check_again = false;
	for (int i = 0; i < 9; i++) {
		if (check_again == true)
			break;
		if (check_num[i] == 0)
			break;
		if (!(isdigit(check_num[i]))) {
			check_again = true;
		}
	}

	if (check_again == true) {
		cout << "Error: Please enter a valid number" << endl;
		cout << "Please try again: ";
		cin >> check_num;
		intCheck(check_num);
	}
	else {
		return atoi(check_num);
	}
}

void showMenu() 
{
	cout << "1. Play game\n";
	cout << "2. Adjust settings\n";
	cout << "3. Exit game\n";
}

int getAnswer()
{
	int menu_answer = 0;
	char input_answer[9];
	while ((menu_answer > 3) || (menu_answer < 1)) {
		cout << "\nEnter an input number: ";
		cin >> input_answer;
		menu_answer = intCheck(input_answer);
		if ((menu_answer > 3) || (menu_answer < 1))
			cout << "Error: input number out of range";
	}
	return menu_answer;
}

void playGame() {
	cout << "game working" << endl;
	int input, ex;
	int randa = 0;
	int randb = 0;
	const int LENGTH = 10;
	const int WIDTH = 10;
	int playerLength = 1;
	bool life = true;
	bool test = true;
	bool win = false;
	int playerDirection = 2; //1 = north (check map[x-1][x]), 2 = east (check map[x][x+1]), 3 = south (check map[x+1][x]), 4 = west (check map[x][x - 1])
	int map[LENGTH + 2][WIDTH + 2] = {0}; //most of the game will be handled within an array

	//populate borders with 2 (1 is fruit, 2 is wall, 3 is body, 4 is tail, 5 is head)
	for (int i = 0; i < LENGTH + 2; i++)
		for (int j = 0; j < WIDTH + 2; j++){
			if (i == 0)
				map[i][j] = 2;
			if (j == 0)
				map[i][j] = 2;
			if (i == (LENGTH + 1))
				map[i][j] = 2;
			if (j == (WIDTH + 1))
				map[i][j] = 2;
			} 

	//set position of head
	map[5][5] = 5;

	//place first fruit
	while (map[randa][randb] != 0){  //TODO: turn this thing into a function
	randa = rand() % 10 + 1;
	randb = rand() % 10 + 1;
	}
	map[randa][randb] = 1;

	for (int i = 0; i < LENGTH + 2; i++){
		for (int j = 0; j < WIDTH + 2; j++){
			cout << map[i][j];
		}
		cout << '\n';
	}

	while (life == true){
	test = true;
	//basic game loop:
	//1. check if the user has input a direction, update direction if they did
	input = getch();
	while(test == true){
	if (!(input && input != 224))
	switch(ex = getch())
	{
		case KEY_UP     /* H */:
			if (playerDirection != 3)
				playerDirection = 1;
				test = false;
			break;
		case KEY_DOWN   /* K */:
			if (playerDirection != 1)
				playerDirection = 3;
				test = false;
			break;
		case KEY_LEFT   /* M */:
			if (playerDirection != 2)
				playerDirection = 4;
				test = false;
			break;
		case KEY_RIGHT: /* P */
			if (playerDirection != 4)
				playerDirection = 2;
				test = false;
			break;
	}
}
	//2. move the snake forward
	test = true;
	for (int i = 0; i < LENGTH + 2; i++) //This can be made more efficient by not scanning border elements
		for (int j = 0; j < WIDTH + 2; j++){
			if (test == true){
			if (map[i][j] == 5){
				test = false;
				if (playerDirection == 1){ //north
					map[i-1][j] = 5 + map[i-1][j];
				}
				if (playerDirection == 2){ //east
					map[i][j+1] = 5 + map[i][j+1];
				}
				if (playerDirection == 3){ //south
					map[i+1][j] = 5 + map[i+1][j];
				}
				if (playerDirection == 4){ //west
					map[i][j - 1] = 5 + map[i][j - 1];
				}
				if (playerLength = 1) //TODO: turn this check into a function
					map[i][j] = 0;
				else if (playerLength = 2)
					map[i][j] = 5;
				else
					map[i][j] = 3;
			}
		}
		}
	//3. check if a fruit has been eaten, update length and place a new fruit if it has (also checks other collision)
	for (int i = 0; i < LENGTH + 2; i++)
		for (int j = 0; j < WIDTH + 2; j++){
			if (map[i][j] == 6){
				map[i][j] = 5;
				playerLength++;
				if (playerLength >= (LENGTH*WIDTH))
					win = true;
				else{
				while (map[randa][randb] != 0){
					randa = rand() % 10 + 1;
					randb = rand() % 10 + 1;
					}
					map[randa][randb] = 1;
				}
			}
			else if (map[i][j] >= 7){
				life = false;
				//need a function to handle dying
			}
		}
	//4. update the drawing (clear it and then redraw it with the change above made)
	for (int i = 0; i < LENGTH; i++)
		cout << '\n';
	for (int i = 0; i < LENGTH + 2; i++){
		for (int j = 0; j < WIDTH + 2; j++){
			cout << map[i][j];
		}
		cout << '\n';
	
	//it may be worth looking into the library pdcurses/ncurses to make the game run better
	}
	cout << playerDirection;
}
}

int setSpeed() {
	cout << "menu working" << endl;
	return 20;
}
