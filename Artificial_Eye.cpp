/* 
 * File:   Artificial_Eye.cpp
 * Author: oal
 * 
 * Created on 27 January 2014, 18:58
 */


#include "Artificial_Eye.h"


/* -------------------------------------------------------------------- */


Artificial_Eye::Artificial_Eye(int field_of_view){
 hog_feature_size=36;
ulbp_feature_size=236;
retina_side=5;
fovea_side=5;
fovea_lower_limit=30; //(int)(fovea_pixels_length/2);
width= (int)(sqrt(field_of_view));
height=width;
width_range=(int)(width/retina_side);
height_range=(int)(height/retina_side);
total_range=width_range*height_range;
fovea_width_range=(int)(fovea_pixels_length/fovea_side);
fovea_height_range=(int)(fovea_pixels_length/fovea_side);
fovea_total_range=fovea_width_range*fovea_height_range;
retina_size=retina_side*retina_side;
fovea_size=retina_size;
PeripheralArea = Mat::zeros(width, height,CV_8UC1);
 aver=new double [25];
HOG_Feature_Vector=new double [hog_feature_size];
ULBP_Feature_Vector=new double [ulbp_feature_size];
  fovea_aver=new double [25];
 mat_read_pixels=new double *[width];
 for(int i=0;i<width;i++){
      mat_read_pixels[i]=new double[height];
 }

 mat_read_fovea_pixels=new double *[fovea_pixels_length];
 for(int i=0;i<fovea_pixels_length;i++){
      mat_read_fovea_pixels[i]=new double[fovea_pixels_length];
 }
  Vect_HOG_Features=new double*[4];
  for(int i=0;i<4;i++){
    Vect_HOG_Features[i]=new double[9];
  }

  Vect_ULBP_Features=new double*[4];
  for(int i=0;i<4;i++){
    Vect_ULBP_Features[i]=new double[59];
  }

  av=new double *[retina_side];
  for(int i=0;i<retina_side;i++){
    av[i]=new double[retina_side];
  }

  Vect_Mat_fovea=new double*[fovea_side];
  for(int i=0;i<fovea_side;i++){
    Vect_Mat_fovea[i]=new double [fovea_side];
  }

}

/* -------------------------------------------------------------------- */



/* -------------------------------------------------------------------- */

void Artificial_Eye::read_pixels( double *camera_readings){
int k=0;
    for(int i=0;i<width;i++){
   for(int j=0;j<height;j++){
   mat_read_pixels[i][j]=camera_readings[k];    
    k++;
   }
  }

}

double* Artificial_Eye::average_pixels(){    
    int offset_x =0, offset_y = 0, count_x=0, count_y = 0;
    do{

      av[count_x][count_y] = 0.0;
      for(int i=0;i<width_range;i++){
      for(int j=0;j<height_range;j++){
     av[count_x][count_y] += (double) mat_read_pixels[offset_x+i][offset_y+j];   
        }
      }

      av[count_x][count_y] /= (double)(total_range);
av[count_x][count_y]+=(double) (((gsl_rng_uniform_pos( GSL_randon_generator::r_rand ) * retina_noise_range) + retina_noise_lower_bound));
     if(av[count_x][count_y] >1){
              av[count_x][count_y] =1;
      }else if(av[count_x][count_y] <0){
            av[count_x][count_y]=0;
      }
 
      count_x++;
      offset_x += height_range;
      if( offset_x == height){
        offset_y += width_range;
        offset_x = 0;
        count_y++;
        count_x = 0;
      }

    }while( offset_y < width);

int k=0;
    for(int x=0;x<retina_side;x++){
        for(int y=0;y<retina_side;y++){
           aver[k]= av[x][y];
           k++;
        }
    }

    return aver;
}

void Artificial_Eye::read_fovea_pixels(){
for(int i=fovea_lower_limit;i<height-fovea_lower_limit;i++){
for(int j=fovea_lower_limit;j<width-fovea_lower_limit;j++){
 mat_read_fovea_pixels[i-fovea_lower_limit][j-fovea_lower_limit] = mat_read_pixels[i][j];
}
}

}

