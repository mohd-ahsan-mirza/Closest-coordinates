// EPISLON is the difference between 1 and the smallest value greater than 1 that is representable for the data type
#define EPISLON 0.0000000000000001
class Coordinate {

public:

	// Constructor takes xCoordinate, yCoordinate and a key as parameter . The key is just a unique identifier for every coordinate
	// The only reason key is a part of Coordinate is because of < operator which is required for when Coordinate is used in map as key
	Coordinate(double x, double y,int k);

	// Default constructor
	Coordinate();

	Coordinate(const Coordinate&);
	
	// Returns the yCoordinate of the cartesian product
	double getY();

	// Returns the xCoordinate of the cartesian product
	double getX();

	// Used for when comparing if two coordinates are equal or not
	friend bool operator== (const Coordinate& coordinate1, const Coordinate& coordinate2);
	
	// Used as comparison operator in map 
	friend bool operator < (const Coordinate& Left, const Coordinate& Right);

	// Returns the key of the coordinates
	int getKey();


	~Coordinate();

private:

	double x;
	double y;
	int key;


};
