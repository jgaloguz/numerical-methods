// Canny edge detection algorithm

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

// Definition of pi
const double pi = M_PI;
const double pi_2 = M_PI/2;
const double pi_4 = M_PI/4;
const double npi_2 = -1*M_PI/2;
const double npi_4 = -1*M_PI/4;

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
void init2D(double **A, int h, int w)
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
void print2D(double **A, int h, int w, int p)
{
	int i,j;
	cout << setprecision(p);
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
}

// Define read from file function
void read2D(double **A, ifstream& file, string path, int h, int w, int margin_h, int margin_w)
{
	int i,j;
	file.open(path);			// Open file
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			file >> A[i+margin_h][j+margin_w];	// Input entries
		}
	}
	file.close();				// Close file
}

// Define write to file function
void write2D(double **A, ofstream& file, string path, int h, int w, int margin_h, int margin_w)
{
	int i,j;
	file.open(path);			// Open file
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			file << A[i+margin_h][j+margin_w] << " ";	// Output entries
		}
		file << endl;
	}
	file.close();				// Close file
}

// Define matrix dot product function
double mat_dot(double **A, double **B, int lim_h, int lim_w, int shift_h, int shift_w, int H, int W)
{
	int i,j;
	double S = 0;
	for(i = 0; i < lim_h; i++)
	{
		for(j = 0; j < lim_w; j++)
		{
			S += A[(i+shift_h) % H][(j+shift_w) % W]*B[i][j];
		}
	}
	return S;
}

// Define convolution function 2D arrays
void conv2D(double **img, double **ker, double **con, int h, int w, int margin_h, int margin_w, int H, int W, int lim_h, int lim_w)
{
	int i,j;
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			con[i+margin_h][j+margin_w] = mat_dot(img, ker, lim_h, lim_w, i, j, H, W);
		}
	}
}

// Define pad image function (currently not being used)
/*
void pad_image(double **raw_img, double **pad_img, int h, int w, int margin_h, int margin_w)
{
	int i,j;
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			pad_img[i+margin_h][j+margin_w] = raw_img[i][j];
		}
	}
}
*/

// Define Gaussian smoother initializing function
void G_smooth(double **G, int n_G, double std)
{
	int i,j;
	int k = n_G/2;
	if(std == 0)						// No smoothing
	{
		G[k][k] = 1;
	}
	else							// Smoothing
	{
		double var = pow(std,2);
		double twovar = 2*var;
		double twopivar = pi*twovar;
		for(i = 0; i < n_G; i++)
		{
			for(j = 0; j < n_G; j++)
			{
				G[i][j] = exp(-(pow(i-k,2)+pow(j-k,2))/twovar)/twopivar;
			}
		}
	}
}

// Define smooth image function
void smooth_image(double **img, double **smooth_image, int n_G, double std, int h, int w, int margin_h, int margin_w, int H, int W)
{
	int i,j;
	double **gauss_smoother;						// Gaussian smoother

	// Allocate memory
	gauss_smoother = create2D<double>(H,W);
	// Initilize array
	init2D(gauss_smoother,H,W);
	// Find smoothing coefficients
	G_smooth(gauss_smoother,n_G,std);

	conv2D(img,gauss_smoother,smooth_image,h,w,margin_h,margin_w,H,W,n_G,n_G);	// Smooth image

	// Delete memory
	delete2D(gauss_smoother,H,W);
}

// Define compute gradients function
void comp_grad(double **img, double **Ln, double **Ld, int h, int w, int margin_h, int margin_w, int H, int W)
{
	int i,j,k,l;
	double **Sx, **Sy;						// x and y finite difference operators
	double **Lx, **Ly;						// x and y approximate gradient arrays
	double diag, cent, ndiag, ncent;				// coefficients for operators

	// Allocate memory
	Sx = create2D<double>(H,W);
	Sy = create2D<double>(H,W);
	Lx = create2D<double>(H,W);
	Ly = create2D<double>(H,W);
	// Initialize arrays
	init2D(Sx,H,W);
	init2D(Sy,H,W);
	init2D(Lx,H,W);
	init2D(Ly,H,W);
	// Set coefficients
	diag = 3;
	cent = 10;
	ndiag = -1*diag;
	ncent = -1*cent;
	Sx[0][0] = diag;
	Sx[1][0] = cent;
	Sx[2][0] = diag;
	Sx[0][2] = ndiag;
	Sx[1][2] = ncent;
	Sx[2][2] = ndiag;
	Sy[0][0] = diag;
	Sy[0][1] = cent;
	Sy[0][2] = diag;
	Sy[2][0] = ndiag;
	Sy[2][1] = ncent;
	Sy[2][2] = ndiag;

	// Find x and y gradients
	conv2D(img,Sx,Lx,h,w,margin_h,margin_w,H,W,3,3);
	conv2D(img,Sy,Ly,h,w,margin_h,margin_w,H,W,3,3);

	// Find gradient magnitude and direction
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			k = i+margin_h;
			l = j+margin_w;
			Ln[k][l] = sqrt(pow(Lx[k][l],2)+pow(Ly[k][l],2));	// Gradient norm
			Ld[k][l] = atan(Ly[k][l]/Lx[k][l]);			// Gradient direction
		}
	}

	// Delete memory
	delete2D(Sx,H,W);
	delete2D(Sy,H,W);
	delete2D(Lx,H,W);
	delete2D(Ly,H,W);
}

