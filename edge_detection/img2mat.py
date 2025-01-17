# Edge detection for CME propagation

# Import packages
from PIL import Image
import numpy as np
import math

# Variable declaration
img_path = "images/raw_img.jpg"                 # Raw image filename
dims_file_path = "matrices/dims.txt"            # Dimensions matrix
mat_file_path = "matrices/raw_img.txt"          # Raw image matrix file
img = Image.open(img_path).convert('L')         # Open image
w, h = img.size                                 # Get width and height of image
mat = img.load()                                # Load matrix like array from image

print("Converting raw image to matrix...")      # Status message

#Output dimensions
dims_file = open(dims_file_path,"w")            # Open file
dims_file.write("%d %d\n" %(h,w))               # Output height and width
dims_file.close()                               # Close file
#Output values
mat_file = open(mat_file_path, "w")             # Open file
for i in range(h):
   for j in range(w):
      mat_file.write("%.15f " %(mat[j,i]/255))  # Output grayscale values from 0 to 1
   mat_file.write("\n") 
mat_file.close()                                # Close file
