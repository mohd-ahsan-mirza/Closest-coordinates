#include"stdafx.h"

Coordinate::Coordinate(double x,double y,int key) {

	this->x = x;
	this->y = y;
	this->key = key;
	

}

Coordinate::Coordinate(const Coordinate& other) {

	this->x = other.x;
	this->y = other.y;
	this->key = other.key;

}

Coordinate::Coordinate() {

	this->x = 0;
	this-> y = 0;
	this->key = -1;

}

Coordinate::~Coordinate() {

	this->x = NULL;
	this->y = NULL;
	this->key = NULL;
}



// Two coordinates are equal only when their x and y coordinates are equal to each other
bool operator== (const Coordinate& coordinate1, const Coordinate& coordinate2) {
	
	// Note: This is prone to error since comparing two doubles to 15 decimal points can cause issues 
	if ((abs(coordinate1.x - coordinate2.x) < EPISLON) && (abs(coordinate1.y - coordinate2.y) < EPISLON)) {
		
		return true;
	}
	else
		return false;
}

// Compares on the bases of the unique keys of the coordinates
bool operator < (const Coordinate& Left, const Coordinate& Right) {

	if (Left.key < Right.key)
		return true;
	else
		return false;
}


double Coordinate::getX() { return x; };

double Coordinate::getY() { return y; };

int Coordinate::getKey() { return this->key; };