# /bin/bash

python3 img2mat.py
g++ -o canny_edge_detection canny_edge_detection.cpp
./canny_edge_detection
python3 mat2img.py
