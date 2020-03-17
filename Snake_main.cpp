#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include "snakecab.h"

//snake from scratch no console feito com função gotoxy 
//made it by lucas lima

//variaveis globais
unsigned int global_tamanho_cobra = 3,qtd_maca=0,pontuacao=0;
unsigned int Up=1,Down=2,Left=3,Right=4;
unsigned int Keyword = Right;
unsigned int check_clean = 4;

bool check_game = 1;

//declaração do vetor cobra
Snake cobra[100] = {{10,20},{10,19},{10,18}};

//posição estática da maça
int Apple::posicao_xp;
int Apple::posicao_yp;

Apple maca(20,20);

//aqui a mágica acontece, basicamente eu coloco um x e y e a função gotoxy imprime
//no console na posição exata em que foi passada
void gotoxy(int x, int y,char print_user)
{
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
        || (maca.posicao_yp >= lenght-1 || maca.posicao_xp >= height-1))   
		{
			for(int i=global_tamanho_cobra;i>1;i--)
			{
				if(maca.posicao_xp == cobra[i].posicao_x
				&& maca.posicao_yp == cobra[i].posicao_y)
				{
					maca.posicao_xp = rand()%70;
		        	maca.posicao_yp = rand()%20;
				}
			}
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
//preciso sabe se voce quer continuar ou nao
bool check_if_want_continue()
{
	//primeiramente apago a tela depois coloca a posição do ponteiro
	//e fica um gui bonitinho 
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
	if(Keyword == Up)
		cobra->Sum_posicao(0,-1);
	else if(Keyword == Down)
		cobra->Sum_posicao(0,1);
	else if(Keyword == Left)
		cobra->Sum_posicao(-1,0);
	else if(Keyword == Right)
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
//chamando todas as funcs pra fazer o jogo funcionar de fato
void Jogo()
{
	inicializar_mapa();
	char keyboard_char;
	while(check_game)
	{
		Print_snake_apple();
		Update_position();
		if(kbhit()){keyboard_char = getch();}
        for(int i=0;i<=30000000;i++);
		switch (keyboard_char)
		{
			case'w':
				if(Keyword != Down)
					Keyword = Up;
				break;
			case's':
				if(Keyword != Up)
					Keyword = Down;
				break;
			case'a':
				if(Keyword != Right)
					Keyword = Left;
				break;
			case'd':
				if(Keyword != Left)
					Keyword = Right;
				break;
		}
		if((cobra[0].posicao_x <= 1 || cobra[0].posicao_x >= height)
		|| (cobra[0].posicao_y >= lenght || cobra[0].posicao_y <= 1)
        || (check_if_touch_snake()))    
		{		
			if(check_if_want_continue())
			{
				check_clean = 4;
				system("cls");
				global_tamanho_cobra = 4;	
				maca.Set_pos(20,20);
				cobra[0].posicao_x = 10;
				cobra[0].posicao_y = 10;
				inicializar_mapa();	
			}
			else
			{
				check_game = 0;
			}		
		}
	}
}
//não gosto de colocar muitas coisas na main sla ksksksksk
int main()
{
	while(true)
	{
		Jogo();
		break;
	}
	std::cout << "\n\n\n\n\n";
	return 0;
}
