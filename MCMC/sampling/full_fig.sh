#!/bin/bash

magick posterior_parameter_2.png -rotate 270 posterior_parameter_2_rot.png
magick 2D_hist.png posterior_parameter_2_rot.png +append top.png
magick posterior_parameter_1.png chain_parameters.png +append bot.png
magick top.png bot.png -append samples.png

rm chain_parameters.png posterior_parameter_1.png posterior_parameter_2.png \
   posterior_parameter_2_rot.png 2D_hist.png top.png bot.png