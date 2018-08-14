#ifndef _SIMPLE_OBJECTS_
#define _SIMPLE_OBJECTS_

#include "world_entity.h"

using namespace std;

class SIMPLE_Objects : public World_Entity
{

protected:
  bool visible;
  vector <double> pos;
  vector <double> rot;
  vector <double> dim;
  double safe_dist;

  int type_id;
  static const int robot_slices    = 20;

  void copy(const SIMPLE_Objects &other);
  void destroy();

private:

public:
    SIMPLE_Objects( );
    SIMPLE_Objects(const SIMPLE_Objects& other);
    virtual ~SIMPLE_Objects();
    
    inline bool is_visible                   ( void )      { return visible; }
    inline void set_visible                  ( bool flag ) {
      visible = flag;
    }
    
    inline void set_pos ( const int which_joint, const vector <double> &_pos ){
        pos[0] = _pos[0];
        pos[1] = _pos[1];
        pos[2] = _pos[2];
    }
    inline void set_rot ( const int which_joint, const vector <double> &_rot ){
        rot[0] = _rot[0];
        rot[1] = _rot[1];
        rot[2] = _rot[2];
    }
      inline void set_dim ( const int which_joint, const vector <double> &_dim ){
        dim[0] = _dim[0];
        dim[1] = _dim [1];
        dim[2] = _dim [2];
    }
    
    inline const vector <double> get_pos     ( const int which_joint ){ return pos;}
    inline const vector <double> get_tmp_pos ( const int which_joint ){ return pos;}
    inline const vector <double> get_rot     ( const int which_joint ){ return rot;}
    inline const vector <double> get_dim     ( const int which_joint ){ return dim;}
    inline const vector <double> get_colour  ( const int which_joint ){ return colour;}
    inline const int             get_type_id ( void ){ return type_id;}
    inline const double          get_safe_dist ( void ) {return safe_dist;}
    
    SIMPLE_Objects& operator=(const SIMPLE_Objects &other);

    //#ifdef _GRAPHICS_
    virtual void    render                   ( void ) = 0;
    //#endif

};

/* ------------------------------------------------------------ */

class SIMPLE_Brick : public SIMPLE_Objects
{

private:
    void copy(const SIMPLE_Brick &other);
    void destroy();

public:
    SIMPLE_Brick( double *data );
    SIMPLE_Brick( const SIMPLE_Brick& other );
    virtual ~SIMPLE_Brick();

    SIMPLE_Brick& operator=(const SIMPLE_Brick &other);
    //#ifdef _GRAPHICS_
    void    render                   ( void );
    //#endif
};

/* ------------------------------------------------------------ */

class SIMPLE_Cylinder : public SIMPLE_Objects
{
private:
    void copy(const SIMPLE_Cylinder &other);
    void destroy();

public:
    SIMPLE_Cylinder( double *data );
    SIMPLE_Cylinder( const SIMPLE_Cylinder& other );
    virtual ~SIMPLE_Cylinder();

    SIMPLE_Cylinder& operator=(const SIMPLE_Cylinder &other);
    //#ifdef _GRAPHICS_
    void    render                   ( void );
    //#endif
};

/* ------------------------------------------------------------ */

class SIMPLE_Sphere : public SIMPLE_Objects
{
private:
    void copy(const SIMPLE_Sphere &other);
    void destroy();

public:
    SIMPLE_Sphere( double *data );
    SIMPLE_Sphere( const SIMPLE_Sphere& other );
    virtual ~SIMPLE_Sphere();

    SIMPLE_Sphere& operator=(const SIMPLE_Sphere &other);
    //#ifdef _GRAPHICS_
    void    render                     ( void );
    //#endif
};

/* ------------------------------------------------------------ */

class SIMPLE_Light : public SIMPLE_Objects
{
private:
    void copy(const SIMPLE_Light &other);
    void destroy();

public:
    SIMPLE_Light( double *data );
    SIMPLE_Light( const SIMPLE_Light& other );
    virtual ~SIMPLE_Light();

    SIMPLE_Light& operator=(const SIMPLE_Light &other);
    //#ifdef _GRAPHICS_
    void    render                     ( void );
    //#endif
};

/* ------------------------------------------------------------ */

#endif
