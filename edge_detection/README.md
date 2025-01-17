**Canny Edge Detection**

Detecting (grayscale) edges for given image using the following procedure,
	- smooth raw image using Gaussian filter,
	- compute brightness/intensity gradient (magnitude and direction) using the Sobel kernel,
	- perform non-maximal gradient suppression,
	- apply two-threshold standard to label weak and strong edges (while suppressing very weak edges),
	- track weak edges that connect to strong edges by hysteresis (while suppressing isolated weak edges).

`edge_detection.sh`: bash file used to compile and execute all the relevant programs in the appropriate order.

img2mat.py input(s):
	- `images/raw_img.jpg` file.

img2mat.py output(s):
	- `matrices/dims.txt` file containing the raw image dimensions in height-width format.
	- `matrices/raw_img.txt` file containing the brightness of each pixel in the raw image (grayscale version), scaled from 0 to 1, in the standard row-column format.

canny_edge_detection.cpp input(s):
	- `matrices/dims.txt` file (output from img2mat.py).
	- `matrices/raw_img.txt` file (output from img2mat.py).
	- size of Gaussian filter, `n_G` (hard-coded).
	- spread of Gaussian filter, `std` (hard-coded).
	- low and high thresholds, `l_thres`, `h_thres` (hard-coded).

canny_edge_detection.cpp output(s):
	- `matrices/smo_img.txt` file contaning the brightness of each pixel in the smoothed image (grayscale version), scaled from 0 to 1, in the standard row-column format.
	- `matrices/grad.txt` file containing the estimated gradient magnitude at each pixel in the grayscale smoothed image, in the standard row-column format.
	- `matrices/thin_grad.txt` file containing same information as in the grad.txt file but only retaining the local gradient maxima in the gradient direction at each pixel.
	- `matrices/ws_edges.txt` file containing a categorization of each pixel as very weak (value 0), weak (value 0.5), or strong (value 1), in the standard row-column format.
	- `matrices/edges.txt` file containing a categorization of each pixel as a detected edge (value 1), or not-edge (value 0), in the standard row-column format.

mat2img.py input(s):
	- `matrices/dims.txt` file (output from img2mat.py).
	- `matrices/smo_img.txt` file (output from canny_edge_detection.cpp).
	- `matrices/grad.txt` file (output from canny_edge_detection.cpp).
	- `matrices/thin_grad.txt` file (output from canny_edge_detection.cpp).
	- `matrices/ws_edges.txt` file (output from canny_edge_detection.cpp).
	- `matrices/edges.txt` file (output from canny_edge_detection.cpp).

mat2img.py output(s):
	- `matrices/smo_img.jpg` file.
	- `matrices/grad.jpg file`.
	- `matrices/thin_grad.jpg` file.
	- `matrices/ws_edges.jpg` file.
	- `matrices/edges.jpg` file.