double* Artificial_Eye::fovea_pixels(){
    int offset_x =0, offset_y = 0, count_x=0, count_y = 0;
    do{
      Vect_Mat_fovea[count_x][count_y] = 0.0;
      for(int i=0;i<fovea_width_range;i++){
      for(int j=0;j<fovea_height_range;j++){
   Vect_Mat_fovea[count_x][count_y] += (double) mat_read_fovea_pixels[offset_x+i][offset_y+j];
         // cout<<"peripheral values="<<" "<<mat_read_pixels[i][j]<<endl;
        }
      }

       Vect_Mat_fovea[count_x][count_y] /= (double)(fovea_total_range);
       
  Vect_Mat_fovea[count_x][count_y]+=(double) (((gsl_rng_uniform_pos( GSL_randon_generator::r_rand ) * retina_noise_range) + retina_noise_lower_bound));
 if(Vect_Mat_fovea[count_x][count_y] >1){
              Vect_Mat_fovea[count_x][count_y] =1;
      }else if(Vect_Mat_fovea[count_x][count_y] <0){
            Vect_Mat_fovea[count_x][count_y]=0;
      }     
 count_x++;
      offset_x += fovea_height_range;
      if( offset_x == fovea_pixels_length){
        offset_y += fovea_width_range;
        offset_x = 0;
        count_y++;
        count_x = 0;
      }

    }while( offset_y < fovea_pixels_length);
int k=0;
    for(int x=0;x<fovea_side;x++){
        for(int y=0;y<fovea_side;y++){
           fovea_aver[k]= Vect_Mat_fovea[x][y];
           k++;
        }
    }

    return fovea_aver;
}


/* -------------------------------------------------------------------- */

 double * Artificial_Eye::Get_HOG_Features(double *camera_readings) {
int k=0;
    for(int i=0;i<width;i++){
   for(int j=0;j<height;j++){
   PeripheralArea.at<uchar>(i,j)=(camera_readings[k]*255);
       //cerr<<" "<<(int)PeripheralArea.at<uchar>(i,j);      
    k++;
   }
  }

Window_Norm();
int c=0;
    for (int i = 0; i <4; i++) {
       for (int j = 0; j <9; j++) {
        HOG_Feature_Vector[c]= Vect_HOG_Features[i][j];
         c++;
       }
  }
   return   HOG_Feature_Vector;
 }



void Artificial_Eye::uniform_Lbp(){
//cout<<"uniform_Lbp_1"<<endl;
               const char lookup[256] = {
               0, 1, 2, 3, 4, 58, 5, 6, 7, 58, 58, 58, 8, 58, 9, 10,
               11, 58, 58, 58, 58, 58, 58, 58, 12, 58, 58, 58, 13, 58, 14, 15,
               16, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58,
               17, 58, 58, 58, 58, 58, 58, 58, 18, 58, 58, 58, 19, 58, 20, 21,
               22, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58,
               58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58,
               23, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58,
               24, 58, 58, 58, 58, 58, 58, 58, 25, 58, 58, 58, 26, 58, 27, 28,
               29, 30, 58, 31, 58, 58, 58, 32, 58, 58, 58, 58, 58, 58, 58, 33,
               58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 34,
               58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58,
               58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 35,
               36, 37, 58, 38, 58, 58, 58, 39, 58, 58, 58, 58, 58, 58, 58, 40,
               58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 41,
               42, 43, 58, 44, 58, 58, 58, 45, 58, 58, 58, 58, 58, 58, 58, 46,
               47, 48, 58, 49, 58, 58, 58, 50, 51, 52, 58, 53, 54, 55, 56, 57
           };

           int lbpbinary;
           int val = 1;
           int counter = 0,off_grid_cell_x = 0, off_grid_cell_y = 0;
           int xoffsets[] = {-1, 0, 1, 1, 1, 0, -1, -1};
           int yoffsets[] = {-1, -1, -1, 0, 1, 1, 1, 0};

           do {

               for(int j=0;j<59;j++){
                Vect_ULBP_Features[counter][j]=0.0;
               }

               for (int offset_cell_x = 1; offset_cell_x < (PeripheralArea.rows / 2)-1; offset_cell_x++) {
                   for (int offset_cell_y = 1; offset_cell_y < (PeripheralArea.cols / 2)-1; offset_cell_y++) {
                       lbpbinary = 0;
                       val = 1;
                       int k  =   PeripheralArea.at<uchar>(offset_cell_x+ off_grid_cell_x, offset_cell_y+ off_grid_cell_y);

                       for (int i = 0; i < 8; i++) {

                           if ( (int) PeripheralArea.at<uchar>(xoffsets[i]+(offset_cell_x + off_grid_cell_x), yoffsets[i]+(offset_cell_y + off_grid_cell_y))>=k) {
                               lbpbinary += val;
                           }
                           val *= 2;

                       }

                      Vect_ULBP_Features[counter][lookup[lbpbinary]]++;
                   }

               }

               off_grid_cell_x += (int)(rint(width/2));
               counter++;
               if (off_grid_cell_x >= PeripheralArea.rows - 2) {
                   off_grid_cell_x = 0;
                   off_grid_cell_y += (int)height/2;
               }
           } while (off_grid_cell_y < PeripheralArea.cols - 1);

}


