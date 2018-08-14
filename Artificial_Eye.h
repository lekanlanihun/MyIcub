/* 
 * File:   Artificial_Eye.h
 * Author: oal
 *
 * Created on 27 January 2014, 18:58
 */

#ifndef ARTIFICIAL_EYE_H
#define	ARTIFICIAL_EYE_H
#include </usr/include/opencv2/core/core.hpp>
#include </usr/include/opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include </usr/include/opencv/cv.h>
#include </usr/include/opencv/highgui.h>
#include "/usr/include/opencv2/imgproc/imgproc.hpp"
#include <vector>
#include "../MISC/general.h"
#define retina_noise_upper_bound  0.1
#define retina_noise_lower_bound -0.05
#define retina_noise_range 0.1 
#define retina_processed_rows 4
#define retina_processed_cols 9

#define fovea_pixels_length 40
//#define angle_range 12
//#define angle_lbound -6
//#define ImageLength_range 16
//#define ImageLength_lbound -8
//#define ImageWidth_range 20
//#define ImageWidth_lbound -10
//#define histogram_noise_upper_bound  0.1
//#define histogram_noise_lower_bound  0.001
//#define histogram_noise_range 0.999
//#define EPSILON 0.0001
//#include <random>
using namespace cv;
using namespace std;
//static int segmented_loc_x1=97,segmented_loc_x2=180,segmented_loc_y1=120,segmented_loc_y2=250;
//static int histogram_rows=4;
//static int histogram_cols=59;
 
class Artificial_Eye {
 public:
 
Artificial_Eye ( int /*,int,int,int*/);
 int  peripheral_size, fovea_size,total_range;
int retina_size,  hog_feature_size, ulbp_feature_size;

  //double **Get_Fovea();
  
  void uniform_Lbp(void);

void HOG_Trucating_Version();
double * Get_HOG_Features(double *camera_readings);
double * Get_ULBP_Features(double *camera_readings);
double* average_pixels();
double* fovea_pixels();
void read_pixels( double *camera_readings);
void read_fovea_pixels(void);
void Window_Norm();

  
  virtual ~Artificial_Eye();
  
 private:
int  width,height, width_range,height_range, retina_side;
int fovea_total_range,fovea_width_range,fovea_height_range, fovea_side;
  Mat PeripheralArea;
Mat grad_x;
Mat grad_y;
double * HOG_Feature_Vector;
double * ULBP_Feature_Vector;
double**mat_read_pixels;
double**mat_read_fovea_pixels;
int fovea_lower_limit;
  double** Vect_Mat_fovea;
 double ** av;
double * aver;
double * fovea_aver;
//double ** Hog_average;
//double ** Hog_max;
double **  Vect_HOG_Features;
double **  Vect_ULBP_Features;



};

#endif	/* ARTIFICIAL_EYE_H */

