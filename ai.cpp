/*
 * ai.cpp
 *
 *  Created on: Sep 26, 2019
 *      Author: Monesh
 */

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <time.h>
#include <limits.h>
#include <bits/stdc++.h>
#include "ai.h"
using namespace std;

#define BOARDHEIGHT 6
#define BOARDWIDTH 7
#define PLAYER 'x'
#define AI 'o'
#define windowlength 3


void delay(int delay)
{
 int now=time(NULL);
 int later=now+delay;
 while(now<=later)now=time(NULL);
}

int max(int a, int b){
	return a>b?a:b;
}

int min(int a, int b){
	return b>a?a:b;
}

// TASK 1
// drop the disc to col
// you can assume col always has space for this new disc
// mark board[row][col] with player's symbol
// return the row of the dropped disc (so you know disc location (row, col)
int drop_disc(char board[][BOARDWIDTH], int height, int width, int col, char disc) {
	for(int i = height-1; i>=0; i--){
		if(board[i][col] == ' '){
			board[i][col] = disc;
			return i;
		}
	}
	return -1;
}

// TASK 2
// check whether the newly dropped disc at (row, col) creates 4-in-a-col
// if yes, return true
bool check_4_in_a_col(const char board[][BOARDWIDTH], int height, int width, int row, int col, char disc) {
	if(row>=height-3) return false;
	if(board[row][col] == disc && board[row+1][col] == disc && board[row+2][col] == disc && board[row+3][col] == disc) return true;
	return false;
}

// TASK 3
// check whether the newly dropped disc at (row, col) creates 4-in-a-row
// if yes, return true
bool check_4_in_a_row(const char board[][BOARDWIDTH], int height, int width, int row, int col, char disc) {
	for(int i = 0; i<width-3; i++){
		if(board[row][col] == disc && board[row][col+1] == disc && board[row][col+2] == disc && board[row][col+3] == disc) return true;
	}
	return false;
}

// TASK 4
// check whether the newly dropped disc at (row, col) creates 4-in-a-diagonal
// both diagonal directions count
// if yes, return true
bool check_4_in_a_diagonal(const char board[][BOARDWIDTH], int height, int width, int row, int col, char disc) {
	uint8_t maxrow =row, maxcol =col, minrow =row, mincol =col;
	while(maxrow!= height-1 && maxcol!= width-1){
		maxrow++;
		maxcol++;
	}
	while(minrow!=0 && mincol!=width-1){
		minrow --;
		mincol ++;
	}
	//left counting
	for(int i =0;i<(maxrow<maxcol?maxrow:maxcol)-3; i++){
			if(board[maxrow-i][maxcol-i] == disc && board[maxrow-i-1][maxcol-i-1] == disc && board[maxrow-i-2][maxcol-i-2] == disc&& board[maxrow-i-3][maxcol-i-3] == disc){
				return true;
			}
	}
	//right counting
	for(int i =0;i<((height-1-minrow)<mincol?(height-1-minrow):mincol)-3; i++){
			if(board[minrow+i][mincol-i] == disc && board[minrow+i+1][mincol-i-1]== disc && board[minrow+i+2][mincol-i-2]== disc&& board[minrow+i+3][mincol-i-3] == disc){
				return true;
			}
	}

	return false;
}

// check whether the game board is full
// simply check whether row 0 is full is good enough
// if yes, return true
bool check_board_full(const char board[][BOARDWIDTH], int height, int width){
	for (int j = 0; j < width; j++)
		if (board[0][j] == ' ')
			return false;
	return true;
}

// check whether a dropped disc triggers the finish of the game
// if yes, e.g. a player wins, or game draws, return true
bool check_game_over(const char board[][BOARDWIDTH], int height, int width, int row, int col, char disc) {
	if (check_4_in_a_col(board, height, width, row, col, disc)){
		cout << "Player " << disc << " wins! " << "col"<<endl;
		return true;
	}
	if (check_4_in_a_diagonal(board, height, width, row, col, disc)){
		cout << "Player " << disc << " wins! " << "diag"<<endl;
		return true;
	}
	if (check_4_in_a_row(board, height, width, row, col, disc) ){
		cout << "Player " << disc << " wins! " << "row"<<endl;
		return true;
	}

	if (check_board_full(board, height, width)){
		cout << "Draw!" << endl;
		return true;
	}

	return false;
}

bool check_game_over_CPU(const char board[][BOARDWIDTH], int height, int width, char disc) {
	for (int i = 0; i<height; i++){
		for (int j =0; j<width; j++){
			if (check_4_in_a_col(board, height, width, i, j, disc) ||
					check_4_in_a_row(board, height, width, i, j, disc) ||
					check_4_in_a_diagonal(board, height, width, i, j, disc)){
				return true;
			}
		}
	}
	return false;
}

// suppose player chooses to drop the disc to col
// validate whether the disc can be dropped
// if yes, return true
bool check_drop_valid(const char board[][BOARDWIDTH], int height, int width, int col, int game_mode) {
	if(game_mode == 0){
		// validate whether col is within board
		if (col < 0 || col >= width) {
			cout << "Board column should be [0, width - 1]" << endl;
			cout << "Please re-enter..." << endl;
			return false;
		}
		// validate if the selected column is full
		if (board[0][col] != ' ') {
			cout << "Column " << col << " is full. Please re-enter..." << endl;
			return false;
		}
		// valid input
		return true;
	}else{
		if (col < 0 || col >= width) {
			return false;
		}
		// validate if the selected column is full
		if (board[0][col] != ' ') {
			return false;
		}
		// valid input
		return true;
	}
}

