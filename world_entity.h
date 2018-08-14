#ifndef _WORLD_ENTITY_
#define _WORLD_ENTITY_

#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "../MISC/general.h"
#include "../MISC/AlgoMatrix.h"

//#ifdef _GRAPHICS_
#include <GL/glut.h>
//#endif

#define PI     3.141592654
#define TWO_PI 6.283185307
#define ONE_PI 0.017453293

#define DIST_OFFSET_SECURITY 0.1

using namespace std;

static const int NOISE_LEVEL = 1.0;

class World_Entity 
{
  
 protected:
  vector <double> colour;
  
 public:
  World_Entity(){}
  World_Entity(const World_Entity& other)
    {
      colour = other.colour;
    }
  virtual ~World_Entity(){};
  
  virtual void  set_pos                     ( const int which_joint, const vector <double> &_pos ) = 0;
  virtual void  set_rot                     ( const int which_joint, const vector <double> &_rot ) = 0;
  virtual const vector <double> get_pos     ( const int which_joint ) = 0;
  virtual const vector <double> get_tmp_pos ( const int which_joint ) = 0;
  virtual const vector <double> get_dim     ( const int which_joint ) = 0;
  virtual const vector <double> get_colour  ( const int which_joint ) = 0;
  virtual const vector <double> get_rot     ( const int which_joint ) = 0;
  virtual const double          get_safe_dist ( void ) = 0;
  
  /* ------------------------------------------------------------ */
  inline void set_colour( const vector <double> &c ) {
    colour[0] = c[0];
    colour[1] = c[1];
    colour[2] = c[2];
  }
  /* ------------------------------------------------------------ */
  
};

#endif