// Define interpolation function
double interpol(double A, double B, double a, double b, double h, double t)
{
	return A*(b-t)/h + B*(t-a)/h;
}

// Define non-maximum suppression function
void non_max_supp(double **Ln, double **Ld, double **L, int h, int w, int margin_h, int margin_w)
{
	int i,j,k,l;
	double pgrad,ngrad;					// Interpolated values in the positive and negative gradient directions

	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			k = i+margin_h;
			l = j+margin_w;
			// Interpolate
			if(Ld[k][l] > pi_4)
			{
				pgrad = interpol(Ln[k-1][l+1],Ln[k-1][l],pi_4,pi_2,pi_4,Ld[k][l]);
				ngrad = interpol(Ln[k+1][l-1],Ln[k+1][l],pi_4,pi_2,pi_4,Ld[k][l]);
			}
			else if(Ld[k][l] > 0)
			{
				pgrad = interpol(Ln[k][l+1],Ln[k-1][l+1],0,pi_4,pi_4,Ld[k][l]);
				ngrad = interpol(Ln[k][l-1],Ln[k+1][l-1],0,pi_4,pi_4,Ld[k][l]);
			}
			else if(Ld[k][l] > npi_4)
			{
				pgrad = interpol(Ln[k+1][l+1],Ln[k][l+1],npi_4,0,pi_4,Ld[k][l]);
				ngrad = interpol(Ln[k-1][l-1],Ln[k][l-1],npi_4,0,pi_4,Ld[k][l]); 
			}
			else
			{
				pgrad = interpol(Ln[k+1][l],Ln[k+1][l+1],npi_2,npi_4,pi_4,Ld[k][l]);
				ngrad = interpol(Ln[k-1][l],Ln[k-1][l-1],npi_2,npi_4,pi_4,Ld[k][l]);
			}
			// Compare
			if(Ln[k][l] >= pgrad && Ln[k][l] >= ngrad)
			{
				L[k][l] = Ln[k][l];				// Keep maximum values only
			}
		}
	}
}

// Define max function
double max2D(double **A, int h, int w, int margin_h, int margin_w)
{
	int i,j,k,l;
	double max = 0;
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			k = i+margin_h;
			l = j+margin_w;
			if(A[k][l] > max)			// Check max
			{
				max = A[k][l];			// Update max
			}
		}
	}
	return max;
}

// Define two threshold function
void two_threshold(double **L, double ht, double lt, int h, int w, int margin_h, int margin_w)
{
	int i,j,k,l;
	double Lij, max = max2D(L,h,w,margin_h,margin_w);
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			k = i+margin_h;
			l = j+margin_w;
			Lij = L[k][l]/max;
			if(Lij <= lt)
			{
				L[k][l] = 0;			// Suppress if under low threshold
			}
			else if(Lij < ht)
			{
				L[k][l] = 0.5;			// Weak edge if between low and high threshold
			}
			else
			{
				L[k][l] = 1;			// Strong edge if higher than
			}
		}
	}
}

// Define copy matrix function
void copy2D(double **A, double **B, int h, int w, int margin_h, int margin_w)
{
	int i,j,k,l;
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			k = i+margin_h;
			l = j+margin_w;
			B[k][l] = A[k][l];			// Copy array A to array B
		}
	}
}

// Define check equality function
bool check2D(double **A, double **B, int h, int w, int margin_h, int margin_w)
{
	int i,j,k,l;
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			k = i+margin_h;
			l = j+margin_w;
			if(A[k][l] != B[k][l])
			{
				return true;		// TRUE if matrices are NOT equal
			}
		}
	}
	return false;					// FALSE if matrices are equal
}

// Define hysteresis function
void hysteresis(double **L, double **edges, int h, int w, int margin_h, int margin_w)
{
	int i,j,k,l;
	do {
		copy2D(L,edges,h,w,margin_h,margin_w);
		for(i = 0; i < h; i++)
		{
			for(j = 0; j < w; j++)
			{
				k = i+margin_h;
				l = j+margin_w;
				// Trace weak edges that link with strong edges
				if(L[k][l] == 1)
				{
					if(L[k][l+1] == 0.5)
					{
						L[k][l+1] = 1;
					}
					if(L[k-1][l+1] == 0.5)
					{
						L[k-1][l+1] = 1;
					}
					if(L[k-1][l] == 0.5)
					{
						L[k-1][l] = 1;
					}
					if(L[k-1][l-1] == 0.5)
					{
						L[k-1][l-1] = 1;
					}
					if(L[k][l-1] == 0.5)
					{
						L[k][l-1] = 1;
					}
					if(L[k+1][l-1] == 0.5)
					{
						L[k+1][l-1] = 1;
					}
					if(L[k+1][l] == 0.5)
					{
						L[k+1][l] = 1;
					}
					if(L[k+1][l+1] == 0.5)
					{
						L[k+1][l+1] = 1;
					}
				}
			}
		}
	} while(check2D(L,edges,h,w,margin_h,margin_w));		// Check matrix equality
	// Suppress isolated weak edges
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			k = i+margin_h;
			l = j+margin_w;
			if(edges[k][l] == 0.5)
			{
				edges[k][l] = 0;
			}
		}
	}
}

