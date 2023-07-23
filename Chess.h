#pragma once
#include<SFML/Graphics.hpp>
#include"Board.h"
extern void delay(int milliseconds);
void LoadBoard(sf::RenderWindow& window, sf::RectangleShape& board_display, Board& board);
class Chess
{
private:
	char player;
	Board board;
public:
	Chess()
	{
		player = 'W';
	}
	void Menu(sf::RenderWindow& window, int flag)
	{
		static sf::Texture menuTexture;
		sf::RectangleShape menu_display(sf::Vector2f(800.0f, 800.0f));
		menu_display.setPosition(0, 0);
		menuTexture.loadFromFile("menubackground.jpg");
		menu_display.setTexture(&menuTexture);
		sf::Sprite resume_button;
		if (flag == 1)
		{
			static sf::Texture resume_texture;
			resume_texture.loadFromFile("resumebutton.png");
			resume_button.setTexture(resume_texture);
			resume_button.scale(sf::Vector2f(0.12, 0.12));
			resume_button.setPosition(100, 140);
		}
		sf::Sprite play_button;
		static sf::Texture play_texture;
		play_texture.loadFromFile("playbutton.png");
		play_button.setTexture(play_texture);
		play_button.scale(sf::Vector2f(0.1, 0.1));
		play_button.setPosition(350, 150);
		sf::Sprite exit_button;
		static sf::Texture exit_texture;
		exit_texture.loadFromFile("exitbutton.png");
		exit_button.setTexture(exit_texture);
		exit_button.scale(sf::Vector2f(0.23, 0.23));
		exit_button.setPosition(570, 140);
		sf::FloatRect playBoundingBox = play_button.getGlobalBounds();
		sf::FloatRect resumeBoundingBox = resume_button.getGlobalBounds();
		sf::FloatRect exitBoundingBox = exit_button.getGlobalBounds();
		sf::Event evnt;
		while (window.isOpen())
		{
			window.draw(menu_display);
			window.draw(play_button);
			window.draw(resume_button);
			window.draw(exit_button);
			window.display();
			while (window.pollEvent(evnt))
			{
				if (evnt.type == evnt.Closed)
				{
					window.close();
				}
			}
			for (;;)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2i sourcePos = sf::Mouse::getPosition(window);
					if ((sourcePos.x >= 770 && sourcePos.x <= 800) && (sourcePos.y <= 0 && sourcePos.y >= -30))
					{
						window.close();
						exit(1);
					}
					if ((sourcePos.x < 0 || sourcePos.x > 800) || (sourcePos.y < 0 || sourcePos.y > 800))
					{
						delay(300);
						continue;
					}
					if (playBoundingBox.contains((float)sourcePos.x, (float)sourcePos.y))
					{
						window.clear();
						board.newBoard();
						player = 'W';
						return;
					}
					if (resumeBoundingBox.contains((float)sourcePos.x, (float)sourcePos.y))
					{
						return;
					}
					if (exitBoundingBox.contains((float)sourcePos.x, (float)sourcePos.y))
					{
						exit(1);
					}
					delay(300);
				}
			}
		}
	}
	void Run()
	{
		static sf::RenderWindow window(sf::VideoMode(800, 800), "Chess v1.0", sf::Style::Close | sf::Style::Titlebar);
		Menu(window, 0);
		sf::Font font;
		sf::Text text;
		sf::Event evnt;
		static sf::Texture boardTexture;
		sf::RectangleShape board_display(sf::Vector2f(800.0f, 800.0f));
		board_display.setPosition(0, 0);
		boardTexture.loadFromFile("chess_board.jpg");
		board_display.setTexture(&boardTexture);
		font.loadFromFile("font.ttf");
		text.setFont(font);
		while (window.isOpen())
		{
			while (window.pollEvent(evnt))
			{
				if (evnt.type == evnt.Closed)
				{
					window.close();
				}
			}
			LoadBoard(window, board_display, board);
			if (CheckGameStatus())
			{
				if (board.ScanCheck(player))
				{
					if (player == 'W')
					{
						text.setCharacterSize(100);
						text.setStyle(sf::Text::Style::Bold);
						text.setString("Checkmate! Black Wins");
						text.setPosition(120, 300);
						text.setFillColor(sf::Color::Blue);
						window.draw(text);
						delay(5000);
					}
					else
					{
						text.setCharacterSize(100);
						text.setStyle(sf::Text::Style::Bold);
						text.setString("Checkmate! White Wins");
						text.setPosition(120, 300);
						text.setFillColor(sf::Color::Blue);
						window.draw(text);
						delay(5000);
					}
				}
				else
				{
					text.setCharacterSize(100);
					text.setStyle(sf::Text::Style::Bold);
					text.setString("Stalemate!");
					text.setPosition(200, 300);
					text.setFillColor(sf::Color::Blue);
					window.draw(text);
					delay(5000);
				}
				break;
			}
		StartInput:
			LoadBoard(window, board_display, board);
			if (player == 'W')
			{
				text.setCharacterSize(100);
				text.setStyle(sf::Text::Style::Bold);
				text.setString("White's Turn");
				text.setPosition(200, 300);
				text.setFillColor(sf::Color::Blue);
				window.draw(text);
			}
			else
			{
				text.setCharacterSize(100);
				text.setStyle(sf::Text::Style::Bold);
				text.setString("Black's Turn");
				text.setPosition(200, 300);
				text.setFillColor(sf::Color::Blue);
				window.draw(text);
			}
			window.display();
			delay(1000);
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
			window.display();
			for (;;)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					Menu(window, 1);
					goto StartInput;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2i sourcePos = sf::Mouse::getPosition(window);
					if ((sourcePos.x >= 770 && sourcePos.x <= 800) && (sourcePos.y <= 0 && sourcePos.y >= -30))
					{
						exit(1);
					}
					if ((sourcePos.x < 0 || sourcePos.x > 800) || (sourcePos.y < 0 || sourcePos.y > 800))
					{
						delay(300);
						continue;
					}
					if ((board.pieces[sourcePos.y / 100][sourcePos.x / 100] == 0))
					{
						text.setCharacterSize(100);
						text.setStyle(sf::Text::Style::Bold);
						text.setString("Wrong Click!");
						text.setPosition(200, 300);
						text.setFillColor(sf::Color::Red);
						LoadBoard(window, board_display, board);
						window.draw(text);
						window.display();
						delay(1000);
						goto StartInput;
					}
					else if (board.pieces[sourcePos.y / 100][sourcePos.x / 100]->getColor() != player)
					{
						text.setCharacterSize(100);
						text.setStyle(sf::Text::Style::Bold);
						text.setString("Wrong Piece Clicked!");
						text.setPosition(125, 300);
						text.setFillColor(sf::Color::Red);
						LoadBoard(window, board_display, board);
						window.draw(text);
						window.display();
						delay(1000);
						goto StartInput;
					}
					delay(300);
					for (;;)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						{
							Menu(window, 1);
							goto StartInput;
						}
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							sf::Vector2i destPos = sf::Mouse::getPosition(window);
							if ((destPos.x >= 770 && destPos.x <= 800) && (destPos.y <= 0 && destPos.y >= -30))
							{
								window.close();
								exit(1);
							}
							if ((destPos.x < 0 || destPos.x > 800) || (destPos.y < 0 || destPos.y > 800))
							{
								delay(300);
								continue;
							}
							if (InitiateMove(board.pieces, sourcePos.y / 100, sourcePos.x / 100, destPos.y / 100, destPos.x / 100))
								break;
							else
							{
								text.setCharacterSize(100);
								text.setStyle(sf::Text::Style::Bold);
								text.setString("Invalid Move!");
								text.setPosition(200, 300);
								text.setFillColor(sf::Color::Red);
								LoadBoard(window, board_display, board);
								window.draw(text);
								window.display();
								delay(1000);
								goto StartInput;
							}
						}
					}
					break;
				}
			}
			if (player == 'W') player = 'B';
			else player = 'W';
		}
		window.clear();
	}
	int CheckGameStatus()
	{
		if (board.MoveCheck(player) == 0) return 1;
		else return 0;
	}
	int  InitiateMove(Piece* TempPieces[8][8], int fromRow, int fromCol, int toRow, int toCol)
	{
		if (fromRow >= 0 && fromRow <= 7 && toRow >= 0 && toRow <= 7 && fromCol >= 0 && fromCol <= 7 && toCol >= 0 && toCol <= 7)
		{
			Piece* inputPiece = TempPieces[fromRow][fromCol];
			if (inputPiece != 0 && inputPiece->getColor() == player && inputPiece->MovePossible(fromRow, fromCol, toRow, toCol, TempPieces))
			{
				Piece* temp = TempPieces[toRow][toCol];
				TempPieces[toRow][toCol] = TempPieces[fromRow][fromCol];
				TempPieces[fromRow][fromCol] = 0;
				if (!board.ScanCheck(player))
				{
					delete temp;
					inputPiece->setxy(toRow, toCol);
					return 1;
				}
				else
				{
					TempPieces[fromRow][fromCol] = TempPieces[toRow][toCol];
					TempPieces[toRow][toCol] = temp;
					if (player == 'W') player = 'B';
					else player = 'W';
				}
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
};
