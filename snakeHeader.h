#ifndef SNAKE_HEADER
#define SNAKE_HEADER

#define LENGTH 25
#define HEIGHT 75

class Apple {
public:
	static int pos_x;
	static int pos_y;
	Apple(int pos_x, int pos_y);
	void setPosicao(int set_x, int set_y);
};

class Map {
private:
	int length;
	int height;
public:
	char Matriz[LENGTH][HEIGHT];
public:
	Map();
	~Map();
	void setObject(int length, int height, char caracter);
	char getObject(int pos_x, int pos_y);
	int getLength();
	int getHeight();
};

class Snake {
public:
    int pos_x;
    int pos_y;
	Snake(int pos_x, int pos_y);
	void sumPosicao(int set_x, int set_y);
};

bool isLineOnBottomOrTop(int line, int bottom=0, int height);
bool isColumnOnBottomOrTop(int column, int bottom=0, int top); 
bool checkIfLineOrColumn(Map* map, int line, int column); 
void checkIfCanSet_O_toMap(Map* map, int line, int column); 
void printColumnMap(Map* map, int line);
void constructMap();

#endif