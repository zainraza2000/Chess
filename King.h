#pragma once
#include "Piece.h"
class King : public Piece
{
public:
	King(char color, int x, int y) : Piece(color, x, y) {}
	sf::Sprite getSprite()
	{
		sf::Sprite sprite;
		static sf::Texture texture;
		if (PieceColor == 'W')
			texture.loadFromFile("w_king.png");
		else
			texture.loadFromFile("b_king.png");
		sprite.setTexture(texture);
		sprite.scale(sf::Vector2f(0.35, 0.35));
		sprite.setPosition(y * 100, x * 100);
		return sprite;
	}
	void setxy(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
private:
	char getPiece() {
		return 'K';
	}
	bool MovePossible(int fromRow, int fromCol, int toRow, int toCol, Piece* pieces[8][8])
	{
		Piece* toPiece = pieces[toRow][toCol];
		if ((toPiece == 0) || (PieceColor != toPiece->getColor()))
		{
			int RowDifference = toRow - fromRow;
			int ColDifference = toCol - fromCol;
			if (((RowDifference >= -1) && (RowDifference <= 1)) && ((ColDifference >= -1) && (ColDifference <= 1)))
			{
				return true;
			}
		}
		return false;
	}
};