double *Artificial_Eye::Get_ULBP_Features(double *camera_readings){
int k=0;
    for(int i=0;i<width;i++){
   for(int j=0;j<height;j++){
   PeripheralArea.at<uchar>(i,j)=(camera_readings[k]*255);      
    k++;
   }
  }
GaussianBlur(PeripheralArea, PeripheralArea, Size(3, 3), 0, 0, BORDER_DEFAULT);
    uniform_Lbp();
      for(int i=0;i<4;i++){
          //double total = 0;
          double norm_var = 0.0;
          for(int j=0;j<59;j++){
               norm_var+=((Vect_ULBP_Features[i][j])*(Vect_ULBP_Features[i][j]));
          }
               norm_var=sqrt(norm_var);
          for(int j=0;j<59;j++){
             // Vect_Mat_peripheral[i][j]/=total;
            Vect_ULBP_Features[i][j]= (double)(Vect_ULBP_Features[i][j]/norm_var);  //l2 norm
          }

      }

   int c=0;
    for (int i = 0; i <4; i++) {
       for (int j = 0; j <59; j++) {
        ULBP_Feature_Vector[c]= Vect_ULBP_Features[i][j];
         c++;
       }
  }

return ULBP_Feature_Vector;

}

void  Artificial_Eye::HOG_Trucating_Version(){
  int ddepth=CV_32F;
 int scale = 1;
 Scharr(PeripheralArea, grad_y, ddepth, 0, 1, scale, BORDER_DEFAULT );
 Scharr(PeripheralArea, grad_x, ddepth, 1, 0, scale, BORDER_DEFAULT );
   double gradient_direction_radians=0.0, magnitude=0.0;
   double gradient_direction_degrees=0.0;
   int off_set_y = 0, off_set_x = 0,count = 0,hog_bin=0 ;
    do{
       for(int j=0;j<9;j++){
         Vect_HOG_Features[count][j]=0.0;
       }
    for (int row_y1 = 0, row_y2 = 0; row_y1 < grad_y.rows/2, row_y2 < grad_x.rows/2; row_y1++, row_y2++) {
          for (int col_x1 = 0, col_x2 = 0; col_x1 < grad_y.cols/2, col_x2 < grad_x.cols/2; col_x1++, col_x2++) {

              double dx = grad_x.at<float>((row_y2 + off_set_y), (col_x2 + off_set_x));
              double dy = grad_y.at<float>((row_y1 + off_set_y), (col_x1 + off_set_x));
              magnitude = (double)sqrt(dx*dx+dy*dy);
              gradient_direction_radians = (double) atan2(dy, dx);
             gradient_direction_degrees =  (double)(( (gradient_direction_radians / M_PI) * 180.0)+(gradient_direction_radians> 0 ? 0 : 360.0));
                 hog_bin = (int)(gradient_direction_degrees/40);
              hog_bin %= 9;
           Vect_HOG_Features[count][hog_bin] += magnitude;
          }
    }

    off_set_y += (int)height/2;
    count++;
    if (off_set_y == height) {
        off_set_y = 0;
        off_set_x += (int)width/2;
    }

    }while(off_set_x <width);

}


void Artificial_Eye::Window_Norm() {
     HOG_Trucating_Version();
 double Norm_Var=0.0;
         for(int i=0;i<retina_processed_rows;i++){
                 for(int j=0;j<retina_processed_cols;j++){
                     Norm_Var+=(( Vect_HOG_Features[i][j])*( Vect_HOG_Features[i][j]));
                 }
         }
 Norm_Var= sqrt(Norm_Var);
       for(int i=0;i<retina_processed_rows;i++){
             for(int j=0;j<retina_processed_cols;j++){
                      Vect_HOG_Features[i][j]=(double)( Vect_HOG_Features[i][j]/Norm_Var);
             }
         }
}


Artificial_Eye::~Artificial_Eye() {
 // cout << "Deallocating artifical eye"<<endl;
    delete[] HOG_Feature_Vector;
    delete[] ULBP_Feature_Vector;
 delete [] aver; 
 delete [] fovea_aver;
     
      for(int i=0;i<width;i++){
           delete mat_read_pixels[i];
      }
      delete [] mat_read_pixels;

     for(int i=0;i<fovea_pixels_length;i++){
           delete mat_read_fovea_pixels[i];
      }
      delete [] mat_read_fovea_pixels;

    for(int i=0;i<fovea_side;i++){
        delete [] Vect_Mat_fovea [i];
    }
    delete [] Vect_Mat_fovea;

  for(int i=0;i<retina_side;i++){
       delete [] av[i];
    }
    delete [] av;

  for(int i=0;i<4;i++){
       delete []Vect_HOG_Features[i];
    }
    delete []  Vect_HOG_Features;

 for(int i=0;i<4;i++){
       delete []Vect_ULBP_Features[i];
    }
    delete []  Vect_ULBP_Features;

}