int evaluatecol(char window[], char piece){
	int score =0, counter =0, empty =0, oppcounter;
	uint8_t windowsize = sizeof(window)/sizeof(window[0]);
	for(int i =0; i<windowsize; i++){
		if(window[i] == piece) counter++;
		else if(window[i] == ' ') empty++;
		else oppcounter++;
	}
	//if (counter ==4 ) score == 10;
	/*else */if(counter == 3 && empty ==1) score+= 5;
	else if(counter ==2 && empty ==2) score +=2;

	if(oppcounter == 3 && empty == 1) score -= 4;
	return score;
}

int score_position(char board[][BOARDWIDTH], char piece){
	int score = 0, center_count=0;
	int center_col = BOARDWIDTH/2;
	for(uint8_t i =0; i<BOARDHEIGHT; i++){
		if(board[i][center_col] == piece) center_count++;
	}
	score += center_count*3;

	//horizontal scoring
	for(uint8_t i = 0; i<BOARDHEIGHT; i++){
		char row_array[BOARDWIDTH];
		for(uint8_t j =0; j<BOARDWIDTH; j++){
			row_array[j] = board[i][j];
		}
		score += evaluatecol(row_array,piece);
	}
	//vertical scoring
	for(uint8_t i = 0; i<BOARDWIDTH; i++){
		char col_array[BOARDHEIGHT];
		for(uint8_t j =0; j<BOARDHEIGHT; j++){
			col_array[j] = board[j][i];
		}
		score += evaluatecol(col_array,piece);
	}
	//diagonal scoring
	for(uint8_t i =0; i<BOARDHEIGHT-3; i++){
		for (uint8_t j =0; j<BOARDWIDTH-3; j++){
			char window[windowlength];
			for(uint8_t k =0; k<windowlength; k++){
				window[k] = board[i+windowlength][j+windowlength];
			}
			score += evaluatecol(window,piece);
		}
	}
	for(uint8_t i =0; i<BOARDHEIGHT-3; i++){
		for (uint8_t j =0; j<BOARDWIDTH-3; j++){
			char window[windowlength];
			for(uint8_t k =0; k<windowlength; k++){
				window[k] = board[i+3-windowlength][j+windowlength];
			}
			score += evaluatecol(window,piece);
		}
	}

	return score;

}

int CPUezinit(char board[][BOARDWIDTH]){
	int col =0;
	do{
		col = rand()% BOARDWIDTH;
	}while(!check_drop_valid(board, BOARDHEIGHT, BOARDWIDTH, col, 2));
	delay(1);
	return col;
}

int CPUhardinit(char board[][BOARDWIDTH]){
	return minimax(board, 7, true).col;
}

int CPUmedinit(char board[][BOARDWIDTH]){
	return minimax(board, 3, true).col;
}

minimaxresult minimax(char board[][BOARDWIDTH], uint8_t depth, bool maximizingPlayer){
	if(depth == 0 || check_game_over_CPU(board, BOARDHEIGHT, BOARDWIDTH, PLAYER) || check_game_over_CPU(board, BOARDHEIGHT, BOARDWIDTH, AI)){
		if(check_game_over_CPU(board, BOARDHEIGHT, BOARDWIDTH, PLAYER)) return (minimaxresult){0,-10000000};
		if(check_game_over_CPU(board, BOARDHEIGHT, BOARDWIDTH, AI)) return (minimaxresult){0,10000000};
		if(check_board_full(board, BOARDHEIGHT, BOARDWIDTH)) return (minimaxresult){0,0};
		return (minimaxresult){0,score_position(board, AI)};
	}
	if(maximizingPlayer){
		int value = INT_MIN;
		uint8_t column = 0;
		for(int i =0; i<BOARDWIDTH; i++){
			if(check_drop_valid(board, BOARDHEIGHT, BOARDWIDTH, i, 1)){
				char bcopy[BOARDHEIGHT][BOARDWIDTH];
				for(uint8_t i = 0; i <BOARDHEIGHT;i++){
					for(uint8_t j =0; j<BOARDWIDTH; j++){
						bcopy[i][j] = board[i][j];
					}
				}
				drop_disc(bcopy, BOARDHEIGHT, BOARDWIDTH, i, AI);
				int new_score = minimax(bcopy, depth-1, false).score;
				if(new_score>value) {
					value = new_score;
					column = i;
				}
			}
		}
		return (minimaxresult){column, value};
	}else{
		int value = INT_MAX;
		uint8_t column = 0;
		for(int i =0; i<BOARDWIDTH; i++){
			if(check_drop_valid(board, BOARDHEIGHT, BOARDWIDTH, i, 1)){
				char bcopy[BOARDHEIGHT][BOARDWIDTH];
				for(uint8_t i = 0; i <BOARDHEIGHT;i++){
					for(uint8_t j =0; j<BOARDWIDTH; j++){
						bcopy[i][j] = board[i][j];
					}
				}
				drop_disc(bcopy, BOARDHEIGHT, BOARDWIDTH, i, PLAYER);
				int new_score = minimax(bcopy, depth-1, true).score;
				if(new_score<value) {
					value = new_score;
					column = i;
				}
			}
		}
		return (minimaxresult){column, value};
	}

}



