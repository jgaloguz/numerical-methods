Canny Edge Detection Algorithm: detects the (grayscale) edges for given image using the following procedure,
	- smooth raw image using Gaussian filter,
	- compute brightness/intensity gradient (magnitude and direction) using the Sobel kernel,
	- perform non-maximal gradient suppression,
	- apply two-threshold standard to label weak and strong edges (while suppressing very weak edges),
	- track weak edges that connect to strong edges by hysteresis (while suppressing isolated weak edges).

edge_detection.sh: bash file used to compile and execute all the relevant programs in the appropriate order.

img2mat.py input(s):
	- raw_img.jpg file (placed within images directory).

img2mat.py output(s):
	- dims.txt file containing the raw image dimensions in height-width format (placed within matrices directory).
	- raw_img.txt file containing the brightness of each pixel in the raw image (grayscale version), scaled from 0 to 1, in the standard row-column format.

canny_edge_detection.cpp input(s):
	- dims.txt file (output from img2mat.py).
	- raw_img.txt file (output from img2mat.py).
	- size of Gaussian filter, n_G (hard-coded).
	- spread of Gaussian filter, std (hard-coded).
	- low and high thresholds, l_thres, h_thres (hard-coded).

canny_edge_detection.cpp output(s):
	- smo_img.txt file (placed within the matrices directory) contaning the brightness of each pixel in the smoothed image (grayscale version), scaled from 0 to 1, in the standard row-column format.
	- grad.txt file (placed within the matrices directory) containing the estimated gradient magnitude at each pixel in the grayscale smoothed image, in the standard row-column format.
	- thin_grad.txt file (placed within the matrices directory) containing same information as in the grad.txt file but only retaining the local gradient maxima in the gradient direction at each pixel.
	- ws_edges.txt file (placed within the matrices directory) containing a categorization of each pixel as very weak (value 0), weak (value 0.5), or strong (value 1), in the standard row-column format.
	- edges.txt file (placed within the matrices directory) containing a categorization of each pixel as a detected edge (value 1), or not-edge (value 0), in the standard row-column format.

mat2img.py input(s):
	- dims.txt file (output from img2mat.py).
	- smo_img.txt file (output from canny_edge_detection.cpp).
	- grad.txt file (output from canny_edge_detection.cpp).
	- thin_grad.txt file (output from canny_edge_detection.cpp).
	- ws_edges.txt file (output from canny_edge_detection.cpp).
	- edges.txt file (output from canny_edge_detection.cpp).

mat2img.py output(s):
	- smo_img.jpg file (placed in the images directory).
	- grad.jpg file (placed in the images directory).
	- thin_grad.jpg file (placed in the images directory).
	- ws_edges.jpg file (placed in the images directory).
	- edges.jpg file (placed in the images directory).
