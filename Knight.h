#pragma once
#include "Piece.h"
class Knight : public Piece
{
public:
	Knight(char color, int x, int y) : Piece(color, x, y) {}
	sf::Sprite getSprite()
	{
		sf::Sprite sprite;
		static sf::Texture texture;
		if (PieceColor == 'W')
			texture.loadFromFile("w_horse.png");
		else
			texture.loadFromFile("b_horse.png");
		sprite.setTexture(texture);
		sprite.scale(sf::Vector2f(0.35, 0.4));
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
		return 'N';
	}
	bool MovePossible(int fromRow, int fromCol, int toRow, int toCol, Piece* pieces[8][8])
	{
		Piece* toPiece = pieces[toRow][toCol];
		if ((toPiece == 0) || (PieceColor != toPiece->getColor()))
		{
			if ((fromCol == toCol + 1) || (fromCol == toCol - 1))
			{
				if ((fromRow == toRow + 2) || (fromRow == toRow - 2))
				{
					return true;
				}
			}
			if ((fromCol == toCol + 2) || (fromCol == toCol - 2))
			{
				if ((fromRow == toRow + 1) || (fromRow == toRow - 1))
				{
					return true;
				}
			}
		}
		return false;
	}
};

