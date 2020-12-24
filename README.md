# Image Vectorization through Energy Optimization


This project implements the research paper :

*Effective Clipart Image Vectorization Through Direct Optimization of Bezigons*

## Introduction

Image vectorisation is a crucial subject for many graphic designers who often have to transform a pixelated image into a vector image. 

The implemented algorithm uses "bezigons", i.e. a closed path made up of Bezier curves, to represent the contours of vector shapes.

![](./data_readme/heart_vectorisation.png)
*Vectorization of a heart clipart using the implemented algorithm*

## Steps
To implement the paper, we proceed according to the following steps:
1. Find a first correct approximation of the image and initialise the bezigons to be optimised.
2. Optimise each of the fragments $P_j$ of bezigon $B$ according to the equation :
   
    $Pj_{*}= argmin_{Pj} [E_{data}(P_j,B) +E_{prior}(P_j,B)]$

with :
* $E_{data}$ the energy which represents the difference between the original image and the image obtained by rasterizing the bezigon. A major challenge is therefore to find a rasterization function that allows the parameters to be optimised. The function used in the paper uses a discrete wavelet decomposition which gives a differentiable $E_{data}$.

* $E_{prior}$ the energy designed according to pre-established criteria and penalizing bezigons with certain aspects. It can be broken down into 4 energies: 
   - $E_{spt}$ penalises bezigons that are self-intersecting
   -  $E_{apt}$ penalises small variations in angle, - $E_{hpt}$ penalises handles that are too close to the knots, 
   -  $E_{lpt}$ penalises twisted curves that add length to the bezigon. 




## Quick Start


* In a terminal, cd in the "Image_Vectorization" folder
* Clone libigl : 
```js
git clone --recursive https://github.com/libigl/libigl.git
```
* Build the project : 
```js
mkdir build && cd build/
cmake .. && make
```

* Lauch the executable : 
```js
./image_vect 
```
* An image appears (change it in main.cpp) 
* CLICK on several points ![](./data_readme/init.png)
* END by pressing 0
* WAIT : The bezier curve will be drawn as well as the rasterized image, and the results will be saved in a svg format.






