/***************************************
 File: Checkers.cc Implementation of
 checkers.h, comments found there.
 ***************************************/
#include "checkers.h" 
#include <iostream> 
#include <iomanip> 
#include <cstdlib>
#include <queue>
using namespace std; 
namespace main_savitch_14{

checkers::checkers()
: game()
{
	restart();
}
void checkers::restart(){
	int n=0,h = 1, c = 2, x = 3; //neutral,user,computer,unplayable
	//initialize the board
	for(int i = 7; i>=0; --i){ // 8rows
		for(int j = 0; j<8; j++){ //8 columns
		if(j%2 != 0 && i == 0) board[i][j] = h;
		else if(j%2 == 0 && i == 1) board[i][j] = h;
		else if(j%2 !=0 && i == 2) board[i][j] = h;
		else if(j%2 == 0 && i == 5) board[i][j] = c;
		else if(j%2 != 0 && i == 6) board[i][j] = c;
		else if(j%2 == 0 && i == 7) board[i][j] = c;
		else if(j%2 == 0 && i == 3) board[i][j] = n;
		else if(j%2 != 0 && i == 4) board[i][j] = n;
		else board[i][j] = x;
		}
	}
	game::display_message("Directions: Enter row and column of piece,\nthen row and column of where to move, no spaces.\n");
}
void checkers::display_status() const {
	cout << setw(10) <<"  1  2  3  4  5  6  7  8" << endl;
	for(int row = 7; row >= 0; --row){
	cout << row+1;
		for(int column = 0; column <= 7; ++column){
			switch(board[row][column])
			{
			case 3: for(int i = 0; i<3; i++){
				cout << WHITE << "\u2588";
				}
				break;
			case 2: cout << BLACK << "\u2588";
				cout << B_BLACK << YELLOW << '@';
				cout << BLACK << "\u2588";
				break;
			case 1: cout << BLACK << "\u2588";
				cout << B_BLACK << RED << '@';
				cout << BLACK << "\u2588";
				break;
			case 0: for(int i=0; i<3; i++){
				cout << BLACK << "\u2588";
				}
				break;
			}
		}
		cout << RESET << endl;
	}
}

bool checkers::is_legal(const string& move) const {
	int first,second,third,fourth;
	first = int(move[0]);
	second = int(move[1]);
	third = int(move[2]);
	fourth = int(move[3]);
	int row = ascii_to_int(first)-1;
	int col = ascii_to_int(second)-1;
	int row_move = ascii_to_int(third)-1;
	int col_move = ascii_to_int(fourth)-1;
	int n=0,h = 1, c = 2, x = 3;
	if(last_mover() == HUMAN){ //computer's turn
	if(board[row][col] == c){
		if(row_move < 0 || row_move > 7 || col_move < 0 || col_move > 7){
			return false;
		}
		if(board[row_move][col_move] == x){
			return false;
		}
		if(row_move == row-2 && is_jump(move)){
			return true;
		}
		if(board[row][col].is_king() && is_jump(move)){
			return true;
		}
		if(force_jump()){
			string msg = "Jump available. Move must be a jump.\n";
			game::display_message(msg);
			return false;
		}
		if(row_move == row-1 && (col_move == col-1 || col_move == col+1)){
			if(board[row_move][col_move] == n){
				return true;
			}
		}
	}
	return false;
	}
	else{
	if(board[row][col] == h){
		if(row_move < 0 || row_move > 7 || col_move < 0 || col_move > 7){
			return false;
		}
		if(board[row_move][col_move] == x){
			return false;
		}
		if(row_move == row+2 && is_jump(move)){
			return true;
		}
		if(board[row][col].is_king() && is_jump(move)){
			return true;
		}
		if(force_jump()){
			string msg = "Jump available. Move must be a jump.\n";
			game::display_message(msg);
			return false;
		}
		if(row_move == row+1 && (col_move == col+1 || col_move == col-1)){
			if(board[row_move][col_move] == 0){
			return true;
			}
		}
		else return false;
	}
	return false;
	}
}

bool checkers::is_jump(const string& move) const {
	int first,second,third,fourth;
	first = int(move[0]);
	second = int(move[1]);
	third = int(move[2]);
	fourth = int(move[3]);
	int row = ascii_to_int(first)-1;
	int col = ascii_to_int(second)-1;
	int row_move = ascii_to_int(third)-1;
	int col_move = ascii_to_int(fourth)-1;
	//neutral,user,computer,unplayable -- int. codes
	int n=0,h = 1, c = 2, x = 3;
	if(last_mover() == HUMAN){ //computers turn
		if(row < 0 || row > 7 || col < 0 || col > 7){
		return false;
		}
		if(row_move < 0 || row_move > 7 || col_move < 0 || col_move > 7){
		return false;
		}
		if(board[row_move][col_move] == x){
		return false;
		}
		if(board[row_move][col_move] == n){
		//non-king piece
		if(!board[row][col].is_king()){
			if(col_move > col){
				if(board[row-1][col+1] == h){
					if(row_move == row-2 &&  col_move == col+2){
					return true;
					}
				}
			}
			else{
				if(board[row-1][col-1] == h){
					if(row_move == row-2 && col_move == col-2){
					return true;
					}
				}
			}
		}
		//king piece
		else{
			if(col_move > col){
				if(board[row+1][col+1] == h){
					if(row_move == row+2 && col_move == col+2){
					return true;
					}
				}
				else if(board[row-1][col+1] == h){
					if(row_move == row-2 && col_move == col+2){
					return true;
					}
				}
			}
			else{
				if(board[row+1][col-1] == h){
					if(row_move == row+2 && col_move == col-2){
					return true;
					}
				}
				else if(board[row-1][col-1] == h){
					if(row_move == row-2 && col_move == col-2){
					return true;
					}
				}
			}
		}
		}
	}
	//human turn
	else{	
		if(row_move < 0 || row_move > 7 || col_move < 0 || col_move > 7){
		return false;
		}
		if(board[row_move][col_move] == x){
		return false;
		}
		if(board[row_move][col_move] == n){
		//non-king piece
		if(!board[row][col].is_king()){
			if(col_move > col){
				if(board[row_move-1][col_move-1] == c){
					if(row_move == row+2 && (col_move == col+2 || col_move == col-2)){
					return true;}
				}
			}
		
			else{
				if(board[row_move-1][col_move+1] == c){
				 	if(row_move == row+2 && (col_move == col+2 || col_move == col-2)){
					return true;}
				}
			}
		}
		//king piece
		else{
			if(col_move > col){
				if(board[row+1][col+1] == c){
					if(row_move == row+2 && col_move == col+2){
					return true;
					}
				}
				else if(board[row-1][col+1] == c){
					if(row_move == row-2 && col_move == col+2){
					return true;
					}
				}
			}
			else{
				if(board[row+1][col-1] == c){
					if(row_move == row+2 && col_move == col-2){
					return true;
					}
				}
				else if(board[row-1][col-1] == c){
					if(row_move == row-2 && col_move == col-2){
					return true;
					}
				}
			}
		}
		}
	}
	return false;
}

bool checkers::force_jump() const
{
	int i,j;
	//neutral,user,computer,unplayable -- int. codes
	int n=0,h = 1, c = 2, x = 3;
	for(i=7;i>=0;--i){
		for(j=7;j>=0;--j){
			if(last_mover() == HUMAN){
				if(board[i][j] == c){
					if(!board[i][j].is_king()){
						if(board[i-1][j+1] == h){
							if(board[i-2][j+2] == n && i>=0 && i<8 && j>=0 && j<8){
								 return true;
							}
						}
						else if(board[i-1][j-1] == h){
							if(board[i-2][j-2] == n && i>=0 && i<8 && j>=0 && j<8){
								return true;
							}
						}
					}
					else{
						if(board[i+1][j+1] == h){
							if(board[i+2][j+2] == n && i>0 && i<8 && j>=0 && j<8){
								 return true;
							}
						}
						else if(board[i+1][j-1] == h){
							if(board[i+2][j-2] == n && i>=0 && i<8 && j>=0 && j<8){
								return true;
							}
						}
						else if(board[i-1][j+1] == h){
							if(board[i-2][j+2] == n && i>=0 && i<8 && j>=0 && j<8){
								 return true;
							}
						}
						else if(board[i-1][j-1] == h){
							if(board[i-2][j-2] == n && i>=0 && i<8 && j>=0 && j<8){
								return true;
							}
						}
					}
				}
			}
			else{
				if(board[i][j] == h){
					if(!board[i][j].is_king()){
						if(board[i+1][j+1] == c){
							if(board[i+2][j+2] == n && i>=0 && i<8 && j>=0 && j<8){
								 return true;
							}
						}
						else if(board[i+1][j-1] == c){
							if(board[i+2][j-2] == n && i>=0 && i<8 && j>=0 && j<8){
								return true;
							}
						}
					}
					else{
						if(board[i+1][j+1] == c){
							if(board[i+2][j+2] == n && i>=0 && i<8 && j>=0 && j<8){
								 return true;
							}
						}
						else if(board[i+1][j-1] == c){
							if(board[i+2][j-2] == n && i>=0 && i<8 && j>=0 && j<8){
								return true;
							}
						}
						else if(board[i-1][j+1] == c){
							if(board[i-2][j+2] == n && i>=0 && i<8 && j>=0 && j<8){
								 return true;
							}
						}
						else if(board[i-1][j-1] == c){
							if(board[i-2][j-2] == n && i>=0 && i<8 && j>=0 && j<8){
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool checkers::is_double_jump(const string& move) const
{
	//this function checks if spot moving to has a jump available after the move
	int first,second,third,fourth;
	first = int(move[0]);
	second = int(move[1]);
	third = int(move[2]);
	fourth = int(move[3]);
	int row = ascii_to_int(first)-1;
	int col = ascii_to_int(second)-1;
	int row_move = ascii_to_int(third)-1;
	int col_move = ascii_to_int(fourth)-1;
	//neutral,user,computer,unplayable -- int. codes
	int n=0,h = 1, c = 2, x = 3;
	int i,j;
	//non-king piece
	if(last_mover() == HUMAN){
	//normal piece -- computer
	if((row_move == row+2 || row_move == row-2) && (col_move == col+2 || col_move == col-2)){
	if(!board[row][col].is_king()){
		i = row_move-2;
		j = col_move;
		for(j=j+2;j>=col_move-2;j=j-2){
			if(j!=col_move){
				if(j >= 0 && j < 8 && i >= 0 && i < 8){
					if(board[i][j] == n){
						if(col_move > col){
							if(board[i+1][j-1] == h){
								return true;
							}
						}
						else{
							if(board[i+1][j+1] == h){
								return true;
							}
						}
					}
				}
			}
		}
	}
	//king piece -- computer
	else{
		i=row_move;
		j=col_move;
		for(i=i+2;i>=row_move-2;i=i-2){
		if(i!= row_move){
			for(j=j+2;j>=col_move-2;j=j-2){
				if(j!= col_move){
					if(i >= 0 && i < 8 && j >= 0 && j < 8){
						if(board[i][j] == n){
							if(col_move > col){
								if(row_move > row){
									if(board[i-1][j-1] == h){
										return true;
									}
								}
								else{
									if(board[i+1][j-1] == h){
										return true;
									}
								}
							}
							else{
								if(row_move > row){
									if(board[i-1][j+1] == h){
										return true;
									}
								}
								else{
									if(board[i+1][j+1] == h){
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
		} 
	}
	}
	}
	else{
	//normal piece -- human
	if((row_move == row+2 || row_move == row-2) && (col_move == col+2 || col_move == col-2)){
	if(!board[row][col].is_king()){
		i = row_move+2;
		j = col_move;
		for(j=j+2;j>=col_move-2;j=j-2){
			if(j!=col_move && j>=col_move-2){
				if(j >= 0 && j < 8 && i >= 0 && i < 8){
					if(board[i][j] == n){
						if(col_move > col){
							if(board[i-1][j-1] == c){
								if(row_move == row+2 && col_move == col+2){
									return true;
								}
							}
						}
						else{
							if(board[i-1][j+1] == c){
								if(row_move == row+2 && col_move == col-2){
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	//king piece -- human
	else{
		int i=row_move;
		int j=col_move;
		for(i=i+2;i>=row_move-2;i=i-2){
		if(i!= row_move){
			for(j=j+2;j>=col_move-2;j=j-2){
				if(j!= col_move){
					if(i >= 0 && i < 8 && j >= 0 && j < 8){
						if(board[i][j] == n){
							if(col_move > col){
								if(row_move > row){
									if(board[i-1][j-1] == c){
										return true;
									}
								}
								else{
									if(board[i+1][j-1] == c){
										return true;
									}
								}
							}
							else{
								if(row_move > row){
									if(board[i-1][j+1] == c){
										return true;
									}
								}
								else{
									if(board[i+1][j+1] == c){
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
		} 
	}
	}
	}
	return false;
}

int checkers::ascii_to_int(int code) const
{
	switch(code){
	case 48: return 0;
		break;
	case 49: return 1;
		break;
	case 50: return 2;
		break;
	case 51: return 3;
		break;
	case 52: return 4;
		break;
	case 53: return 5;
		break;
	case 54: return 6;
		break;
	case 55: return 7;
		break;
	case 56: return 8;
		break;
	case 57: return 9;
		break;
	}
}

string checkers::i_to_s(int i) const
{
	switch(i){
	case 1: return "1";
		break;
	case 2: return "2";
		break;
	case 3: return "3";
		break;
	case 4: return "4";
		break;
	case 5: return "5";
		break;
	case 6: return "6";
		break;
	case 7: return "7";
		break;
	case 8: return "8";
		break;
	case 9: return "9";
		break;
	}
}

void checkers::make_move(const string& move) {
	int first = move[0],second = move[1], third = move[2], fourth = move[3];
	int row = ascii_to_int(first)-1;
	int col = ascii_to_int(second)-1;
	int row_move = ascii_to_int(third)-1;
	int col_move = ascii_to_int(fourth)-1;
	//neutral,user,computer,unplayable -- int. codes
	int n=0,h = 1, c = 2, x = 3; 
	if(is_legal(move)){
	//computer player move
	if(last_mover() == HUMAN){
		if(row_move == row-2 || row_move == row+2){
			if(!board[row][col].is_king()){
				if(col_move > col){
					board[row_move+1][col_move-1].reset_space();
				}
				else{
					board[row_move+1][col_move+1].reset_space();
				}
				board[row_move][col_move] = c;

			}
			else{
				if(col_move > col){
					if(row_move > row){
						board[row_move-1][col_move-1].reset_space();
					}
					else{
						board[row_move+1][col_move-1].reset_space();
					}
				}
				else{
					if(row_move > row){
						board[row_move-1][col_move+1].reset_space();
					}
					else{
						board[row_move+1][col_move+1].reset_space();
					}
				}
			}
		}
		board[row_move][col_move] = c;
		if(row_move == 0){
			board[row_move][col_move].king_me();
		}
	}
	//human player move
	else{
		//if a jump has ocurred then clear space jumped
		if(row_move == row+2 || row_move == row-2){
		//normal piece jump
			if(!board[row][col].is_king()){ 
				if(col_move > col){
					board[row_move-1][col_move-1].reset_space();
				}
				else{
					board[row_move-1][col_move+1].reset_space();
				}
			}
		//king-piece jump
			else{
				if(col_move > col){
					if(row_move > row){
						board[row_move-1][col_move-1].reset_space();
					}
					else{
						board[row_move+1][col_move-1].reset_space();
					}
				}
				else{
					if(row_move > row){
						board[row_move-1][col_move+1].reset_space();
					}
					else{
						board[row_move+1][col_move+1].reset_space();
					}
				}
			}
		}
		board[row_move][col_move] = h;
		if(row_move == 7){
			board[row_move][col_move].king_me();
		}
	}
	board[row][col].reset_space();
	if(!is_double_jump(move)){
		game::make_move(move);
	}
	else{
		game::display_message("Another jump available. Must make jump before next turn.\n");
	}
	}
	//else force jump
/*	else{
		if(last_mover() == HUMAN){
			game::make_computer_move();
		}
		else{
			string msg = "Jump available. User must jump to continue";
			game::display_message(msg);
			game::make_human_move();
		}
	}*/
}

bool checkers::is_game_over( ) const
{
	int i,j;
	int c_count,h_count;
	//neutral,user,computer,unplayable -- int. codes
	int n=0,h = 1, c = 2, x = 3; 
	for(i=7;i>=0;--i){
		for(j=0;j<8;j++){
			if(board[i][j] == c)
				c_count++;
			if(board[i][j] == h)
				h_count++;
		}
	}
	if(c_count == 0)
		return true;
	if(h_count == 0)
		return true;
	else
		return false;
}

void checkers::compute_moves(queue<string>& moves) const
{
	//int codes for computer and neutral 
	int c=2,n=0; 
	//tracks number of pieces and neutral spaces to add to array
	int i,j,num_piece=0,num_move=0; 
	//arrays for max number of computer pieces and neutral spaces on board
	string piece[12],move[32],temp_move; 
	//fill arrays with coordinates for all computer pieces and neutral spaces in string form	
	for(i=8;i>=1;--i){
		for(j=1;j<=0;j++){
			if(board[i][j] == c){
				piece[num_piece] = i_to_s(i)+i_to_s(j);
				num_piece++;
			}
			else if(board[i][j] == n){
				move[num_move] = i_to_s(i)+i_to_s(j);
				num_move++;
			}
		}
	}
	//go through all pieces and neutral places forming a string of both
	//is_legal filters out impossible moves
	//legal moves pushed onto stack
	for(i=num_piece;i>=0;--i){
		for(j=num_move;j>=0;--j){
			temp_move=piece[num_piece]+move[num_move];
			if(is_legal(temp_move)){
				moves.push(temp_move);
			}
		}
	}
}

int checkers::evaluate() const
{
	
}

}
