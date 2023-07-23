#pragma once
#include "Piece.h"
class Pawn : public Piece
{
public:
	Pawn(char color, int x, int y) : Piece(color, x, y) {}
private:
	sf::Sprite getSprite()
	{
		sf::Sprite sprite;
		static sf::Texture texture;
		if (PieceColor == 'W')
			texture.loadFromFile("w_pawn.png");
		else
			texture.loadFromFile("b_pawn.png");
		sprite.setTexture(texture);
		sprite.scale(sf::Vector2f(0.5, 0.4));
		sprite.setPosition(y * 100, x * 100);
		return sprite;
	}
	void setxy(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	char getPiece() {
		return 'P';
	}
	bool MovePossible(int fromRow, int fromCol, int toRow, int toCol, Piece* pieces[8][8])
	{
		Piece* toPiece = pieces[toRow][toCol];
		if ((toPiece == 0) || (PieceColor != toPiece->getColor()))
		{
			if (toPiece == 0)
			{
				if (fromCol == toCol)
				{
					if (getColor() == 'W')
					{
						if (toRow == fromRow + 1)
						{
							return true;
						}
						else if (fromRow == 1)
						{
							if (toRow == fromRow + 2)
							{
								return true;
							}
						}
					}
					else if (getColor() == 'B')
					{
						if (toRow == fromRow - 1)
						{
							return true;
						}
						else if (fromRow == 6)
						{
							if (toRow == fromRow - 2)
							{
								return true;
							}
						}
					}
				}
			}
			else
			{
				if ((fromCol == toCol + 1) || (fromCol == toCol - 1))
				{
					if (getColor() == 'W')
					{
						if (toRow == fromRow + 1)
						{
							return true;
						}
					}
					else
					{
						if (toRow == fromRow - 1)
						{
							return true;
						}
					}
				}
			}
		}
		return false;
	}
};
