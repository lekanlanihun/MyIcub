#ifndef RENDER_H
#define RENDER_H

//#include <Qt>
#include <GL/glut.h>
#include <GL/glu.h>
//#if QT_VERSION >= 0x040000
//#endif

#include "../../ROB_SENSORS_OBJS/world_entity.h"
#include "../../ROB_SENSORS_OBJS/simple_objects.h"
#include "../../ROB_SENSORS_OBJS/icub.h"
//#include "../EXP/RENDERING/init_environment.h"
#include "../../MISC/general.h"
#include <FreeImage.h>
//#define object_noise_lower_bound -1.6
//#define object_noise_range 3.2
//#define rotation_lower_bound -20.0
//#define rotation_range 40.0
#define num_images 10

class Experiment;


class Render
{

 protected:
  void copy ( const Render& other);
  void destroy();
  int nWidth; int nHeight;  int counter;
double angle;
string*image_path;
//GLuint tex= 200;
GLuint texture_name [num_images];
//GLuint theSphere;
GLuint thetable;
GLUquadric *quadric;
GLUquadric* quad;
 public:
  Render(/*int eval,*/ std::vector< MyIcub* > m_agents, std::vector< SIMPLE_Objects* > m_objects);
  virtual ~Render();
  
  Render(const Render& other)
    {
      copy(other);
    }
  
  Render& operator=(const Render &other)
    {
      if(this != &other)
        {
	  destroy();
	  copy(other);
        }
      return *this;
    }
 //Environment*environ;
  void initialization ();
 
  void init_lighting();
  void paint          (int eval, double sca, double rota);
  void paintOnlyEnv   (int evals, double scaled, double rot);
void draw_horizontal_lines(void);
void draw_vertical_lines(void);

void create_sphere_displaylist() ;



void draw_environment(void);
void draw_sphere_environment(int evaluate, double scaling,  double orient);
void draw_cube(int eva);
void draw_objects(int evaluation, double sc,double rt);
void draw_table();
void table(double topWid, double topThick, double legThick , double legLen);
void tableLeg(double thick, double len);
void load_texture();
void init_texture();
void init_texture_objects_cats();
void init_sphere();
 void init_draw_sphere(int el, double sa, double ro);
void draw_sphere(int evs, double st, double rc);
void display();
void draw_cube();
  //SKY mySky;
  int evals;
  std::vector< MyIcub* > m_agents;
  std::vector< SIMPLE_Objects* > m_objects;
};

#endif
