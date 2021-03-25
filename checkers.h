/********************************************
Kevin Renicker	4-11-17	    checkers game
File: checkers.h
This is a game of checkers. Move by entering 
the row then column of the piece you want to 
move then the row and piece to move to.
This file uses game.h, space.h, and colors.h.
*********************************************/ 

#ifndef CHECKERS_H
#define CHECKERS_H

#include "game.h"
#include "space.h"
#include "colors.h"

namespace main_savitch_14{
class checkers : public game
{
	public:
	checkers();
	void restart();
	void display_status() const;
	bool is_legal(const std::string& move) const;
	bool is_jump(const std::string& move) const;
	bool is_double_jump(const std::string& move) const;
	bool force_jump() const;
	virtual bool is_game_over( ) const;
	void make_move(const std::string& move);
	virtual void compute_moves(std::queue<std::string>& move) const;
	virtual int evaluate() const;
	int ascii_to_int(int code) const;
	std::string i_to_s(int i) const;
	private:
	space board[8][8];
};
}
#endif        
