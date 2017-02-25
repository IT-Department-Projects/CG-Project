#include <bits/stdc++.h>

using namespace std;

class Board {
	public:
		int arr[8][8];
		bool gameEnd;
		Board() {
			this->gameEnd = false;
			for(int i = 0; i < 8; i ++) {
				for(int j = 0; j < 8; j ++) {
					this->arr[i][j] = 0;
				} 
			}
		}
};

class Player {
	public:
		string colour;
		bool hasWon;
		bool hasCheck;	//Checks if player is Check-Mate or not!
		Player(string colour) {
			this->colour = colour;
			this->hasWon = false;
			this->hasCheck = false;
		}

};

class Piece {
	public:
		string name;
		string colour;
};


void init() {
	printf("Welcome to the game of Chess using the terminal.\n");
	printf("This is a 2-player multiplayer game.\n");
}

int main() {
	Board board;

	Player Player1("White");
	Player Player2("Black");

	//Initialize 
	init();

	

	printf("Game ends successfully\n");
	return 0;
}