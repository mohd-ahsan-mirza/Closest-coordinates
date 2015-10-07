#include"stdafx.h"

int main() {

	//%%%%%%%%%%%%%% MAKE SURE THAT WHEN "test3.txt" IS RUN, IT IS IN RELEASE MODE %%%%%%%%%%%%%%%%%%%%%//


	//The clock is just for measuring performance
	clock_t tStart = clock();

	NearestPoints p = NearestPoints("test3.txt");
	
	pair<Coordinate,Coordinate> res=p.nearestPoints();

	cout <<setprecision(16)<<"(" << res.first.getX() << "," << res.first.getY() <<") ";
	cout << setprecision(16)<<"(" << res.second.getX() << "," << res.second.getY() <<")"<< endl;
	
	// Uncomment first line and the two lines below to check how much time it takes for the program to execute
	cout << "\n-------------------------------------------------------" << endl;
	printf("Time taken: %.9fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	return 0;
}