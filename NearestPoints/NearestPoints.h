#pragma once
#include "stdafx.h"



// This class is where the calculation for the two nearest coordinates is computed
class NearestPoints {

public:

	// Constructor which takes file name containing the coordinates as argument 
	NearestPoints(string filename);

	// Returns the private data member Coordinates
	list<Coordinate> getList();

	// Returns the private data member total
	int getTotal();

	// Computes the distance between two cartesian coordinates using the the Distance Formula 
	//Goto : http://hotmath.com/hotmath_help/topics/distance-formula.html for more details

	double distanceBetweenTwoPoints(double x1, double y1, double x2, double y2);

	// Returns a pair containing the two closest coordinates in terms of distance
	pair<Coordinate, Coordinate> nearestPoints();

	~NearestPoints();

	// Finds the nearest coordinate and stores it in the secondCoordinate pointer and returns the distance between the first and it's nearest
	double otherCoordinate(Coordinate firstCoordinate,Coordinate** secondCoordinate);

private:

	// List of all coordinates are stored in this list after it is read from a file
	list<Coordinate> Coordinates;

	// Private function which returns all the distances from all the coordinates in a map.
	//The key is keyCoordinate from which all distances to other coordinates is calculated.
	// The value which is another map contains all other coordinates except for the keycoordinate as KEY and distance from key to them as value
	map<Coordinate, map<Coordinate, double>> allDistances();
	
	// Total number of coordinates .Not really used, but is given in the file.
	int total;


};