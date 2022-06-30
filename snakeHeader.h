#ifndef SNAKE_HEADER
#define SNAKE_HEADER

#define LENGTH 25
#define HEIGHT 75

extern const int Up;
extern const int Down;
extern const int Left;
extern const int Right;
extern const int check_clean;

class Apple {
public:
	static int pos_x;
	static int pos_y;
	Apple(int pos_x, int pos_y);
	void setPosition(int set_x, int set_y);
	void resetApple();
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

class Body {
public:
    int pos_x;
    int pos_y;
	Body(int pos_x, int pos_y);
	void incrementPosition(int set_x, int set_y);
	int snakeSize();
};

class Snake {
private:
	std::vector<Body>* snake;
public:
	Snake();
	int getSize();
	void snakeReset();
private:
	void constructSnake(std::vector<std::vector<int>> body);
	void constructSnake();
};

bool isLineOnBottomOrTop(int line, int bottom=0, int height);
bool isColumnOnBottomOrTop(int column, int bottom=0, int top); 
bool checkIfLineOrColumn(Map* map, int line, int column); 
void checkIfCanSet_O_toMap(Map* map, int line, int column); 
void printColumnMap(Map* map, int line);
void constructMap();

#endif