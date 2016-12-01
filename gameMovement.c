
#include "gameMovement.h"

//------------------------------------
//	FUNCTION ask_for_movement 
//------------------------------------
char ask_for_movement() {

	char a = ' ';

	printf("\n\nMAKE NEW MOVMENT \n");
	printf("ENTER A MOVE FOR THE KNIGHT\n");
	printf("'a' for left, 'd' for right, 'w' for up, 's' down");
	a = my_get_char();
	return a;
}

//-------------------------------------------
//	FUNCTION get_position_coord_from_pointer 
//-------------------------------------------
void get_position_coord_from_pointer(char board[6][6], char* object, int* x_pos, int* y_pos) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			//If current cords are equal to the object we are serching for set pointer value
			if(board[i][j] == *object){
				*x_pos = i;
				*y_pos = j;
			}
		}
	}
}

//------------------------------------
//	FUNCTION get_new_position_coord 
//------------------------------------
void get_new_position_coord(int x_pos, int y_pos, char movement, int* new_x_pos, int* new_y_pos) {
	if( movement == 'a'){
		*new_x_pos = x_pos;
		*new_y_pos = y_pos -1;
	}else if(movement == 'w'){
		*new_x_pos = x_pos -1;
		*new_y_pos = y_pos;
	}else if(movement == 'd'){
		*new_x_pos = x_pos;
		*new_y_pos = y_pos +1;
	}else if(movement == 's'){
		*new_x_pos = x_pos +1;
		*new_y_pos = y_pos;
	}
}

//------------------------------------
//	FUNCTION is_winning_movement 
//------------------------------------
bool is_winning_movement(char board[6][6], char* barrel, char movement){
	bool res = False;
	int b_x_pos;
	int b_y_pos;
	int b_n_x_pos;
	int b_n_y_pos;

	get_position_coord_from_pointer(board, barrel, &b_x_pos, &b_y_pos);
	get_new_position_coord(b_x_pos, b_y_pos, movement, &b_n_x_pos, &b_n_y_pos);

	if(b_n_x_pos == 2 && b_n_y_pos == 6){
		res = True;
	}
	return res;
}

//------------------------------------
//	FUNCTION is_movement_safe 
//------------------------------------
bool is_movement_safe(char board[6][6], char* knight, char* barrel, char movement) {
	bool res = True;
	int k_x_pos;
	int k_y_pos;
	int k_n_x_pos;
	int k_n_y_pos;

	int b_x_pos;
	int b_y_pos;
	int b_n_x_pos;
	int b_n_y_pos;

	//Get current pos
	get_position_coord_from_pointer(board, knight, &k_x_pos, &k_y_pos);
	get_position_coord_from_pointer(board, barrel, &b_x_pos, &b_y_pos);

	//Get new pos
	get_new_position_coord(k_x_pos, k_y_pos, movement, &k_n_x_pos, &k_n_y_pos);
	get_new_position_coord(b_x_pos, b_y_pos, movement, &b_n_x_pos, &b_n_y_pos);

	//IF movment entered is valid 
	if(movement == 'a' || movement == 'w' || movement == 'd' || movement == 's'){
		//if knight is out of bounds or moving at wall
		if(k_n_x_pos >= 6 || k_n_y_pos >= 6 || k_n_x_pos < 0 || k_n_y_pos < 0 || board[k_n_x_pos][k_n_y_pos] == 'W'){
			res = False;
		}else if(k_n_x_pos == b_x_pos && k_n_y_pos == b_y_pos ){//If knight is pushing barrel
			if( b_n_x_pos >= 6 || b_n_y_pos >= 6 || b_n_x_pos < 0 || b_n_y_pos < 0 || board[b_n_x_pos][b_n_y_pos] == 'W'){
				res = False;
			}
		}
	}else{
		res = False;
	}
	return res;
}

//------------------------------------
//	FUNCTION perform_movement 
//------------------------------------
bool perform_movement(char board[6][6], char** knight, char** barrel, int* steps, int* treasures) {
	bool res = False;
	//Ask user for movment
	char movement = ask_for_movement();

	int k_x_pos;
	int k_y_pos;
	int k_n_x_pos;
	int k_n_y_pos;

	int b_x_pos;
	int b_y_pos;
	int b_n_x_pos;
	int b_n_y_pos;

	//Get current pos
	get_position_coord_from_pointer(board, *knight, &k_x_pos, &k_y_pos);
	get_position_coord_from_pointer(board, *barrel, &b_x_pos, &b_y_pos);

	//Get new pos
	get_new_position_coord(k_x_pos, k_y_pos, movement, &k_n_x_pos, &k_n_y_pos);
	get_new_position_coord(b_x_pos, b_y_pos, movement, &b_n_x_pos, &b_n_y_pos);

	//If the knight is pushinh the barrel
	if(k_n_x_pos == b_x_pos && k_n_y_pos == b_y_pos){
		if(is_winning_movement(board, *barrel, movement)==True){
			*steps += 1;
			res = True;
		}else if(is_movement_safe(board, *knight, *barrel, movement) == True){
			//If the new cords are to a tressure location increment value
			if(board[b_n_x_pos][b_n_y_pos] == 'T'){
				*treasures +=1;
			}


			//Set new cords and update board
			board[k_x_pos][k_y_pos] = ' ';
			board[b_x_pos][b_y_pos] = 'K';
			board[b_n_x_pos][b_n_y_pos] ='B';
			*knight = &board[b_x_pos][b_y_pos];
			*barrel = &board[b_n_x_pos][b_n_y_pos];
			*steps++;
		}
	}
	else if(is_movement_safe(board, *knight, *barrel, movement)==True){//Else if not pushing the barrel
		if(board[k_n_x_pos][k_n_y_pos] == 'T'){
			*treasures += 1;
		}

		board[k_x_pos][k_y_pos] = ' ';
		board[k_n_x_pos][k_n_y_pos] = 'K';
		*knight = &board[k_n_x_pos][k_n_y_pos];

		*steps += 1;
	}

	return res;
}


