#include "checkers.h"
#include <iostream>
using namespace std;
using namespace main_savitch_14;

int main()
{
	checkers mygame;
	checkers::who winner;
	winner = mygame.play();
	return 0;
}