int main() {
	// Variable definition
	int h, w;							// Height and width of original image
	int margin_h, margin_w;						// Margins for height and width
	int H, W;							// Height and width of image with margins
	int n_G;							// Height/width of Gaussian smoother
	int std;							// Std of Gaussian smoother
	double h_thres;							// High threshold
	double l_thres;							// Low threshold

	double **raw_img;						// Raw image
	double **pad_img;						// Image with margins
	double **smo_img;						// Smoothed image
	double **Ln, **Ld;						// Norm and direction of gradient
	double **maxL;							// Thinned gradient array
	double **edges;							// Blob analysis

	string dims_path = "matrices/dims.txt";				// Path for dimensions text file
	string raw_img_path = "matrices/raw_img.txt";			// Path for image text file
	string smo_img_path = "matrices/smo_img.txt";			// Path for smoothed image text file
	string grad_path = "matrices/grad.txt";				// Path for gradient text file
	string thin_grad_path = "matrices/thin_grad.txt";		// Path for thinned gradient text file
	string ws_edges_path = "matrices/ws_edges.txt";			// Path for weak/strong edges
	string edges_path = "matrices/edges.txt";			// Path for final edges

	ifstream dims_file;						// In file for raw image dimensions
	ifstream raw_img_file;						// In file for raw image data
	ofstream smo_img_file;						// Out file for smoothed image data
	ofstream grad_file;						// Out file for gradient image data
	ofstream thin_grad_file;					// Out file for thinned gradient image data
	ofstream ws_edges_file;						// Out file for weak/strong edges
	ofstream edges_file;						// Out file for edges

	// Set key parameters
	n_G = 5;							// Gaussian smoother dimensions
	std = 1;							// Std of Gaussian smoother
	h_thres = 0.1;							// High threshold
	l_thres = 0.01;							// Low threshold

	// Read image dimensions from file
	dims_file.open(dims_path);					// Open dimensions file
	dims_file >> h >> w;						// Read height and width
	dims_file.close();						// Close dimensions file

	// Compute derived parameters
	margin_h = n_G/2;						// Height margin
	margin_w = n_G/2;						// Width margin
	H = h + 2*margin_h;						// Height with margin
	W = w + 2*margin_w;						// Width with margin

	// Allocate memory for arrays
	pad_img = create2D<double>(H,W);
	smo_img = create2D<double>(H,W);
	Ln = create2D<double>(H,W);
	Ld = create2D<double>(H,W);
	maxL = create2D<double>(H,W);
	edges = create2D<double>(H,W);

	// Initialize arrays
	init2D(pad_img,H,W);
	init2D(smo_img,H,W);
	init2D(Ln,H,W);
	init2D(Ld,H,W);
	init2D(maxL,H,W);
	init2D(edges,H,W);

	// Import and pad image
	cout << "Transfering/padding matrix..." << endl;
	read2D(pad_img,raw_img_file,raw_img_path,h,w,margin_h,margin_w);

	// Smooth image
	cout << "Smoothing image..." << endl;
	smooth_image(pad_img,smo_img,n_G,std,h,w,margin_h,margin_w,H,W);
	write2D(smo_img,smo_img_file,smo_img_path,h,w,margin_h,margin_w);

	// Compute gradients
	cout << "Computing gradient..." << endl;
	comp_grad(smo_img,Ln,Ld,h,w,margin_h,margin_w,H,W);
	write2D(Ln,grad_file,grad_path,h,w,margin_h,margin_w);

	// Perform non-maximum suppression
	cout << "Perfoming non-maximum suppression..." << endl;
	non_max_supp(Ln,Ld,maxL,h,w,margin_h,margin_w);
	write2D(maxL,thin_grad_file,thin_grad_path,h,w,margin_h,margin_w);

	// Apply two thresholds
	cout << "Labeling weak and strong edges..." << endl;
	two_threshold(maxL,h_thres,l_thres,h,w,margin_h,margin_w);
	write2D(maxL,ws_edges_file,ws_edges_path,h,w,margin_h,margin_w);

	// Hysteresis
	cout << "Refining edges by hysteresis..." << endl;
	hysteresis(maxL,edges,h,w,margin_h,margin_w);
	write2D(edges,edges_file,edges_path,h,w,margin_h,margin_w);

	// Deallocate memory
	delete2D(pad_img,H,W);
	delete2D(smo_img,H,W);
	delete2D(Ln,H,W);
	delete2D(Ld,H,W);
	delete2D(maxL,H,W);
	delete2D(edges,H,W);

	return 0; // End of the program
}
