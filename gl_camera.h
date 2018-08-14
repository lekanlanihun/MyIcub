#ifndef GL_CAMERA_H
#define GL_CAMERA_H

#include "GL/osmesa.h"
#include "../EXP/RENDERING/render.h"

class GL_Camera : public Render 
{
  
 public:
  GL_Camera(int eval,double scale, double rotate, std::vector< MyIcub* > _m_agents, std::vector< SIMPLE_Objects* > _m_objects, bool display_, int camera_mode, int argc, char** argv);
  GL_Camera(const GL_Camera& other);
  virtual ~GL_Camera();
  GL_Camera& operator=(const GL_Camera &other);
  
  void init( );
  void draw( int r ,int evals , double scale, double rotate);

  unsigned char* getData();
  unsigned char getPixelR(int x, int y);
  unsigned char getPixelG(int x, int y);
  unsigned char getPixelB(int x, int y);
  unsigned char showPixel(int x, int y);
  unsigned char showPixels();
  int get_num_pixels();
int num_retina_pixels;
vector<double>alpha_gamma_lamda;
  void get_readings(double *camera_readings );
void read_pixels( );
double* average_pixels();
  void copy(const GL_Camera& other);

  inline void  set_active_perception                     ( const vector <double> &alp_gam_lam ){
    alpha_gamma_lamda[0]=alp_gam_lam[0];  alpha_gamma_lamda[1]=alp_gam_lam[1];  alpha_gamma_lamda[2]=alp_gam_lam[2];
  }

  inline  vector <double> get_active_perception( void ){ return alpha_gamma_lamda;}


  void destroy();
int evals;

double scales, rotates;
 private:
  void initw();
  unsigned char *pRGB;
  float ratio, depth, minClip, maxClip;
  int width, height;
  int* w;

  bool display;
  OSMesaContext ctx;
  int num_gl_camera_channels;
  int mode;
   
};

#endif
