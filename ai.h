/*
 * ai.h
 *
 *  Created on: Sep 27, 2019
 *      Author: Monesh
 */

#ifndef AI_H_
#define AI_H_

#define BOARDWIDTH 7
#define BOARDHEIGHT 6

typedef struct{
	int col;
	int score;
}minimaxresult;

int drop_disc(char board[][BOARDWIDTH], int height, int width, int col, char disc);
bool check_4_in_a_col(const char board[][BOARDWIDTH], int height, int width, int row, int col, char disc);
bool check_4_in_a_row(const char board[][BOARDWIDTH], int height, int width, int row, int col, char disc);
bool check_4_in_a_diagonal(const char board[][BOARDWIDTH], int height, int width, int row, int col, char disc);
bool check_board_full(const char board[][BOARDWIDTH], int height, int width);
bool check_game_over(const char board[][BOARDWIDTH], int height, int width, int row, int col, char disc);
bool check_game_over_CPU(const char board[][BOARDWIDTH], int height, int width, char disc);
bool check_drop_valid(const char board[][BOARDWIDTH], int height, int width, int col, int game_mode);
int CPUezinit(char board[][BOARDWIDTH]);
int CPUhardinit(char board[][BOARDWIDTH]);
int CPUmedinit(char board[][BOARDWIDTH]);
minimaxresult minimax(char board[][BOARDWIDTH], uint8_t depth, bool maximizingPlayer);
void delay(int delay);






#endif /* AI_H_ */
