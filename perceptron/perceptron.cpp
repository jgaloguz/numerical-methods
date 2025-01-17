// Perceptron algorithm

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

// Create 2D array template
template <class T> T **create2D(int h, int w)
{
   T **array = new T*[h];
   for (int i = 0; i < h; i++) array[i] = new T[w];
   return array;
};

// Delete 2D array template
template <class T> void delete2D(T **array, int h, int w)
{
   for (int i = 0; i < h; i++) delete[] array[i];
   delete array;
};

// Initialize array function
void init2D(float **A, int h, int w)
{
   int i,j;    // dummy indinces
   for (i = 0; i < h; i++) {
      for (j = 0; j < w; j++) {
         A[i][j] = 0;   // set entry to zero
      };
   };
};

// Perceptron
float percep(vector<float> &W, float b, float **X, int vec, int dim)
{
   int i;         // dummy index
   float S = b;   // value related to distance from and location wrt to hyperplane
   for (i = 0; i < dim; i++) S += W[i]*X[vec][i];  // find whether point is "above" or "below" hyperplane
   if (S > 0) return 1;    // above
   else return 0;          // below
};

int main() {
   // Variable definition
   int i, j, k;                        // Misc indices
   int N, K;                        // Size of separable set and dimension of each vector in the set
   int counter = 0;                    // Counter for the numbe of updates during training
   float LR = 0.1;                        // Learning rate
   float bias = 0;                        // Bias
   float y = 0, delta = 0;                   // Dummy variables
   float **data;                       // data matrix
   bool check = true;                     // Check to see if perceptron is trained
   ifstream data_set;                     // File with separable data set
   ofstream hyperplane;                   // File with weight and bias to separate the data set
   
   // Open data file
   data_set.open("separable_set.txt");             // open file
   data_set >> N;                      // Input number of vectors in the data set
   data_set >> K;                      // Input number of dimensions for each vector
   
   // Allocate memory for array (and initialize)
   data = create2D<float>(N,K);
   init2D(data,N,K);
   // Allocate memory for weight and classification vectors (and initialize)
   vector<float> weight(K);
   for (i = 0; i < K; i++) weight[i] = 0; // initialize weights
   vector<int> classif(N); // declare classification array
   
   // Input vectors from file
   for (j = 0; j < N; j++) {
      for (i = 0; i < K; i++) data_set >> data[j][i];
      data_set >> classif[j];
   };
   data_set.close();                   // close file
   
   // Train perceptron
   while (check) {
      check = false;
      for (j = 0; j < N; j++) {
         y = percep(weight, bias, data, j, K);        // check jth point
         // Update weights and bias if classification is incorrect
         if (y != classif[j]) {
            counter++;
            check = true;                 // remian in loop
            delta = LR*(classif[j] - y);  // compute amount to change bias and weights
            bias += delta;                // change bias
            for (i = 0; i < K; i++) weight[i] += delta*data[j][i];         // change weights
         };
      };
   };
   
   cout << endl << "Perceptron trained!" << endl;
   cout << "Number of updates made during training: " << counter << endl << endl;
   // Output weight and bias to file for visualization
   hyperplane.open("hyperplane.txt");     // open file
   hyperplane << bias << endl;         // output bias
   for (i = 0; i < K; i++) hyperplane << weight[i] << " ";     // output weights
   hyperplane.close();           // close file
   
   // Deallocate memory
   delete2D<float>(data,N,K);
   
   return 0;
};
