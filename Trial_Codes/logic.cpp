#include <bits/stdc++.h>
using namespace std;
/* Declare constant values for king, queen, bishop, knight, rook, pawn*/

const int king = 8;
const int queen = 7;
const int bishop = 6;
const int knight = 5;
const int rook = 4;
const int pawn = 3;

int board[8][8];

void init(void) {
	for(int i = 0; i < 8; i ++) {
		for(int j = 0; j < 8; j ++) {
			board[i][j] = -1;
		}
	}

	//White pieces
	board[0][0] = board[0][7] = rook;
	board[0][1] = board[0][6] = knight;
	board[0][2] = board[0][5] = bishop;
	board[0][3] = queen;
	board[0][4] = king; 
	for(int i = 0; i < 8; i ++)
		board[1][i] = pawn;

	//Black pieces
	board[7][0] = board[7][7] = - rook;
	board[7][1] = board[7][6] = - knight;
	board[7][2] = board[7][5] = - bishop;
	board[7][4] = - queen;
	board[7][3] = - king;
	for(int i = 0; i < 8; i ++)
		board[6][i] = -pawn;

}

void printBoard(void) {

	printf("Welcome to Simple Chess by Salman Shah.\n");

	for(int i = 0; i < 8; i ++) {
		for(int j = 0; j < 8; j ++) {
			printf("%d\t", board[i][j]);
		}
		printf("\n");
	}


}

int main() {

	init();

	printBoard();


}