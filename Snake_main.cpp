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

void Print_snake_apple()
{
	//printando a cabeça da snake
	gotoxy(cobra[0].posicao_x,cobra[0].posicao_y,'O');
        //checando pra ver se a snake comeu a maça
	if(cobra[0].posicao_x == maca.posicao_xp && cobra[0].posicao_y == maca.posicao_yp)
	{
		while((cobra[0].posicao_x == maca.posicao_xp && cobra[0].posicao_y == maca.posicao_yp)
		|| (maca.posicao_yp <= 1 || maca.posicao_xp <= 1)
                || (maca.posicao_yp >= lenght-2 || maca.posicao_xp >= height-2))   
		{
			maca.posicao_xp = rand()%70;
			maca.posicao_yp = rand()%20;
		}
		global_tamanho_cobra++;
		pontuacao++;
	}
	//plotando na tela a maça
	gotoxy(maca.posicao_xp,maca.posicao_yp,'M');
}

//desenho na tela caso voce perca
void voce_perdeu()
{
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
	while(check_while)
	{
		char keyboard_char;
		gotoxy(37,pos_y,'<');	
		if(kbhit())
		{	
			//se o usuario mexer no teclado a seta eu mudo a posição dela
			//dependendo do y em que o usuario der enter no caso só dois
			//y, eu dou reset no jogo ou acabo o jogo
		    keyboard_char = getch();
			switch(keyboard_char)
			{
			case 's':
				if(pos_y == 13)
				{
					pos_y++;
					gotoxy(37,pos_y-1,' ');
				}
				break;
			case 'w':
				if(pos_y == 14)
				{
					pos_y--;
					gotoxy(37,pos_y+1,' ');						
				}
				break;
			case 13:
				if(pos_y == 13)
				{
					pontuacao = 0;
					return true;			
				}
				else if(pos_y == 14)
				{
					return false;
				}
				break;
			}
		}
	  }
}

bool check_if_touch_snake()
{
	for(int i=global_tamanho_cobra;i>1;i--)
	{
		if(cobra[0].posicao_x == cobra[i].posicao_x
		&& cobra[0].posicao_y == cobra[i].posicao_y)
		{
			return true;
		}
	}
	return false;
}

void Update_position()
{
	int aux,aux1;
        if(check_clean == global_tamanho_cobra)
    	{
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
	//a snake é plotada na tela imprimindo a cabeça e deixando o rastro dela
	// e na cauda dela eu vou apagando faço isso percorrendo todo o vetor da cobra
	// de trás pra frente  atribuindo a posição anterior de um para o de trás
	//na ponta da cauda eu faço atribuição também, porém depois de atribuir eu 
	//apago a ultima posição, pra cobra não ficar plotando infinitamente
	for(int i=global_tamanho_cobra;i>0;i--)
	{
		aux = cobra[i].posicao_x;
		aux1 = cobra[i].posicao_y;
		cobra[i].posicao_x = cobra[i-1].posicao_x;
		cobra[i].posicao_y = cobra[i-1].posicao_y;
		if(i == global_tamanho_cobra)
	    	gotoxy(aux,aux1,' ');
	}
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

		if((cobra[0].posicao_x <= 1 || cobra[0].posicao_x >= height)
		|| (cobra[0].posicao_y >= lenght || cobra[0].posicao_y <= 1)
        || (check_if_touch_snake()))    
		{		
			if(check_if_want_continue())
			{	

			}
			else
			{
				check_game = 0;
			}		
		}
	}
}

int main() {
	Game();
	
	return 0;
}
