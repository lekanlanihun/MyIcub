#include "render.h"

using namespace std;

Render::Render(/*int eval,*/std::vector< MyIcub* > _m_agents, std::vector< SIMPLE_Objects* > _m_objects )
{
  m_agents  = _m_agents;
  m_objects = _m_objects;
  //evals=eval;
//cout<<"eval in render_constructor"<<" "<<evals<<endl;


}

void Render::copy(const Render& other)
{
  m_agents  = other.m_agents;
  m_objects = other.m_objects;
}
  
void Render::destroy( void )
{
  // Delete agents objects
  for (int a = 0; a < m_agents.size(); a++)
    delete m_agents[a];
  m_agents.clear();
  delete [] image_path;
//delete environ;
  // Delete objects
  for (int o = 0; o < m_objects.size(); o++)
    delete m_objects[o];
  m_objects.clear();
}

Render::~Render()
{
  destroy();
}

void Render::initialization()
{
image_path=new string [num_images];
//environ->init_texture();
//init_texture();
//load_texture();
//init_sphere();
//create_sphere_displaylist();
draw_table();
 //quad= gluNewQuadric();
}


void Render::init_texture()
{

for(int i=0;i<num_images;i++){
texture_name[i]=i;
}

// training set
image_path[0]="../image_textures/image_0.jpg";
image_path[1]="../image_textures/image_1.jpeg";
image_path[2]="../image_textures/image_2.jpg";
image_path[3]="../image_textures/image_3.jpg";
image_path[4]="../image_textures/image_4.jpg";
image_path[5]="../image_textures/image_5.jpeg";
image_path[6]="../image_textures/image_6.jpg";
image_path[7]="../image_textures/image_7.jpg";
image_path[8]="../image_textures/image_8.jpg";
image_path[9]="../image_textures/image_9.jpg";

/*image_path[10]="../image_textures/image_10.jpg";
image_path[11]="../image_textures/image_11.jpg";
image_path[12]="../image_textures/image_12.jpg";
image_path[13]="../image_textures/image_13.jpg";
image_path[14]="../image_textures/image_14.JPG";
image_path[15]="../image_textures/image_15.jpg";
image_path[16]="../image_textures/image_16.jpg";
image_path[17]="../image_textures/image_17.jpg";
image_path[18]="../image_textures/image_18.jpg";
image_path[19]="../image_textures/image_19.jpg";*/

//evaluuating set
/*image_path[0]="../image_textures/image_20.jpg";
image_path[1]="../image_textures/image_21.jpg";
image_path[2]="../image_textures/image_22.jpg";
image_path[3]="../image_textures/image_23.jpg";
image_path[4]="../image_textures/image_24.jpg";
image_path[5]="../image_textures/image_25.jpg";
image_path[6]="../image_textures/image_26.jpg";
image_path[7]="../image_textures/image_27.jpg";
image_path[8]="../image_textures/image_28.jpg";
image_path[9]="../image_textures/image_29.jpg";
image_path[10]="../image_textures/image_30.jpg";
image_path[11]="../image_textures/image_31.jpg";
image_path[12]="../image_textures/image_32.jpg";
image_path[13]="../image_textures/image_33.jpg";
image_path[14]="../image_textures/image_34.jpg";
image_path[15]="../image_textures/image_35.jpg";
image_path[16]="../image_textures/image_36.jpg";
image_path[17]="../image_textures/image_37.jpg";
image_path[18]="../image_textures/image_38.jpg";
image_path[19]="../image_textures/image_39.jpg";*/



}

void Render::load_texture()
{

for(int i=0;i<num_images;i++){
char* result = strcpy((char*)malloc(image_path[i].length()+1), image_path[i].c_str());
FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(result, 0), result);
glEnable(GL_TEXTURE_2D);
glGenTextures(0, &texture_name[i]);
 glBindTexture(GL_TEXTURE_2D,texture_name[i]);
 FIBITMAP *pImage = FreeImage_ConvertTo32Bits(bitmap);
 nWidth = FreeImage_GetWidth(pImage);
nHeight = FreeImage_GetHeight(pImage);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,  nWidth,nHeight,0, GL_RGBA, GL_UNSIGNED_BYTE,(void*)FreeImage_GetBits(pImage));
glDisable(GL_TEXTURE_2D);
 }

}


void Render::init_sphere() {
 //prepare quadric for sphere
    quadric = gluNewQuadric();
    gluQuadricOrientation(quadric, GLU_INSIDE);
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricNormals(quadric, GLU_SMOOTH);
}



//This fucntion is to paint objects in the scene
void Render::paint(int evals, double scal,double rotating)
{
//cout<<"get here1"<<" "<<evals<<endl;
/*glClear(GL_COLOR_BUFFER_BIT);
draw_sphere_environment(evals,scal,rotating);
glFlush();*/
//cout<<"get here3"<<" "<<evals<<endl;
  for(int r = 0; r < m_agents.size(); r++ ){
    m_agents[r]->render( );
  }

  for(int ob = 0; ob < m_objects.size(); ob++){
   // m_objects[ob]->render();

}


draw_objects(evals,scal, rotating);
glCallList(thetable);
//glFlush();
}


