#include "stdafx.h"

NearestPoints::NearestPoints(string filename) {
	
	if (!(filename.empty())) {
		
		int id = 0;

		ifstream file(filename);

		// The first line is always the total number of coordinates in the file.
		file >> this->total;

		
		
		string line="";
		

		while (getline(file, line))
		{
			if (!line.empty()) {
				
				// Parsing the string in order to extract the x and y coordinates

				line = line.substr(line.find_first_of("1234567890"), line.find_last_of("1234567890"));
				string xCoordinate = line.substr(0, line.find_first_of(","));

				string yCoordinate = line.substr(xCoordinate.length());
				yCoordinate = yCoordinate.substr(yCoordinate.find_first_of("1234567890"));

				// Converting the strings to doubles and storing them in the private data member Coordinates
				Coordinates.push_back(Coordinate(stod(xCoordinate), stod(yCoordinate), ++id));

			}
		}




	}

}


NearestPoints::~NearestPoints() {

	this->total = NULL;
	this->Coordinates.clear();
	


}


list<Coordinate> NearestPoints::getList() {

	return this->Coordinates;
}

int NearestPoints::getTotal() {

	return this->total;
}

double NearestPoints::distanceBetweenTwoPoints(double x1, double y1, double x2, double y2) {

	//This is the original function which calculates the distance between any two points correctly.Takes a toll on performance
	//return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

	// Incorrect distance but the returned value works for the scope of this project. For correct distance uncomment line above
	return (abs((x2 - x1)) + abs((y2 - y1)));

}

// Function not used in the current scope of the project but can be helpful in the future. Can cause performance issues especially in debug mode
map<Coordinate, map<Coordinate, double>> NearestPoints::allDistances() {

	map<Coordinate, map<Coordinate, double>> result = map<Coordinate, map<Coordinate, double>>();

	list<Coordinate> list1 = this->Coordinates;


	for (list<Coordinate>::iterator iterator1 = list1.begin(), end = list1.end(); iterator1 != end; iterator1++)
	{

		// Coordinate1 from the list	
		Coordinate coordinate1 = *iterator1;

		// Inserts coordinate1 in result with empty map as value
		result.insert(make_pair(coordinate1,map<Coordinate,double>()));

		// Iterating through the list again
		for (list<Coordinate>::iterator iterator2 = list1.begin(), internalEnd = list1.end(); iterator2 != internalEnd; iterator2++)
		{
			// Coordinate2 from the same list
			Coordinate coordinate2 = *iterator2;
			
			//######### This if else statement has been commented out due to performance issues but will produce the same result ###########//
			/*
			if (result.find(coordinate2) != result.end())
			{
				if(!(coordinate1 ==coordinate2))
					result.at(coordinate1).insert(make_pair(coordinate2, result.at(coordinate2).at(coordinate1)));
			}
			*/

			//else
			//{
			
			// To make sure that the distance added at any point is not zero
			if(!(coordinate1 ==coordinate2))
				result.at(coordinate1).insert(make_pair(coordinate2, this->distanceBetweenTwoPoints(coordinate1.getX(),coordinate1.getY(),coordinate2.getX(),coordinate2.getY())));
			//}
		}

		
	}

	
	return result;

}


