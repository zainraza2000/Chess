#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	Bishop(char color, int x, int y) : Piece(color, x, y) {}
	sf::Sprite getSprite()
	{
		sf::Sprite sprite;
		static sf::Texture texture;
		if (PieceColor == 'W')
			texture.loadFromFile("w_bishop.png");
		else
			texture.loadFromFile("b_bishop.png");
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
	char getPiece()
	{
		return 'B';
	}
	bool MovePossible(int fromRow, int fromCol, int toRow, int toCol, Piece* pieces[8][8])
	{
		int RowDirection;
		int ColDirection;
		Piece* toPiece = pieces[toRow][toCol];
		if ((toPiece == 0) || (PieceColor != toPiece->getColor()))
		{
			if ((toCol - fromCol == toRow - fromRow) || (toCol - fromCol == fromRow - toRow))
			{
				if (toRow - fromRow > 0)
				{
					RowDirection = 1;
				}
				else
				{
					RowDirection = -1;
				}
				if (toCol - fromCol > 0)
				{
					ColDirection = 1;
				}
				else
				{
					ColDirection = -1;
				}
				int CheckRow;
				int CheckCol;
				for (CheckRow = fromRow + RowDirection, CheckCol = fromCol + ColDirection; CheckRow != toRow; CheckRow = CheckRow + RowDirection, CheckCol = CheckCol + ColDirection)
				{
					if (pieces[CheckRow][CheckCol] != 0)
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

