#pragma once
class Die
{
public:
	Die();
	~Die();
	int frontalMove(int, int, bool);
	int lateralMove(int, int, bool);
private:
	int topSide;
	int rightSide;
	bool keyPiece;
};

