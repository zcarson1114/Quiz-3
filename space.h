/***************************************
 Kevin Renicker checkers project 4-9-17 
 File: space.h
 This class is used in checkers.h. It
 holds information for the board pieces.
 Uses an integer code: 0 = neutral, 
 1 = human, 2 = computer, 3 = unplayable.
***************************************/

#ifndef SPACE_H
#define SPACE_H 
#include <iostream>
class space {
	public:
	space();
	bool is_empty() const;
	bool is_red() const;
	bool is_king() const;
	void king_me();
	void reset_space();
	int operator =(int t) {type = t;}	
	operator int() const {return type;}
	private:
	int type; //stores type of space. 3 = unplayable, 2 = computer, 1 = user, 0 = empty
	bool king_status;

};

#endif
