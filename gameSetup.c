
#include "gameSetup.h"

//------------------------------------
//	FUNCTION game_instructions 
//------------------------------------
void game_instructions() {
	printf("---------------------------------\n");
	printf(" ESCAPE FROM THE LABYRINTH\n");
	printf("---------------------------------\n");
	printf("Instructions. \n\n");
	printf("Use the keys 'a', 'd', 'w' and 'x' to move the knight ('K) left, right, up and down over the labyrinth, respectively\n");
	printf("'K' can only be moved within the board. Moreover, it can not be moved into any wall position ('W)\n");
	printf("The goal of the game is to use ('K') to push the barrel ('B') towards the escape of the labyrinth, indicated by -->\n");
	printf("On its way, ('K') can collect treasures ('T') so as to make extra points on its journey.\n");
	printf("However, any treasure is susceptible of being buried by pushing ('B') into its position.\n");
	printf("Press any key so as to start the game\n");
	char c = my_get_char();
}

//------------------------------------
//	FUNCTION set_game_initial_status 
//------------------------------------
void set_game_initial_status(char board[6][6], char** knight, char** barrel, int* steps, int* treasures) {
	//First Row
	board[0][0] = ' ';
	board[0][1] = ' ';
	board[0][2] = ' ';
	board[0][3] = ' ';
	board[0][4] = ' ';
	board[0][5] = 'T';

	//Second Row
	board[1][0] = ' ';
	board[1][1] = ' ';
	board[1][2] = 'W';
	board[1][3] = ' ';
	board[1][4] = 'W';
	board[1][5] = 'W';

	//Third Row
	board[2][0] = 'T';
	board[2][1] = 'W';
	board[2][2] = 'W';
	board[2][3] = ' ';
	board[2][4] = ' ';
	board[2][5] = ' ';
	
	//Fourth Row
	board[3][0] = ' ';
	board[3][1] = ' ';
	board[3][2] = ' ';
	board[3][3] = ' ';
	board[3][4] = ' ';
	board[3][5] = 'W';

	//Fith Row
	board[4][0] = 'W';
	board[4][1] = 'B';
	board[4][2] = 'W';
	board[4][3] = 'W';
	board[4][4] = ' ';
	board[4][5] = 'W';

	//Sixth Row
	board[5][0] = 'K';
	board[5][1] = ' ';
	board[5][2] = ' ';
	board[5][3] = 'T';
	board[5][4] = ' ';
	board[5][5] = ' ';

	*knight = &board[5][0];
	*barrel = &board[4][1];
	*steps = 0;
	*treasures = 0;


}

//------------------------------------
//	FUNCTION display_board 
//------------------------------------
void display_board(char board[6][6]) {
	/* output each array element's value */
	for (int i = 0; i < 6; i++) {
		printf("\n------------------------------------\n");
		for (int j = 0; j < 6; j++) {
			printf("|  %c  ", board[i][j]);
		}
		if (i == 2){
			printf("| -->");
		}else{
			printf("|");
		}
		
	}
	printf("\n------------------------------------\n");
}

//------------------------------------
//	FUNCTION display_game_status 
//------------------------------------
void display_game_status(char board[6][6], int steps, int treasures) {
	display_board(board);
	printf("------------------------------------\n");
	printf("\n           GAME STATUS              \n");
	printf("\n------------------------------------\n");
	printf("STEPS DONE = %d\n", steps);
	printf("TREASURES COLLECTED = %d\n", treasures);

}

//------------------------------------
//	FUNCTION play_game 
//------------------------------------
void play_game() {
	//Declare conpnent varibles 
	char board[6][6];
	int treasures;
	int steps;
	char* knight;
	char* barrel;
	char movment = ' ';

	//Show game instructions & set initial status
	game_instructions();
	set_game_initial_status(board, &knight, &barrel, &steps, &treasures);

	//Loop game play while is winning move is not true
	do{
		display_game_status(board, steps, treasures);
	}while(perform_movement(board, &knight,  &barrel, &steps, &treasures) == 0);
	

	printf("*************************************\n");
	printf("            GAME SOLVED              \n");
	printf("*************************************\n");
	printf("STEPS DONE = %d\n", steps);
	printf("TREASURES COLLECTED = %d\n", treasures);
	printf("=====================================\n");

	

}

