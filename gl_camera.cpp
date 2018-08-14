#include "gl_camera.h"

using namespace std;

GL_Camera::GL_Camera(int eval,double scale, double rotate, std::vector< MyIcub* > _m_agents, std::vector< SIMPLE_Objects* > _m_objects, bool _display, int camera_mode, int argc, char** argv)
  : Render(_m_agents,  _m_objects  )
{

  //#ifdef _GRAPHICS_
  glutInit(&argc, argv);
  //#endif
evals=eval;
scales=scale;
rotates=rotate;


  display = _display; //if display=false we use MESA (nothing displayed on screen) else we use GLUT (with rendering)
  w = new int[ m_agents.size() ];
 
  mode = camera_mode;
  if( mode < 4 )
    num_gl_camera_channels = 1;
  else
    num_gl_camera_channels = 3;

  init( );
  
}

GL_Camera::~GL_Camera()
{
  destroy();
}

void GL_Camera::destroy(){
  delete[] pRGB;
  delete[] w;


}

/* ---------------------------------------------------------------------------------------- */
GL_Camera::GL_Camera(const GL_Camera& other)
  : Render(  other.m_agents,  other.m_objects )
{
  copy(other);
}
/* ---------------------------------------------------------------------------------------- */
void GL_Camera::copy(const GL_Camera& other)
{ 
	Render::copy(other);
  w = new int[ other.m_agents.size() ];
  display = other.display;
  num_gl_camera_channels = other.num_gl_camera_channels;
  mode = other.mode;

 evals=other.evals;
scales=other.scales;
//rotates=other.rotates;
  ratio = other.ratio;
  depth = other.depth;
  width = other.width;  
  minClip = other.minClip;
  maxClip = other.maxClip;
  height = other.height;

  display = other.display;
 
  ctx = other.ctx;
  num_gl_camera_channels = other.num_gl_camera_channels;
  mode = other.mode;

 

  init();

}

/* ---------------------------------------------------------------------------------------- */

GL_Camera& GL_Camera::operator=(const GL_Camera &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }

    return *this;
}
/* ---------------------------------------------------------------------------------------- */

void GL_Camera::init( )
{

 alpha_gamma_lamda.assign(3, 0.0);
  //Properties of the camera
  ratio = 1.0; //between width and height  
  depth = 1.0;
  width = 100;
  
  height = (int)((float)width/ratio);
  minClip = 0.9;
  maxClip = 300.0;
  if(width < 1) width = 1;
  if(height < 1) height = 1;
  pRGB = new unsigned char [4 * width * height];
  
  if(!display)
    {

      /* Create an RGBA-mode context */
#if OSMESA_MAJOR_VERSION * 100 + OSMESA_MINOR_VERSION >= 305
      /* specify Z, stencil, accum sizes */
      ctx = OSMesaCreateContextExt( OSMESA_RGBA, 16, 0, 0, NULL );
#else
      ctx = OSMesaCreateContext( OSMESA_RGBA, NULL );
#endif
      if (!ctx) {
	printf("OSMesaCreateContext failed!\n");
      }
      
     
      if (!OSMesaMakeCurrent( ctx, pRGB, GL_UNSIGNED_BYTE , width, height )) {
	printf("OSMesaMakeCurrent failed!\n");
      }
      initw();

    }
  else
    {
      glutInitWindowSize(width, height);
      glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
      char buff[10];
      for(int i = 0; i < m_agents.size(); i++)
	{
	  glutInitWindowPosition(20 + i*width, 20);
	  sprintf(buff, "Robot %i", i);
	  w[i] = glutCreateWindow(buff);
      initw();


    }

    }
}

void GL_Camera::initw()
{
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  
  glMatrixMode(GL_PROJECTION);
  glFrustum(-depth, depth, -depth/ratio, depth/ratio, minClip, maxClip);
  glViewport(0, 0, width, height);
  
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  initialization();
  glFlush();
}


