#include<SFML/Graphics.hpp>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include <windows.h>
#include<fstream>
#include "Chess.h"
#include"Board.h"
#include"Piece.h"
using namespace std;
void HideConsole()
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}
void delay(int milliseconds) 
{
	clock_t time_end;
	time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
	while (clock() < time_end)
	{
	}
}
void LoadBoard(sf::RenderWindow& window, sf::RectangleShape& board_display, Board& board)
{
	window.clear();
	window.draw(board_display);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board.pieces[i][j] != 0)
				window.draw(board.pieces[i][j]->getSprite());
		}
	}
}
int main()
{
	HideConsole();
	Chess game;
	game.Run();

}