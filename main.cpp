/*
 * main.cpp
 *
 *  Created on: Sep 26, 2019
 *      Author: Monesh
 */
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdint>
#include "ai.h"
using namespace std;

#define BOARDHEIGHT 6
#define BOARDWIDTH 7

// print game board
void print_board(const char board[][BOARDWIDTH], int height, int width) {

	for (int row = 0; row < height; row++){
		cout << row << '|';
		for (int col = 0; col < width; col++)
			cout << board[row][col] << '|';
		cout << endl;
	}

	for (int i = 0; i <= 2 * width + 1; i++)
		cout << '=';
	cout << endl;
	cout << "  ";

	for (int i = 0; i < width; i++) {
		cout << i << ' ';
	}
	cout << endl << endl;
}

// connect 4 game
int main() {
	char retry = 'y', difficulty = 'e';
	do{
		cout << "***************" << endl;
		cout << "Connect 4 Game" << endl;
		cout << "***************" << endl << endl;

		// game board setup

		// row = 0: top row; row = height-1: bottom row
		// col = 0: leftmost col, col = width-1: rightmost col
		char board[BOARDHEIGHT][BOARDWIDTH];
		// position of the player's disc
		int row, col;
		char disc; // 2 players, one uses 'x', the other uses 'o'
		bool game_over = false;

		// game initialization
		for (int row = 0; row < BOARDHEIGHT; row++)
			for (int col = 0; col < BOARDWIDTH; col++)
				board[row][col] = ' ';

		int game_mode = 0;
		cout << "Please select game mode: 0. 2player mode 1. vsCPU mode" << endl;
		cin >> game_mode;
		if(game_mode== 0) {
			srand(time(NULL));
			int whogofirst = rand() % 2; //pick random player to start
			disc = (whogofirst == 0 ? 'x' : 'o');
		}
		else if(game_mode ==1){
			cout<< "This is the vs CPU mode. Please Choose Difficulty. Type e for easy, m for medium, h for hard."<<endl;
			cin >> difficulty;
			srand(time(NULL));
			int whogofirst = rand() % 2; //pick random player to start
			disc = (whogofirst == 0 ? 'x' : 'o');

		}
		cout << "Game start!" << endl << endl;
		print_board(board, BOARDHEIGHT, BOARDWIDTH);

	// game loop
		do {
			if(game_mode == 0){
				cout << "It's player " << disc << "'s turn. Enter the column to drop your disc:" << endl;
				// select a col to drop the disc
				// input validation enforced
				do{
					cin >> col;
				} while (!check_drop_valid(board, BOARDHEIGHT, BOARDWIDTH, col, 0));
				// grab the row location of the dropped disc
				row = drop_disc(board, BOARDHEIGHT, BOARDWIDTH, col, disc);
				// print updated board
				print_board(board, BOARDHEIGHT, BOARDWIDTH);
				// check whether the player wins
				game_over = check_game_over(board, BOARDHEIGHT, BOARDWIDTH, row, col, disc);
				// swap player
				disc = (disc == 'x' ? 'o' : 'x');
			}else{
				if(disc == 'x'){
					cout<< "It's your turn. Enter the column to drop your disc:" <<endl;
					do{
						cin >> col;
					} while (!check_drop_valid(board, BOARDHEIGHT, BOARDWIDTH, col, 0));
				}
				else {
					cout<<"It's the CPU's turn. Please wait."<<endl;
					switch(difficulty){
						case 'e': col = CPUezinit(board); break;
						case 'm': col = CPUmedinit(board);break;
						case 'h': col = CPUhardinit(board); break;
					}
				}
				row = drop_disc(board, BOARDHEIGHT, BOARDWIDTH, col, disc);
				// print updated board
				print_board(board, BOARDHEIGHT, BOARDWIDTH);
				// check whether the player wins
				game_over = check_game_over(board, BOARDHEIGHT, BOARDWIDTH, row, col, disc);
				// swap player
				disc = (disc == 'x' ? 'o' : 'x');
			}
		} while (!game_over);

		cout << "game over!, would you like to retry? (y/n)" << endl;
		cin>>retry;
	}while (retry!='n');
}


