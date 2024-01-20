#pragma once

class Position {
	int x, y;
public:
	Position(int a, int b);
	void updatePos(int a, int b);
	int getXpos() const;
	int getYpos() const;
};

Position::Position(int a, int b) 
{
	x = a;
	y = b;
}

void Position::updatePos(int a, int b) 
{
	x = a;
	y = b;
}

int Position::getXpos() const 
{
	return x;
}

int Position::getYpos() const 
{
	return y;
}
