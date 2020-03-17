#include <iostream>
#include "snakecab.h"

Apple::Apple(int pos_x, int pos_y)
{
	posicao_xp = pos_x;
	posicao_yp = pos_y;
}

void Apple::Set_pos(int set_x, int set_y)
{
	posicao_xp = set_x;
	posicao_yp = set_y;
}

void Mapa::Set_object(int l, int h,char caracter)
{
	this->Matriz[l][h] = caracter;
}
Mapa::Mapa()
{
	this->x = height;
	this->y = lenght;
}

int Mapa::Get_hei()
{
	return y;
}
int Mapa::Get_len()
{
	return x;
}

Snake::Snake(int elemento_y, int elemento_x)
{
	posicao_x = elemento_x;
	posicao_y = elemento_y;
}

Snake::Snake(){}

void Snake::Sum_posicao(int set_x, int set_y)
{
	posicao_x+=set_x;
	posicao_y+=set_y;
}	

void inicializar_mapa()
{
	Mapa map;
	for(int i=0;i<map.Get_hei();i++)
	{
		for(int j=0;j<map.Get_len();j++)
		{
			map.Set_object(i,j,' ');
			if((i == 0 || i == map.Get_hei()-1) || (j == 0 || j == map.Get_len()-1))
			{
				map.Set_object(i,j,'O');
			}
			std::cout << map.Matriz[i][j];
		}
		std::cout << std::endl;
	}
}