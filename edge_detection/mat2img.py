# Edge detection for CME propagation

# Import packages
from PIL import Image
import numpy as np
import math

def mat2img(mat_path, img_path, h, w):
	mat = np.zeros((h,w))
	mat_file = open(mat_path, "r")				# Open file
	for i in range(h):
		row = mat_file.readline()
		row = row.split()
		for j in range(w):
			mat[i,j] = row[j]			# Get values
	mat_file.close()					# Close file

	scale = np.max(mat)					# Find scale
	mat = mat*255/scale					# Scale value

	img = Image.fromarray(mat).convert('L')			# Generate image
	img.save(img_path)					# Save to file

# Variable declaration
smo_img_path = "images/smo_img.jpg"				# Smoothed image filename
grad_img_path = "images/grad.jpg"				# Gradient image filename
thin_grad_img_path = "images/thin_grad.jpg"			# Thinned gradient image filename
ws_edges_img_path = "images/ws_edges.jpg"			# Weak/Strong edges image filename
edges_img_path = "images/edges.jpg"				# Edges image filename

dims_file_path = "matrices/dims.txt"				# Dimensions matrix file
smo_mat_file_path = "matrices/smo_img.txt"			# Smoothed image matrix file
grad_mat_file_path = "matrices/grad.txt"			# Gradient matrix file
thin_grad_mat_file_path = "matrices/thin_grad.txt"		# Thinned gradient matrix file
ws_edges_math_file_path = "matrices/ws_edges.txt"		# Weak/Strong edges matrix file
edges_math_file_path = "matrices/edges.txt"			# Edges matrix file

print("Converting processed matrices to images...")		# Status message

#Output dimensions
dims_file = open(dims_file_path,"r")				# Open file
# Read dimensions
dims = dims_file.readline()
dims = dims.split()
h = int(dims[0])						# Height
w = int(dims[1])						# Width
dims_file.close()						# Close file

#Convert smooth image
mat2img(smo_mat_file_path, smo_img_path, h, w)
#Convert gradient
mat2img(grad_mat_file_path, grad_img_path, h, w)
#Convert thinned gradient
mat2img(thin_grad_mat_file_path, thin_grad_img_path, h, w)
#Convert weak/strong edges
mat2img(ws_edges_math_file_path, ws_edges_img_path, h, w);
#Convert edges
mat2img(edges_math_file_path, edges_img_path, h, w);
