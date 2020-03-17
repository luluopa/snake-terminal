#ifndef SNAKE_CAB
#define SNAKE_CAB

#define lenght 23
#define height 75

class Apple
{
public:
	static int posicao_xp;
	static int posicao_yp;
	Apple(int pos_x, int pos_y);
	void Set_pos(int set_x, int set_y);
};
class Mapa
{
private:
	int x;
	int y;
public:
	char Matriz[lenght][height];
public:
	Mapa();
	void Set_object(int l, int h,char caracter);
	int Get_len();
	int Get_hei();
};

class Snake
{
public:
    int posicao_x;
    int posicao_y;
	Snake(int elemento_y, int elemento_x);
	Snake();
	void Sum_posicao(int set_x, int set_y);
};

void inicializar_mapa();

#endif