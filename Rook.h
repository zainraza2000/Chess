#pragma once
#include "Piece.h"
class Rook : public Piece
{
public:
	Rook(char color, int x, int y) : Piece(color, x, y) {}
	sf::Sprite getSprite()
	{
		sf::Sprite sprite;
		static sf::Texture texture;
		if (PieceColor == 'W')
			texture.loadFromFile("w_rook.png");
		else
			texture.loadFromFile("b_rook.png");
		sprite.setTexture(texture);
		sprite.scale(sf::Vector2f(0.42, 0.36));
		sprite.setPosition(y * 100, x * 100);
		return sprite;
	}
	void setxy(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
private:
	char getPiece()
	{
		return 'R';
	}
	bool MovePossible(int fromRow, int fromCol, int toRow, int toCol, Piece* pieces[8][8])
	{
		int RowDirection;
		int ColDirection;
		Piece* toPiece = pieces[toRow][toCol];
		if ((toPiece == 0) || (PieceColor != toPiece->getColor()))
		{
			if (fromRow == toRow)
			{
				if (toCol - fromCol > 0)
				{
					ColDirection = 1;
				}
				else
				{
					ColDirection = -1;
				}
				for (int CheckCol = fromCol + ColDirection; CheckCol != toCol; CheckCol = CheckCol + ColDirection)
				{
					if (pieces[fromRow][CheckCol] != 0)
					{
						return false;
					}
				}
				return true;
			}
			else if (toCol == fromCol)
			{
				if (toRow - fromRow > 0)
				{
					RowDirection = 1;
				}
				else
				{
					RowDirection = -1;
				}
				for (int CheckRow = fromRow + RowDirection; CheckRow != toRow; CheckRow = CheckRow + RowDirection)
				{
					if (pieces[CheckRow][fromCol] != 0)
					{
						return false;
					}
				}
				return true;
			}
		}
		return false;
	}
};