//Implementation of space.h
#include "space.h"

space::space()
{
	king_status = false;
	type = 3;
}
bool space::is_empty() const
{
	return (type == 0);
}

bool space::is_red() const
{
	return (type == 1);
}
bool space::is_king() const
{
	return king_status;
}

void space::king_me()
{
	king_status = true;
}

void space::reset_space()
{
	type = 0;
	king_status = false;
}