void GL_Camera::draw(int r, int evals , double scale, double rotate)
{
 
  if(display)
    glutSetWindow(w[r]);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  
  glPushMatrix();
  vector <double> position;
  position.assign(3, 0.0);
  vector <double> pointM;
  pointM.assign(16, 0.0);
  
  vector <double> cameraPosition;
  R4SetIdentity( pointM, &position[0] );
  pointM[3]  = 0.0;
  pointM[7]  = 0.0;
  pointM[11] = 0.0;
  cameraPosition.assign(16, 0.0);
  R4Multiply( cameraPosition, m_agents[0]->RE2, pointM );
  
  vector <double> viewpoint;
  R4SetIdentity( pointM, &position[0] );
  pointM[3]  = 0.0;
  pointM[7]  = 0.0;
  pointM[11] = 50.0;//This is the Z axis
  viewpoint.assign(16, 0.0);
  R4Multiply( viewpoint, m_agents[0]->RE2, pointM );
  
  glLoadIdentity();
  gluLookAt(cameraPosition[3], cameraPosition[7], cameraPosition[11], 
	    viewpoint[3], viewpoint[7], viewpoint[11],
   	    0,0,1);
//cout<<"eval in g_camera_draw"<<" "<<evals<<endl;
  paintOnlyEnv(evals , scale, rotate);

 
  glPopMatrix();
  glFlush();
 //glutSwapBuffers(); //bpt

  if(display)
  {
    glReadBuffer( GL_FRONT );
    glReadPixels(0, 0, width, height, GL_RGBA,GL_UNSIGNED_BYTE , pRGB);
    //showPixels();
  }

}

unsigned char* GL_Camera::getData()
{
  return pRGB;
}

int GL_Camera::get_num_pixels()
{
  return width*height*num_gl_camera_channels;
}

void GL_Camera::get_readings(double*camera_readings ){

  int count = 0;  
  if(mode == 3) // Grey levels
    {
      for(int i = 0; i < width; i++)
	{
	  for(int j = 0; j < height; j++)
	    {
   camera_readings[i*height + j] = (float)(pRGB[j*4*width + i*4] + pRGB[j*4*width + i*4 + 1] + pRGB[j*4*width + i*4 + 2])/(255.0*3.0); //for float btw 0 and 1
   //camera_readings[i*height + j] = (int)(pRGB[j*4*width + i*4] + pRGB[j*4*width + i*4 + 1] + pRGB[j*4*width + i*4 + 2])/(3);  // for integer btw 0 and 255
//camera_readings[i*height + j] = (float)((pRGB[j*4*width + i*4])*(get_active_perception()[0]) + (pRGB[j*4*width + i*4 + 1])*(get_active_perception()[1]) + (pRGB[j*4*width + i*4 + 2]) *(get_active_perception()[2]))/(255.0*3.0);  //this for active perception
	    }
	}
    }
  else if(mode >= 0 && mode < 3) // R, G or B levels (0 for Red, 1 for Green and 2 for Blue)
    {
      for(int i = 0; i < width; i++)
	{
	  for(int j = 0; j < height; j++)
	    {
          camera_readings[i*height + j] = (double)(pRGB[j*4*width + i*4 + mode])/255.0;
          
	    }
	}
    }
  else{

    for(int i = 0; i < width; i++)
      {
	for(int j = 0; j < 3*height; j++)
	  {
	    //camera_readings[i*height + j] = (double)(pRGB[j*4*width + i*4])/255.0;
	    //camera_readings[i*height + j + 1] = (double)(pRGB[j*4*width + i*4 + 1])/255.0;
	    //camera_readings[i*height + j + 2] = (double)(pRGB[j*4*width + i*4 + 2])/255.0;
	    count++;
	  }
      }
  }
  //cerr << " " << count << endl;



}


unsigned char GL_Camera::getPixelR(int x, int y)
{
  if(x < 0 || y < 0 || x >= width || y >= height)
    return 0;
  return pRGB[y*4*width + x*4];
}

unsigned char GL_Camera::getPixelG(int x, int y)
{
  if(x < 0 || y < 0 || x >= width || y >= height)
    return 0;
  return pRGB[y*4*width + x*4 + 1];
}

unsigned char GL_Camera::getPixelB(int x, int y)
{
  if(x < 0 || y < 0 || x >= width || y >= height)
    return 0;
  return pRGB[y*4*width + x*4 + 2];
}

unsigned char GL_Camera::showPixel(int x, int y)
{
    printf("Pixel %i, %i : (%i,%i,%i)\n",x,y, getPixelR(x,y), getPixelG(x,y), getPixelB(x,y));
}

unsigned char GL_Camera::showPixels()
{
  for(int i = 0; i < width; i++) {
    printf("Line %i : ", i);
    for(int j = 0; j < 4*height; j++) {
     printf("%i ", pRGB[i*4*height + j]);
    }
    printf("\n");

  }
}