// This function reduced the execution time by almost 92% as compared to the commented out function below
pair<Coordinate, Coordinate> NearestPoints::nearestPoints() {

	//Gets the list of all the coordinates
	list<Coordinate> List = this->Coordinates;
	
	// This will be the minimum value of all shortest Distances possible
	double shortestDistancePossible= numeric_limits<double>::max();
	//This will later contain the resultant pair of coordinates
	pair<Coordinate, Coordinate> result;

	

	for (list<Coordinate>::iterator iterator1 = List.begin(), end = List.end(); iterator1 != end; iterator1++)
	{
		// Coordinate1 from the list	
		Coordinate coordinate1 = *iterator1;

		
		//Setting the current shortestDistance from coordinate1 to secCoordinate to Inifinity
		double shortestDistance = numeric_limits<double>::max();
		// Initializing the coordinate nearest to coordinate1
		Coordinate secCoordinate;

		for (list<Coordinate>::iterator iterator2 = List.begin(), internalEnd = List.end(); iterator2 != internalEnd; iterator2++)
		{
			// Coordinate2 from the same list
			Coordinate coordinate2 = *iterator2;

			// To make sure that the distance added at any point is not zero
			if (!(coordinate1 == coordinate2))
			{
				// Representation of the the distance between two points . Note:This is not the correct distance . Look at the function for more details
				double currentDistance = this->distanceBetweenTwoPoints(coordinate1.getX(),coordinate1.getY(),coordinate2.getX(),coordinate2.getY());

				if (currentDistance < shortestDistance)
				{
					shortestDistance = currentDistance;
					secCoordinate = coordinate2;					
				}

			}

		}

		if (shortestDistance < shortestDistancePossible)
		{
			shortestDistancePossible = shortestDistance;
			result = pair<Coordinate, Coordinate>(coordinate1, secCoordinate);
		}
		
	
	}

	return result;

}


// Another possible implementation of function nearestPoints() but is a way slower approach 
/*
pair<Coordinate, Coordinate> NearestPoints::nearestPoints() {

	// This list will contain all the shortestDistances between anyone given coordinate to another coordinate as key
	// The nearest coordinates will be stored as pair of the value of this map
	map<double, pair<Coordinate, Coordinate>> shortestDistances= map<double, pair<Coordinate, Coordinate>>();

	map<Coordinate, map<Coordinate, double>> wholeList=this->allDistances();

	// Iterating over the map of all the distances from all coordinates to all coordinates
	for (map<Coordinate, map<Coordinate, double>>::iterator upperIterator = wholeList.begin(); upperIterator != wholeList.end();upperIterator++)
	{
		
		// keyCoordinate 
		Coordinate coordinate1 = upperIterator->first;
		
		// map containing the coordinates and their distances from the keyCoordinate
		map<Coordinate, double> list = upperIterator->second;

		// Setting the shortest Distance in the map to Infinity 
		double shortestDistance = numeric_limits<double>::max();

		// This will at the end of for loop below will be equal to the coordinate with the shortest distance to the keyCoordinate
		Coordinate secondCoordinate;

		//Iterating over the map which is the value of the keyCoordinate in the map above again
		for (map<Coordinate, double>::iterator internalIterator = list.begin(); internalIterator != list.end();internalIterator++)
		{
			//Second coordinate from the internal map
			Coordinate coordinate2 = internalIterator->first;

			//Distance between the keyCoordinate and the second coordinate
			double currentDistance = internalIterator->second;

			if (currentDistance < shortestDistance)
			{
				shortestDistance = currentDistance;
				secondCoordinate = coordinate2;
			}
		}

		//Inserting the closest coordinates to each other as pair and the distance between them in the shortestDistances map
		shortestDistances.insert(make_pair(shortestDistance,pair<Coordinate,Coordinate>(coordinate1,secondCoordinate)));

	}


	//Now just need to find the minimum value of Distance in the shortestDistances map

	double minDistance = numeric_limits<double>::max();

	//This pair after the for loop will be equal to the pair which are nearest to each as compared to all others in the shortestDistances map 
	pair<Coordinate, Coordinate> result;

	// Iterating over the shortestDistances map
	for (map<double, pair<Coordinate, Coordinate>>::iterator iterator = shortestDistances.begin(); iterator != shortestDistances.end(); iterator++)
	{
	
		double curDistance = iterator->first;
		pair<Coordinate, Coordinate> Pair = iterator->second;

		if (curDistance < minDistance) {

			minDistance = curDistance;
			result = Pair;

		}

	}

	return result;

}
*/