//This function is to paint objects in the camera of the robot. These are the objects that the robot sees through its camera
void Render::paintOnlyEnv(int evals, double scaling,double rotation)
{

/*glClear(GL_COLOR_BUFFER_BIT);
draw_sphere_environment( evals, rotation);
glFlush();*/
  for(int r = 0; r < m_agents.size(); r++ ){
   m_agents[r]->render( );
  }

  for(int ob = 0; ob < m_objects.size(); ob++)
    {
     //m_objects[ob]->render();
    }

 
 draw_objects(evals,scaling, rotation);
 glCallList(thetable);


}

void Render::draw_objects( int evals , double x, double angle){
//double x ;
//cout<<"evals 3"<<" "<<evals<<endl;
//cout<<"scale 3"<<" "<<x<<endl;
//cout<<"rotate 3"<<" "<<angle<<endl;

double angle2=0.0;
 GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat positions[] = { 0.0,  -4.0/5.0, 3.0/5.0, 0.0 };
    GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat local_view[] = { 0.0 };

    glClearColor(0.0, 0.1, 0.1, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
 
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, positions);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

   
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 0.0 };
      GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
      GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
      GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
      GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
      GLfloat no_shininess[] = { 4.0 };
      GLfloat low_shininess[] = { 5.0 };
      GLfloat high_shininess[] = { 100.0 };
      GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};
double cat1=(6.5*x); double cat2=(9.0*x); double cat3=(8.0*x); double cat4a=(3.0*x); double cat4b=(5.8*x);
//glPushMatrix();
 if((evals%4)==0){
    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef (3.3, 40.0, 64.5 /*57.0*/);
     //glTranslatef (3.3, 40.0, 57.0); //cube_sphere9 and 10
     glRotatef(angle,0.0,1.0,0.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glutSolidSphere(6.5+cat1, 40, 70);
    glPopMatrix();
  }else if((evals%4)==1){
     glColor3f(1.0, 1.0, 0.0);
     glPushMatrix();
  glTranslatef (3.3, 40.0,64.5 /*57.0*/);
    //glTranslatef (3.3, 40.0, 57.0); //cube_sphere9 and 10
      glRotatef(angle,0.0,1.0,0.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
     glutSolidCube(9.0+cat2); // this for cube
glPopMatrix();
}else if((evals%4)==2){
     glColor3f(1.0, 1.0, 0.0);
     glPushMatrix();
  glTranslatef (3.3, 40.0,61.0 );
      glRotatef(angle,0.0,1.0,0.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
//gluCylinder(GLU quadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint    slices, GLint    stacks);
 //gluCylinder( quad,  6.0,  6.0,  8.0,   50,  50);
  glutSolidCone(8.0+cat3, 8.0+cat3,50, 50);
glPopMatrix();
}else if((evals%4)==3){
     glColor3f(1.0, 1.0, 0.0);
     glPushMatrix();
  glTranslatef (3.3, 40.0,64.0 ); //for torus
  //glTranslatef (3.3, 40.0,61.0 ); //for cone
      glRotatef(angle,0.0,1.0,0.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    //glutSolidCone(8.0, 8.0,50, 50); 
 glutSolidTorus( 3.0+cat4a, 5.8+cat4b, 50, 50); //this for torus
 //glutSolidTeapot(6.5);
glPopMatrix();
}
//glFlush();
 
}

void Render::draw_table(){
  thetable = glGenLists (1);
  glNewList(thetable, GL_COMPILE);
 glPushMatrix();
    glTranslatef(0.0, 50.0, 2.0);

    //glTranslated(0.4, 0, 0.4);
    //glRotatef(10.0,0.0,0.0,1.0);
     glRotatef(130.0,1.0,0.0,0.0);
    //table(0.6, 0.02, 0.02, 0.3); // draw the table
    table(90.0, 10.0, 4.0, 40.0);
  glPopMatrix();
  glEndList(); 


}

void Render::table(double topWid, double topThick, double legThick , double legLen){
    // draw the table  a top and four legs
glColor3f(1.0f, 0.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0, legLen, 0);
    glScalef(topWid,topThick,topWid);
    glutSolidCube(1.0f); //to confirm this
    glPopMatrix();
    double dist = 0.95 *topWid/2.0-legThick/2.0;
    glPushMatrix();
    glTranslatef(dist, 0, dist);
    tableLeg(legThick,legLen);
    glTranslatef(0, 0,-2*dist);
    tableLeg(legThick,legLen);
    glTranslatef(-2*dist, 0, 2*dist);
    tableLeg(legThick,legLen);
    glTranslatef(0, 0,-2*dist);
    tableLeg(legThick,legLen);
 
    glPopMatrix();
    glFlush();
}

void Render::tableLeg(double thick, double len){
    glPushMatrix();
    glTranslatef(0,len/2, 0);
    glScaled(thick,len,thick);
    glutSolidCube(1.0f);
    glPopMatrix();
   //glFlush();

}


/*void Render::create_sphere_displaylist() {
theSphere = glGenLists (1);
glEnable(GL_TEXTURE_2D);
   glNewList(theSphere, GL_COMPILE);
   //glDisable(GL_CULL_FACE);
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
   gluSphere(quadric, 160, 80, 80);
   glDisable(GL_CULL_FACE);
  glEndList();
}*/

void Render::draw_sphere_environment(int evals, double Scalef, double rotated){
evals=evals%num_images;
 glPushMatrix(); 
   glRotatef(rotated,0.0,0.0,1.0);
glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texture_name[evals]);
//glCallList(theSphere);
glDisable(GL_TEXTURE_2D);
glPopMatrix(); 


}



