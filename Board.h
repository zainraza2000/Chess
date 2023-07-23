#pragma once
#include"Piece.h"
#include"Bishop.h"
#include"Knight.h"
#include"King.h"
#include"Pawn.h"
#include"Queen.h"
#include"Rook.h"
class Board
{
public:
	Piece* pieces[8][8];

	Board()
	{
		for (int i = 0; i <= 7; i++)
		{
			for (int j = 0; j <= 7; j++)
			{
				pieces[i][j] = 0;
			}
		}
	}
	~Board() {
		for (int iRow = 0; iRow < 8; ++iRow) {
			for (int iCol = 0; iCol < 8; ++iCol) {
				delete pieces[iRow][iCol];
				pieces[iRow][iCol] = 0;
			}
		}
	}
	void newBoard()
	{
		for (int i = 0; i <= 7; i++)
		{
			for (int j = 0; j <= 7; j++)
			{
				pieces[i][j] = 0;
			}
		}
		for (int i = 0; i < 8; i++)
		{
			pieces[6][i] = new Pawn('B', 6, i);
		}
		pieces[7][0] = new Rook('B', 7, 0);
		pieces[7][1] = new Knight('B', 7, 1);
		pieces[7][2] = new Bishop('B', 7, 2);
		pieces[7][3] = new King('B', 7, 3);
		pieces[7][4] = new Queen('B', 7, 4);
		pieces[7][5] = new Bishop('B', 7, 5);
		pieces[7][6] = new Knight('B', 7, 6);
		pieces[7][7] = new Rook('B', 7, 7);
		for (int i = 0; i < 8; ++i)
		{
			pieces[1][i] = new Pawn('W', 1, i);
		}
		pieces[0][0] = new Rook('W', 0, 0);
		pieces[0][1] = new Knight('W', 0, 1);
		pieces[0][2] = new Bishop('W', 0, 2);
		pieces[0][3] = new King('W', 0, 3);
		pieces[0][4] = new Queen('W', 0, 4);
		pieces[0][5] = new Bishop('W', 0, 5);
		pieces[0][6] = new Knight('W', 0, 6);
		pieces[0][7] = new Rook('W', 0, 7);
	}
	bool ScanCheck(char player)
	{
		int KingRow;
		int KingCol;
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				if (pieces[i][j] != 0 && pieces[i][j]->getColor() == player && pieces[i][j]->getPiece() == 'K')
				{
					KingRow = i;
					KingCol = j;
				}
			}
		}
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				if (pieces[i][j] != 0 && pieces[i][j]->getColor() != player && pieces[i][j]->MovePossible(i, j, KingRow, KingCol, pieces))
				{
					return true;
				}
			}
		}
		return false;
	}
	bool MoveCheck(char currentPlayer) 
	{
		for (int fromRow = 0; fromRow < 8; ++fromRow) 
		{
			for (int fromCol = 0; fromCol < 8; ++fromCol) 
			{
				if (pieces[fromRow][fromCol] != 0)
				{
					if (pieces[fromRow][fromCol]->getColor() == currentPlayer)
					{
						for (int toRow = 0; toRow < 8; ++toRow)
						{
							for (int toCol = 0; toCol < 8; ++toCol) 
							{
								if (pieces[fromRow][fromCol]->MovePossible(fromRow, fromCol, toRow, toCol, pieces)) 
								{
									Piece* tempPiece = pieces[toRow][toCol];
									pieces[toRow][toCol] = pieces[fromRow][fromCol];
									pieces[fromRow][fromCol] = 0;
									bool pieceMovePossible = !ScanCheck(currentPlayer);
									pieces[fromRow][fromCol] = pieces[toRow][toCol];
									pieces[toRow][toCol] = tempPiece;
									if (pieceMovePossible) 
									{
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
		return false;
	}
};
