#!/bin/bash

magick chain_parameter_1.png chain_parameter_2.png +append top.png
magick posterior_parameter_2.png -rotate 270 posterior_parameter_2_rot.png
magick 2D_hist.png posterior_parameter_2_rot.png +append med.png
magick posterior_parameter_1.png sample_fits.png +append bot.png
magick top.png med.png bot.png -append data_fit.png

rm chain_parameter_1.png chain_parameter_2.png posterior_parameter_1.png posterior_parameter_2.png \
   posterior_parameter_2_rot.png 2D_hist.png sample_fits.png top.png med.png bot.png