// Perceptron algorithm

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

// Define create 2D array template
template <class T> T **create2D(int h, int w)
{
	T **array = new T*[h];
	for(int i = 0; i < h; i++)
	{
		array[i] = new T[w];
	}
	return array;
}

// Define delete 2D array template
template <class T> void delete2D(T **array, int h, int w)
{
	for(int i = 0; i < h; i++)
	{
		delete[] array[i];
	}
	delete array;
}

// Define initializing array function
void init2D(float **A, int h, int w)
{
	int i,j;
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			A[i][j] = 0;
		}
	}
}

// Define print array function
float percep(vector<float> &W, float b, float **X, int vec, int dim)
{
	int i;
	float S = b;
	for(i = 0; i < dim; i++)
	{
		S += W[i]*X[vec][i];
	}
	if (S > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int main() {
	// Variable definition
	int i, j, k;								// Misc indices
	int N, K;								// Size of separable set and dimension of each vector in the set
	int counter = 0;							// Counter for the numbe of updates during training
	float LR = 0.1;								// Learning rate
	float bias = 0;								// Bias
	float y = 0, delta = 0;							// Dummy variables
	float **data;
	bool check = true;							// Check to see if perceptron is trained
	ifstream data_set;							// File with separable data set
	ofstream hyperplane;							// File with weight and bias to separate the data set
	
	// Open data file
	data_set.open("separable_set.txt");
	data_set >> N;								// Input number of vectors in the data set
	data_set >> K;								// Input number of dimensions for each vector
	
	// Allocate memory for array (and initialize)
	data = create2D<float>(N,K);
	init2D(data,N,K);
	// Allocate memory for weight and classification vectors (and initialize)
	vector<float> weight(K);
	for (i = 0; i < K; i++)
	{
		weight[i] = 0;
	}
	vector<int> classif(N);
	
	// Input vectors from file
	for (j = 0; j < N; j++)
	{
		for (i = 0; i < K; i++)
		{
			data_set >> data[j][i];
		}
		data_set >> classif[j];
	}
	data_set.close();
	
	// Train perceptron
	while (check)
	{
		check = false;
		for (j = 0; j < N; j++)
		{
			y = percep(weight, bias, data, j, K);
			if (y != classif[j])					// Update weights and bias if classification is incorrect
			{
				counter++;
				check = true;
				delta = LR*(classif[j] - y);
				bias += delta;
				for (i = 0; i < K; i++)
				{
					weight[i] += delta*data[j][i];
				}
			}
		}
	}
	
	cout << endl << "Perceptron trained!" << endl;
	cout << "Number of updates made during training: " << counter << endl << endl;
	// Output weight and bias to file for visualization
	hyperplane.open("hyperplane.txt");
	hyperplane << bias << endl;
	for (i = 0; i < K; i++)
	{
		hyperplane << weight[i] << " ";
	}
	hyperplane.close();
	
	// Deallocate memory
	delete2D<float>(data,N,K);
	
	return 0;
}
