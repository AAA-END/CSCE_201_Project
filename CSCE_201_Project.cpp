#include <iostream>

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
		if (check_num[i] == NULL)
			break;
		if (!(isdigit(check_num[i]))) {
			check_again = true;
		}
	}

	if (check_again == true) {
		cout << "Error: Please enter a valid number\n";
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
	while ((menu_answer > 3) && (menu_answer < 1)) {
		cout << "\nEnter an input number: ";
		cin >> input_answer;
		menu_answer = intCheck(input_answer);
		if ((menu_answer > 3) && (menu_answer < 1))
			cout << "Error: input number out of range";
	}
	return menu_answer;
}

void playGame() {
	cout << "game working" << endl;
	const int LENGTH = 10;
	const int WIDTH = 10;
	int map[LENGTH][WIDTH] = 0; //most of the game will be handled within an array
	//basic game loop:
	//1. check if a fruit has been eaten, and update length if it has
	//2. check if the user has input a direction, update direction if they did (this may be difficult with only iostream, so other libraries may be needed)
	//3. move the snake forward
	//4. update the drawing (clear it and then redraw it with the change above made)
	//it may be worth looking into the library pdcurses/ncurses to make the game run better
}

int setSpeed() {
	cout << "menu working" << endl;
	return 20;
}
