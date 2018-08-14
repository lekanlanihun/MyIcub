#include "simple_objects.h"

/* ------------------------------------------------------------ */

SIMPLE_Objects::SIMPLE_Objects( void ) : World_Entity ( )
{
    rot.assign    (3, 0.0);
    dim.assign    (3, 0.0);
    colour.assign (3, 0.0);
    visible       = true;
    safe_dist     = 0.0;
}

SIMPLE_Objects::SIMPLE_Objects(const SIMPLE_Objects& other)
    : World_Entity(other)
{
    copy(other);
}

SIMPLE_Objects::~SIMPLE_Objects()
{
    destroy();
}

/* ------------------------------------------------------------ */

void SIMPLE_Objects::copy(const SIMPLE_Objects &other)
{
    visible = other.visible;
    pos = other.pos;
    rot = other.rot;
    dim = other.dim;
    type_id = other.type_id;
    safe_dist = other.safe_dist;
}

/* ------------------------------------------------------------ */

void SIMPLE_Objects::destroy()
{
    pos.clear();
    rot.clear();
    dim.clear();
}

/* ------------------------------------------------------------ */

SIMPLE_Objects& SIMPLE_Objects::operator=(const SIMPLE_Objects &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

/* ------------------------------------------------------------ */
/* ------------------------------------------------------------ */

/* ------------------------------------------------------------- */
/* BRICK   BRICK   BRICK   BRICK   BRICK   BRICK   BRICK   BRICK */
/* ------------------------------------------------------------- */

SIMPLE_Brick::SIMPLE_Brick( double *data )
    : SIMPLE_Objects( )
{
    pos.assign    (9, 0.0);
    pos[0] = data[0];//X position
    pos[1] = data[1];//Y position
    pos[2] = data[2];//Z position

    dim[0] = data[3]; //Length on the X axis
    dim[1] = data[4]; //Width on the Y axis
    dim[2] = data[5]; //Height on the Z axis
    safe_dist = dim[0] + DIST_OFFSET_SECURITY;

    rot[2] = data[6]; //Rotation on the XY plain

    double angle = (rot[2]*PI)/180.0;

    pos[3] = pos[0] + ((dim[0]*0.5 * cos(angle)));
    pos[4] = pos[1] + ((dim[0]*0.5 * sin(angle)));
    pos[5] = pos[2];

    pos[6] = pos[0] + (-(dim[0]*0.5 * cos(angle)));
    pos[7] = pos[1] + (-(dim[0]*0.5 * sin(angle)));
    pos[8] = pos[2];

    colour[0] = data[7]; //RED
    colour[1] = data[8]; //GREEN
    colour[2] = data[9]; //BLUE

    type_id  = 4;
}

/* ------------------------------------------------------------ */

SIMPLE_Brick::SIMPLE_Brick( const SIMPLE_Brick& other ) 
	: SIMPLE_Objects (other)
{
}

/* ------------------------------------------------------------ */

SIMPLE_Brick::~SIMPLE_Brick()
{
    destroy();
}

/* ------------------------------------------------------------ */

void SIMPLE_Brick::copy(const SIMPLE_Brick &other)
{
}

/* ------------------------------------------------------------ */

void SIMPLE_Brick::destroy()
{
}

/* ------------------------------------------------------------ */

SIMPLE_Brick& SIMPLE_Brick::operator=(const SIMPLE_Brick &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

/* ------------------------------------------------------------ */

//#ifdef _GRAPHICS_
void SIMPLE_Brick::render ( void ){
  glColor3f(colour[0], colour[1], colour[2]);
    float m[16];
    m[ 0] = 1.0;
    m[ 1] = 0.0;
    m[ 2] = 0.0;
    m[ 3] = 0;
    m[ 4] = 0.0;
    m[ 5] = 1.0;
    m[ 6] = 0.0;
    m[ 7] = 0;
    m[ 8] = 0.0;
    m[ 9] = 0.0;
    m[10] = 1.0;
    m[11] = 0;
    m[12] = pos[0];
    m[13] = pos[1];
    m[14] = pos[2];
    m[15] = 1;
    glPushMatrix();
    glMultMatrixf(m);
    glRotatef(rot[2], 0, 0, 1);
    glScalef(dim[0],dim[1],dim[2]);
    glutSolidCube(1.0f);
    glPopMatrix();
}
//#endif
/* ------------------------------------------------------------ */
/* CYLINDER    CYLINDER    CYLINDER    CYLINDER    CYLINDER     */
/* ------------------------------------------------------------ */

SIMPLE_Cylinder::SIMPLE_Cylinder( double *data ) : SIMPLE_Objects(  )
{
    pos.assign    (3, 0.0);
    pos[0] = data[0];
    pos[1] = data[1];
    pos[2] = data[2];

    dim[0] = data[4]; //width = dim[0] = radius
    dim[1] = data[5]; //height = dim[1] = height
    dim[2] = data[3];
    safe_dist = dim[0] + DIST_OFFSET_SECURITY;

    rot[2] = data[6];

    colour[0] = data[7];
    colour[1] = data[8];
    colour[2] = data[9];

    type_id  = 1;
}

/* ------------------------------------------------------------ */

SIMPLE_Cylinder::SIMPLE_Cylinder( const SIMPLE_Cylinder& other )
    : SIMPLE_Objects (other)
{
}

/* ------------------------------------------------------------ */

SIMPLE_Cylinder::~SIMPLE_Cylinder()
{
    destroy();
}

/* ------------------------------------------------------------ */

void SIMPLE_Cylinder::copy(const SIMPLE_Cylinder &other)
{
}

/* ------------------------------------------------------------ */

void SIMPLE_Cylinder::destroy()
{
}

/* ------------------------------------------------------------ */

SIMPLE_Cylinder& SIMPLE_Cylinder::operator=(const SIMPLE_Cylinder &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

/* ------------------------------------------------------------ */

//#ifdef _GRAPHICS_
void SIMPLE_Cylinder::render ( void ){
    glColor3f(colour[0], colour[1], colour[2]);
    /*float m[16];
  m[ 0] = 1.0;
  m[ 1] = 0.0;
  m[ 2] = 0.0;
  m[ 3] = 0;
  m[ 4] = 0.0;
  m[ 5] = 1.0;
  m[ 6] = 0.0;
  m[ 7] = 0;
  m[ 8] = 0.0;
  m[ 9] = 0.0;
  m[10] = 1.0;
  m[11] = 0;
  m[12] = pos[0];
  m[13] = pos[1];
  m[14] = pos[2];
  m[15] = 1;*/

    glPushMatrix();
    //glMultMatrixf(m);
    glTranslatef(pos[0], pos[1], pos[2]);
    GLUquadric* params_quadric = gluNewQuadric();
    glColor3f(colour[0], colour[1], colour[2] );
    gluCylinder(params_quadric, dim[0], dim[0], dim[1], robot_slices, 1);
    gluDisk(params_quadric, 0, dim[0], robot_slices, 1);
    glTranslated(0,0,dim[1]);
    gluDisk(params_quadric, 0, dim[0], robot_slices, 1);
    gluDeleteQuadric(params_quadric);
    /*glBegin(GL_TRIANGLES);
  for (int i = 0; i<100; i++)
    {
      float n = i*(M_PI/50);
      //glColor3f((n/2),1-(n/2),sin(n));
      glVertex3f((dim[0]*sin(n)),(dim[0]*cos(n)), 0);
      n = (1+i)*(M_PI/50);
      glVertex3f((dim[0]*sin(n)),(dim[0]*cos(n)), 0);
      glVertex3f(0, 0, 0);
    }
  glEnd();
  GLUquadric* quad = gluNewQuadric();
  gluCylinder( quad, dim[0], dim[0], dim[1], 30, 30 );
  gluDeleteQuadric( quad );
  glTranslatef( 0, 0, dim[1] );
  glBegin(GL_TRIANGLES);
  for (int i = 0; i<100; i++)
    {
      float n = i*(M_PI/50);
      //glColor3f((n/2),1-(n/2),sin(n));
      glVertex3f((dim[0]*sin(n)),(dim[0]*cos(n)), 0);
      n = (1+i)*(M_PI/50);
      glVertex3f((dim[0]*sin(n)),(dim[0]*cos(n)), 0);
      glVertex3f(0, 0, 0);
    }
  glEnd();*/
    glPopMatrix();
}
//#endif

/* ------------------------------------------------------------ */
/* SPHERE    SPHERE    SPHERE    SPHERE    SPHERE     SPHERE    */
/* ------------------------------------------------------------ */

SIMPLE_Sphere::SIMPLE_Sphere( double *data ) : SIMPLE_Objects( ) 
{
    pos.assign    (3, 0.0);
    pos[0] = data[0];
    pos[1] = data[1];
    pos[2] = data[2];

    dim[0] = data[3];
    dim[1] = data[4];
    dim[2] = data[5];
    safe_dist = dim[0] + DIST_OFFSET_SECURITY;

    rot[2] = data[6];

    colour[0] = data[7];
    colour[1] = data[8];
    colour[2] = data[9];

    type_id  = 2;
}

SIMPLE_Sphere::SIMPLE_Sphere( const SIMPLE_Sphere& other )
    : SIMPLE_Objects (other)
{
}

/* ------------------------------------------------------------ */

SIMPLE_Sphere::~SIMPLE_Sphere()
{
    destroy();
}

/* ------------------------------------------------------------ */

void SIMPLE_Sphere::copy(const SIMPLE_Sphere &other)
{
}

/* ------------------------------------------------------------ */

void SIMPLE_Sphere::destroy()
{
}

/* ------------------------------------------------------------ */

SIMPLE_Sphere& SIMPLE_Sphere::operator=(const SIMPLE_Sphere &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

/* ------------------------------------------------------------ */

//#ifdef _GRAPHICS_
void SIMPLE_Sphere::render ( void ){
    float m[16];
    m[ 0] = 1.0;
    m[ 1] = 0.0;
    m[ 2] = 0.0;
    m[ 3] = 0;
    m[ 4] = 0.0;
    m[ 5] = 1.0;
    m[ 6] = 0.0;
    m[ 7] = 0;
    m[ 8] = 0.0;
    m[ 9] = 0.0;
    m[10] = 1.0;
    m[11] = 0;
    m[12] = pos[0];
    m[13] = pos[1];
    m[14] = pos[2];
    m[15] = 1;

    glColor3f(colour[0], colour[1], colour[2]);
    glPushMatrix();
    glMultMatrixf(m);
    glutSolidSphere(dim[0],100,100);
    glPopMatrix();
}
//#endif
/* ------------------------------------------------------------ */

/* ------------------------------------------------------------ */
/*    LIGHT    LIGHT    LIGHT    LIGHT    LIGHT     LIGHT       */
/* ------------------------------------------------------------ */

SIMPLE_Light::SIMPLE_Light( double *data ) : SIMPLE_Objects( ) 
{
    pos.assign    (3, 0.0);
    pos[0] = data[0];
    pos[1] = data[1];
    pos[2] = data[2];

    dim[0] = data[3];
    dim[1] = data[4];
    dim[2] = data[5];
    safe_dist = dim[0] + DIST_OFFSET_SECURITY;

    rot[2] = data[6];

    colour[0] = data[7];
    colour[1] = data[8];
    colour[2] = data[9];

    type_id  = 3;
}

SIMPLE_Light::SIMPLE_Light( const SIMPLE_Light& other )
    : SIMPLE_Objects (other)
{
}

/* ------------------------------------------------------------ */

SIMPLE_Light::~SIMPLE_Light()
{
    destroy();
}

/* ------------------------------------------------------------ */

void SIMPLE_Light::copy(const SIMPLE_Light &other)
{
}

/* ------------------------------------------------------------ */

void SIMPLE_Light::destroy()
{
}

/* ------------------------------------------------------------ */

SIMPLE_Light& SIMPLE_Light::operator=(const SIMPLE_Light &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

/* ------------------------------------------------------------ */

//#ifdef _GRAPHICS_
void SIMPLE_Light::render ( void ){
    float m[16];
    m[ 0] = 1.0;
    m[ 1] = 0.0;
    m[ 2] = 0.0;
    m[ 3] = 0;
    m[ 4] = 0.0;
    m[ 5] = 1.0;
    m[ 6] = 0.0;
    m[ 7] = 0;
    m[ 8] = 0.0;
    m[ 9] = 0.0;
    m[10] = 1.0;
    m[11] = 0;
    m[12] = pos[0];
    m[13] = pos[1];
    m[14] = pos[2];
    m[15] = 1;

    if( visible ){
      glColor3f(colour[0], colour[1], colour[2]);
      //glColor3f(0.1, 0.1, 0.1);
    }
    else{
      glColor3f(0, 0, 0);
    }
    glPushMatrix();
    glMultMatrixf(m);
    glutSolidSphere(dim[0],100,100);
    glPopMatrix();
}
//#endif

/* ------------------------------------------------------------ */
/* ------------------------------------------------------------ */
