#pragma once
#include<SFML/Graphics.hpp>
class Piece
{
public:
	Piece(char color, int x, int y)
	{
		PieceColor = color;
		this->x = x;
		this->y = y;
	}
	virtual char getPiece() = 0;
	char getColor()
	{
		return PieceColor;
	}
	virtual bool MovePossible(int fromRow, int fromCol, int toRow, int toCol, Piece* pieces[8][8]) = 0;
	virtual void setxy(int x, int y) = 0;
	virtual sf::Sprite getSprite() = 0;
	int x, y;
protected:
	char PieceColor;
};

