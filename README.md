# ROOT Macros

## How to download
>git clone https://github.com/iguanaterrror/Introduction_to_ROOT_2024.git
cd Introduction_to_ROOT_2024

## Prerequiremnts
You must have installed [ROOT Framework](https://root.cern/install/)

## Macros
### WidmoCs
Reading .dat file, creates histogram and plots it. Mark the photopeak and Compton edge for the Cs-137 spectrum.


### WidmoCsBin
Reading .bin file, creates histogram and plots it. Mark the photopeak and Compton edge for the Cs-137 spectrum.

### RewriteFile
Converts .dat file into .bin file

### HistogramStack
Creates stacked plot with four histograms filled with different random distributions (Gaussian, Exponential, Landau, Linear)

## How to run
First you need to start ROOT by typing
>root
then
>.x macroname.C
replace _macroname_ with the name of the macro you want to run

