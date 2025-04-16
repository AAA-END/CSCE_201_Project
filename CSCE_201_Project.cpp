#include <iostream>
#include <string>
#include <cstdlib> //for rand() 
#include <chrono> // for time
#include <conio.h> //input handling
#include <fstream> //scoreboard management

#define KEY_UP    72 
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80

using namespace std;

int intCheck(char check_num[]);

void showMenu();

int getAnswer();

int setSpeed();

void trackScores();

void playGame(float speed);




int main()
{
	int menu_mode = 0;
	float game_speed = 20;

	while (menu_mode != 4) {
		showMenu();
		menu_mode = getAnswer();

		if (menu_mode == 1) {
			playGame(game_speed);
		}
		else if (menu_mode == 2) {
			game_speed = setSpeed(); //we could add a setting to let user adjust the width of the map display
		}
		else if (menu_mode == 3) {
			trackScores();
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
	cout << "\nSNAKE++\n\n";
	cout << "-----------------------------------\n";
	cout << "1. Play game\n";
	cout << "2. Adjust speed settings\n";
	cout << "3. Score history\n";
	cout << "4. Exit game\n";
}

int getAnswer()
{
	int menu_answer = 0;
	char input_answer[9];
	while ((menu_answer > 4) || (menu_answer < 1)) {
		cout << "\nEnter an input number: ";
		cin >> input_answer;
		menu_answer = intCheck(input_answer);
		if ((menu_answer > 4) || (menu_answer < 1))
			cout << "Error: input number out of range";
	}
	return menu_answer;
}

void playGame(float speed) {
	cout << "game working" << endl;
	int input, ex;
	int randa = 0;
	int randb = 0;
	int ruler = 0;
	const int LENGTH = 10;
	const int WIDTH = 10;
	int playerLength = 1;
	bool life = true;
	bool test = true;
	bool win = false;
	bool eatFruit = false;
	int playerDirection = 2; //1 = north (check map[x-1][x]), 2 = east (check map[x][x+1]), 3 = south (check map[x+1][x]), 4 = west (check map[x][x - 1])
	int map[LENGTH + 2][WIDTH + 2] = { 0 }; //most of the game will be handled within an array

	//populate borders with -2
	for (int i = 0; i < LENGTH + 2; i++)
		for (int j = 0; j < WIDTH + 2; j++) {
			if (i == 0)
				map[i][j] = -2;
			if (j == 0)
				map[i][j] = -2;
			if (i == (LENGTH + 1))
				map[i][j] = -2;
			if (j == (WIDTH + 1))
				map[i][j] = -2;
		}


	//set position of head
	map[5][5] = 1;

	//place first fruit
	while (map[randa][randb] != 0) {
		randa = rand() % 10 + 1;
		randb = rand() % 10 + 1;
	}
	map[randa][randb] = 1000;

	for (int i = 0; i < LENGTH + 2; i++) { //TODO: make a proper start screen
		for (int j = 0; j < WIDTH + 2; j++) {
			cout << map[i][j];
		}
		cout << '\n';
	}

	while (life == true) {
		test = true;
		//basic game loop:

		//1. check if the user has input a direction, update direction if they did
		auto tstart = std::chrono::high_resolution_clock::now();
		while (std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - tstart).count() < (speed / 50.0)) {
			if (_kbhit()) {
				input = _getch();
				while (test == true) {
					if (!(input && input != 224))
						switch (ex = _getch())
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
			}
		}


		//2. move the snake forward
		//move snake body
		if (playerLength > 1) {
			for (int f = playerLength; f > 0; f--) {
				for (int i = 0; i < LENGTH + 2; i++)
					for (int j = 0; j < WIDTH + 2; j++) {
						if (eatFruit == false) {
							if (map[i][j] == f) {
								if (f == playerLength)
									map[i][j] = 0;
								else
									map[i][j] = map[i][j] + 1;
							}
						}
						else
							if (map[i][j] == f)
								map[i][j] = map[i][j] + 1;
					}
				//}
			}
		}
		//move snake head
		test = true;
		for (int i = 0; i < LENGTH + 2; i++) //This can be made more efficient by not scanning border elements
			for (int j = 0; j < WIDTH + 2; j++) {
				if (test == true) {
					if (playerLength == 1) {
						if (map[i][j] == 1) {
							test = false;
							if (playerDirection == 1) { //north
								map[i - 1][j] = 1 + map[i - 1][j];
							}
							if (playerDirection == 2) { //east
								map[i][j + 1] = 1 + map[i][j + 1];
							}
							if (playerDirection == 3) { //south
								map[i + 1][j] = 1 + map[i + 1][j];
							}
							if (playerDirection == 4) { //west
								map[i][j - 1] = 1 + map[i][j - 1];
							}
							map[i][j] = 0;
						}
					}
					else {
						if (map[i][j] == 2) {
							test = false;
							if (playerDirection == 1) { //north
								map[i - 1][j] = 1 + map[i - 1][j];
							}
							if (playerDirection == 2) { //east
								map[i][j + 1] = 1 + map[i][j + 1];
							}
							if (playerDirection == 3) { //south
								map[i + 1][j] = 1 + map[i + 1][j];
							}
							if (playerDirection == 4) { //west
								map[i][j - 1] = 1 + map[i][j - 1];
							}
						}

					}
				}
			}


		test = true;
		eatFruit = false;
		//3. check if a fruit has been eaten, update length and place a new fruit if it has (also checks other collision)
		for (int i = 0; i < LENGTH + 2; i++)
			for (int j = 0; j < WIDTH + 2; j++) {
				if (map[i][j] == 1001) {
					test = false;
					eatFruit = true;
					map[i][j] = 1;
					playerLength++;
					if (playerLength >= (LENGTH * WIDTH)) {
						win = true; //TODO: victory screen
						life = false; //you still die when you win though
					}
					else {
						while (map[randa][randb] != 0) {
							randa = rand() % 10 + 1;
							randb = rand() % 10 + 1;
						}
						map[randa][randb] = 1000;
					}
				}
				else if (map[i][j] == 1) {
					test = false;
				}
			}

		// if the head isn't found, die. 
		if (test == true)
			life = false; //TODO: death screen


		//4. update the drawing (clear it and then redraw it with the change above made)
		for (int i = 0; i < LENGTH; i++) //clear screen
			cout << '\n';
		for (int i = 0; i < LENGTH + 2; i++) {
			for (int j = 0; j < WIDTH + 2; j++) {
				if (map[i][j] == 0)
					cout << "·";
				else if (map[i][j] == -2)
					cout << "■";
				else if (map[i][j] == 1000)
					cout << "0";
				else
					cout << "□";

			}
			cout << '\n'; //THESE ASCII DON'T WORK ON THE WINDOWS COMMAND LINE, FIND COOLER ONES!!

			//it may be worth looking into the library pdcurses/ncurses to make the game run better
		}
		cout << playerDirection;
		cout << playerLength;

		ofstream scoreFile;
		scoreFile.open("Scores.txt", ios::app);

		if ((!scoreFile.fail()) && (life == false)) {
			scoreFile << playerLength << endl;
		}
		else if((scoreFile.fail()) && (life == false))
			cout << "Error: could not open score file";
	}
}

int setSpeed() {
	cout << "Input a speed between 1 (fastest) and 40 (slowest).\n";
	int speed_num = 50;

	while ((speed_num > 40) || (speed_num < 1)) {
		cout << "Enter your speed value (default = 20): ";
		char inp_num[9];
		cin >> inp_num;
		speed_num = intCheck(inp_num);
		cout << endl;
		if ((speed_num > 40) || (speed_num < 1)) {
			cout << "Error: Number out of range.\n";
		}
	}
	return speed_num;
}

void trackScores() {
	cout << endl;
	ifstream scoreFile;
	scoreFile.open("Scores.txt");

	cout << "Score history: \n-------------------------------------------\n";

	if (!scoreFile.fail()) {
		while (true) {
			string line;
			getline(scoreFile, line);
			if (scoreFile.fail())
				break;
			cout << line << endl;
		}
	}
	else
		cout << "Error: could not open score file";
	scoreFile.close();
	cout << endl;
}
