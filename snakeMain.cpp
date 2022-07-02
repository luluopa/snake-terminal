//Snake from scratch in console made it using gotoxy function [only works on windows though] 
//Made it by Lucas Lima

#include <iostream>
#include <stdlib.h>
#include <curses.h>
#include <windows.h>
#include <stdio.h>
#include "snakeHeader.h"
#include <vector>

class Player {
private:
	int points;
	char keyboardHit;
	Snake* snake;
public:
	Player(int points=0, int ) {
		this->points = points;
		this->snake = new Snake();
	}

	Snake* getSnake() {
		return this->snake;
	}

	Body* getHead() {
		this->getSnake()->getHead();
	}

	void incrementSnake() {
		this->snake->getSnake()->push_back(Body(0,0));
	}

	int getPoints() {
		return this->points;
	}

	char getKeyboardHit() {
		return this->keyboardHit;
	}

	void setKeyboardHit(char caracter) {
		this->keyboardHit = caracter;
	}

	void increasePoints(int increment=1) {
		this->points += increment;
	}
};

void gotoxy(int x, int y,char print_user) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
	std::cout << print_user;
}

void isSnakeHeadTouchingApple(Player* player, Apple* apple) {
	int head_position_x = player->getHead()->getPosition()->at(0);
	int head_position_y = player->getHead()->getPosition()->at(1);

	return head_position_x == apple->pos_x && head_position_y == apple->pos_y;
}

void ifPlayerEatTheApple(Player* player, Apple* apple) {
	if(isSnakeHeadTouchingApple(player, apple)) {
		apple->setPosition(rand() % LENGTH, rand() % HEIGHT);
		player->incrementSnake();
		player->increasePoints();
	}
}

void Print_snake_apple(Player* player, Apple* apple) {
	gotoxy(cobra[0].posicao_x,cobra[0].posicao_y,'O');
	gotoxy(maca.posicao_xp,maca.posicao_yp,'M');
}

void plotChar(std::vector<int> position, char caracter) {
	if(position.size() == 2)
		gotoxy(position.at(0), position.at(1), caracter);
}

void plotSnake(Player* player) {
	for(int body=player->getSnake()->getSize(); body > 0 ;body--) {
		if(body == player->getSnake()->getSize())
	    	plotChar(vector<int>{})

		cobra[body].posicao_x = cobra[body-1].posicao_x;
		cobra[body].posicao_y = cobra[body-1].posicao_y;
	}
}

void voce_perdeu() {
	system("cls");
	gotoxy(17,10,' ');
	std::cout << "voce perdeu, sua pontuacao foi: "  << pontuacao << std::endl;
	gotoxy(20,11,' ');
	std::cout << " deseja continuar[s/n]";
	gotoxy(30,13,' ');
	std::cout << "[Sim]";
	gotoxy(30,14,' ');
	std::cout << "[Nao]";
}

bool check_if_want_continue() {
	system("cls");
	voce_perdeu();
	int pos_y = 13;
	bool check_while = 1;
	
	while(check_while) {
		char keyboard_char;
		gotoxy(37,pos_y,'<');	
		if(kbhit()) {	
		    keyboard_char = getch();
			switch(keyboard_char) {
				case 's':
					if(pos_y == 13) {
						pos_y++;
						gotoxy(37,pos_y-1,' ');
					}
					break;
				case 'w':
					if(pos_y == 14) {
						pos_y--;
						gotoxy(37,pos_y+1,' ');						
					}
					break;
				case 13:
					if(pos_y == 13) {
						pontuacao = 0;
						return true;			
					}
					else if(pos_y == 14) {
						return false;
					}
					break;
			}
		}
	}
}

bool isTouchingHisOwnBody(Player* player) {
	for(int i=player->getSnake()->getSize();i>1;i--) {
		if(cobra[0].posicao_x == cobra[i].posicao_x
		&& cobra[0].posicao_y == cobra[i].posicao_y) {
			return true;
		}
	}
	return false;
}

void Update_position() {
	int aux,aux1;
        if(check_clean == player->getSnake()->getSize()) {
        	gotoxy(cobra[0].posicao_x,cobra[0].posicao_y,' ');
    	        check_clean = NULL;			
    	}

	if(player.getKeyboardHit() == Up)
		cobra->Sum_posicao(0,-1);
	else if(player.getKeyboardHit() == Down)
		cobra->Sum_posicao(0,1);
	else if(player.getKeyboardHit() == Left)
		cobra->Sum_posicao(-1,0);
	else if(player.getKeyboardHit() == Right)
		cobra->Sum_posicao(1,0);
}

bool ifPlayerHitTheKeyboard() {
	return kbhit();
}

void changePlayerKeyboardChar(Player* player){
	if ifPlayerHitTheKeyboard() {
		player->setKeyboardHit(getch());
	}
}

void delayTime(int timeDelayer){
	for(int i=0;i<=timeDelayer;i++);
}

void changeKeyboardPlayer(Player* player) {
	switch (player->getKeyboardHit()) {
		case 'w':
			if(player.getKeyboardHit() != Down)
				player.setKeyboardHit(Up);
			break;
		case 's':
			if(player.getKeyboardHit() != Up)
				player.getKeyboardHit() = Down;
			break;
		case 'a':
			if(player.getKeyboardHit() != Right)
				player.getKeyboardHit() = Left;
			break;
		case 'd':
			if(player.getKeyboardHit() != Left)
				player.getKeyboardHit() = Right;
			break;
	}
}

void cleanScreen() {
	system("cls");
}

void reset(Player* player, Apple* apple) {
	check_clean = 4;
	cleanScreen();	
	apple->resetApple();
	player->getSnake()->snakeReset();
	constructMap();
}

bool isTouchingVerticalLine(Player* player) {
	bool propositionOne = player->getHead()->getPosition()->at(0) <= 1;
	bool propositionTwo = player->getHead()->getPosition()->at(0) >= HEIGHT;
	return (propositionOne || propositionTwo);
}

bool isTouchingHorizontalLine(Player* player) {
	bool propositionOne = player->getHead()->getPosition()->at(1) <= 1;
	bool propositionTwo = player->getHead()->getPosition()->at(1) >= LENGTH;
	return (propositionOne || propositionTwo);
}

bool checkIfThePlayerLost(Player* player) { 
	return isTouchingVerticalLine(player) || isTouchingHorizontalLine(player) || isTouchingHisOwnBody();
}

void Game() {

	constructMap();
	Player player = new Player();
	bool isGameRunning = true;
	Apple apple(20,20);

	while(isGameRunning) {

		Print_snake_apple();
		Update_position();
		changePlayerKeyboardChar();
		delayTime(3000000000);
		changeKeyboardPlayer(player);

		if(checkIfThePlayerLost(player)) {		
			if(check_if_want_continue()) {	
				reset(player, apple);
			}
			else {
				check_game = 0;
			}		
		}
	}
}

int main() {
	Game();
	
	return 0;
}
