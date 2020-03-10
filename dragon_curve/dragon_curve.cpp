// Finds dragon curve up to N many iterations.

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

int main() {
	// Variable definition
	int i, j, N, base;
	string orientation = "o", chirality = "o";
	int pos[2] = {0,0}, move[2], rot[2][2];
	ofstream solution;

	// Input initial orientation
	while(orientation != "u" && orientation != "d" && orientation != "l" && orientation != "r")
	{
		cout << "Input initial curve orientation: "; 	// Ask for initial curve orientation
		cin >> orientation;
		if(orientation != "u" && orientation != "d" && orientation != "l" && orientation != "r")
		{
			cout << "Invalid input!" << endl;
			cout << "Please input one of the following:" << endl;
			cout << "  up (u)" << endl;
			cout << "  dow (d)" << endl;
			cout << "  left (l)" << endl;
			cout << "  right (r)" << endl;
			cout << endl << endl;
		}
	}
	if(orientation == "u")
	{
		move[0] = 0;
		move[1] = 1;
	}
	else if(orientation == "d")
	{
		move[0] = 0;
		move[1] = -1;
	}
	else if(orientation == "l")
	{
		move[0] = -1;
		move[1] = 0;
	}
	else
	{
		move[0] = 1;
		move[1] = 0;
	}
	// Input chirality
	while(chirality != "l" && chirality != "r")
	{
		cout << "Input curve chirality: "; 	// Ask for curve chirality
		cin >> chirality;
		if(chirality != "l" && chirality != "r")
		{
			cout << "Invalid input!" << endl;
			cout << "Please input one of the following:" << endl;
			cout << "  left (l)" << endl;
			cout << "  right (r)" << endl;
			cout << endl << endl;
		}
	}
	if(chirality == "l")
	{
		rot[0][0] = 0;
		rot[1][0] = 1;
		rot[0][1] = -1;
		rot[1][1] = 0;
	}
	else
	{
		rot[0][0] = 0;
		rot[1][0] = -1;
		rot[0][1] = 1;
		rot[1][1] = 0;
	}
	// Input number of iterations
	cout << "Input number of iterations: ";
	cin >> N;
	vector<int> curve_x(pow(2,N));
	vector<int> curve_y(pow(2,N));

	// Iterate to draw curve and save points to file
	solution.open("dragon_curve.txt");		// Open output file
	solution << pos[0] << " " << pos[1] << endl;	// Output current position to file
	pos[0] = pos[0] + move[0];			// Update current position
	curve_x[1] = pos[0];
	pos[1] = pos[1] + move[1];			// Update current position
	curve_y[1] = pos[1];
	solution << pos[0] << " " << pos[1] << endl;	// Output current position to file
	for(i = 0; i < N; i++)
	{
		base = pow(2,i);
		for(j = 0; j < base; j++)
		{
			move[0] = rot[0][0]*(curve_x[base-j]-curve_x[base-j-1]) + rot[0][1]*(curve_y[base-j]-curve_y[base-j-1]);
			move[1] = rot[1][0]*(curve_x[base-j]-curve_x[base-j-1]) + rot[1][1]*(curve_y[base-j]-curve_y[base-j-1]);
			pos[0] = pos[0] + move[0];			// Update current position
			curve_x[base+j+1] = pos[0];
			pos[1] = pos[1] + move[1];			// Update current position
			curve_y[base+j+1] = pos[1];
			solution << pos[0] << " " << pos[1] << endl;	// Output current position to file
		}
	}
	solution.close();				// Close file
	return 0; // End of the program
}
