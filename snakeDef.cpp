#include <iostream>
#include <vector>
#include "snakeHeader.h"

#define SPACE_CHAR ' '
#define UPPER_O_CHAR 'O'

const int Up=1;
const int Down=2;
const int Left=3;
const int Right=4;
const int check_clean=4;

const unsigned int DEFAULT_APPLE_POSITION[2] = {20,20};

Apple::Apple(int pos_x, int pos_y) {
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}

void Apple::setPosition(int set_x, int set_y) {
	this->pos_x = set_x;
	this->pos_y = set_y;
}

void Apple::resetApple() {
	this->pos_x = DEFAULT_APPLE_POSITION[0];
	this->pos_y = DEFAULT_APPLE_POSITION[1];
}

void Map::setObject(int length, int height, char caracter) {
	this->Matriz[length][height] = caracter;
}

char Map::getObject(int pos_x, int pos_y) {
	return this->Matriz[pos_x][pos_y];
}

Map::Map() {
	this->length = LENGTH;
	this->height = HEIGHT;
}

Map::~Map() {
	delete this;
}

int Map::getLength() {
	return this->length;
}

int Map::getHeight() {
	return this->height;
}

Body::Body(int pos_x, int pos_y) {
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}

void Body::incrementPosition(int new_posX, int new_posY) {
	this->pos_x += new_posX;
	this->pos_y += new_posY;
}

Snake::Snake() {
	this->constructSnake();
}

void Snake::constructSnake(std::vector<std::vector<int>> body){
	for(int pointVector=0; pointVector < body.size(); pointVector++) {
		this->snake->push_back(Body(body[pointVector][0], body[pointVector][1])); //Getting the position x and y for each body of the given snake
	}
}

void Snake::constructSnake() {
	this->snake = new std::vector<Body>();

	this->snake->push_back(Body(10,20));
	this->snake->push_back(Body(10,19));
	this->snake->push_back(Body(10,18));
}

void Snake::snakeReset() {
	this->constructSnake();
}

int Snake::getSize() {
	return this->snake->size();
}

bool isLineOnBottomOrTop(int line, int bottom=0, int height) {
	return (line == bottom || line == --height);
}

bool isColumnOnBottomOrTop(int column, int bottom=0, int top) {
	return (column == bottom || column == --top);
}

bool checkIfLineOrColumn(Map* map, int line, int column) {
	return isLineOnBottomOrTop(line, map->getHeight()) || isColumnOnBottomOrTop(column, map->getLength());
}

void checkIfCanSet_O_toMap(Map* map, int line, int column){
	if (checkIfLineOrColumn(map, line, column)) {
		map->setObject(line, column, UPPER_O_CHAR);
	}
}

void printColumnMap(Map* map, int line){
	for(int column=0; column < map->getLength(); column++) {
		map->setObject(line, column, SPACE_CHAR);
		checkIfCanSet_O_toMap(map, line, column);
		std::cout << map->getObject(line, column);
	}
}

void constructMap() {
	Map* map = new Map();

	for(int line=0; line < map->getHeight(); line++) {
		printColumnMap(map, line);
		std::cout << std::endl;
	}
}