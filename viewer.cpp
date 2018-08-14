#ifdef _GRAPHICS_
#include "viewer.h"

using namespace std;
using namespace qglviewer;

Viewer::Viewer(QWidget *parent, int eval , double scale, double rot, std::vector< MyIcub* > _m_agents, std::vector< SIMPLE_Objects* > _m_objects, int argc, char** argv /*, Video *_video*/  )
  : QGLViewer(QGLFormat(QGL::Rgba),parent), Render( _m_agents,  _m_objects )
    //QGL::SampleBuffers |
    //QGL::DoubleBuffer |
    //QGL::DepthBuffer |
    //QGL::Rgba |
    //QGL::AlphaChannel |
    //QGL::StencilBuffer),parent)
{
  //exp = _exp;
  //video = _video;
  //glutInit(&argc, argv);

  // glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);  
  // glutInitWindowPosition(300, 300);
  // glutInitWindowSize(500, 500);
  // glutCreateWindow("main window");
  // void (*draw)(void) = draw;
  // glutDisplayFunc( draw );
evals=eval;
scales=scale;
rotation=rot;
  //cout<<"eval in vewer constructor"<<" "<<evals<<endl;
  recording = false;
  init();
}


Viewer::~Viewer()
{
  //delete[] exp;
}

void Viewer::init()
{
  glutInitWindowSize(width(), height());
  glutInitWindowPosition(20, 150);
  glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
  w = glutCreateWindow("Scene camera");

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  //glEnable(GL_TEXTURE_2D);
  
  glMatrixMode(GL_PROJECTION);
  glFrustum(-0.3, 0.3, -0.3, 0.3, 1, 1000);
  glViewport(0, 0, width(), height());

  glMatrixMode(GL_MODELVIEW);

  // Point of view   (eye)   |(where we look)|   (up)
  gluLookAt(0.0, 200.0, 130.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

  //camera()->setPosition(Vec(0,100,60));
  //theta rotates the Camera around its Y axis, and then phi rotates it around its X axis.
  //float theta=-M_PI;
  //float phi=(3.0*M_PI)/2.0;
  //camera()->setOrientation(theta, phi );

  initialization();
  glFlush();
  draw(evals,/* scales, */rotation);

  // //  resizeGL(200, 200);
  // glClearColor(0.0, 0.0, 0.0, 0.0); 
  // //glClearDepth(0.0);
  // glClear(GL_COLOR_BUFFER_BIT );//| GL_DEPTH_BUFFER_BIT );
  // glFlush();
  
  // setGridIsDrawn();
  // setSceneRadius( 300.0 );//300 cm
  // setSceneCenter(Vec(0.0, 0.0, 0.0) );
  // //showEntireScene();

  // camera()->setPosition(Vec(0,100,60));


  // vector <double> R3;
  // double *p = new double[3];
  // float *m = new float[16];
  // R3.assign(12, 0.0);
  // p[0] = exp->getAgent(0)->RE2[3];
  // p[1] = exp->getAgent(0)->RE2[7]; 
  // p[2] = exp->getAgent(0)->RE2[11];
  // R4toR3andPOS(R3, p, exp->getAgent(0)->RE2 );
  // convert_rot_matrix_for_openGL( m, p, R3);

  //Now the rotation of the camera, corresponding to the rotation of
  //the right eye, is stored in m. Now you need to find a funcxtion
  //that set the camera rotation given the rotation matrix m.
 

  	    //glPushMatrix();

  	    //glMultMatrixf(m);
  	    //camera()->setPosition(Vec(exp->getAgent(0)->RE2[3], exp->getAgent(0)->RE2[7], exp->getAgent(0)->RE2[11]));
  //camera()->setOrientation(M_PI, (3.0*M_PI)/2.0 );
  //glPopMatrix();
  //glFlush();

  //theta rotates the Camera around its Y axis, and then phi rotates it around its X axis.
  // float theta=-M_PI;
  // float phi=(3.0*M_PI)/2.0;
  // camera()->setOrientation(theta, phi );
  
  //initialiser le ciel
  // mySky.LoadTexture( SKY_FRONT, "../IMAGES/sky.jpg" );
  // mySky.LoadTexture( SKY_BACK, "../IMAGES/ground.jpg" );

  // mySky.LoadTexture( SKY_RIGHT,"../IMAGES/brick.jpg" );
  // mySky.LoadTexture( SKY_LEFT, "../IMAGES/sky.jpg" );
  // mySky.LoadTexture( SKY_TOP, "../IMAGES/sky.jpg" );
  // mySky.LoadTexture( SKY_BOTTOM, "../IMAGES/brick.jpg" );

  /* turn on default lighting */
  // glEnable(GL_LIGHTING);
  // glEnable(GL_LIGHT0);
  // GLfloat ambient[] = { 0.5f, 0.5f, 0.5f };
  // GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f , 0.0f};
  // GLfloat specular[] = { 0.25f, 0.25f, 0.25f , 0.0f};
  // //GLfloat lightcolor[] = { 0.8, 0.8, 0.8 };

  // glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  // glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  // glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}

void Viewer::draw(int evals , double scale, double rot)
{
//cout<<"get to Viewer::draw"<<endl;
  glutSetWindow(w);
  glDrawBuffer(GL_FRONT);
  //resizeGL(50, 50);
  //glClearColor(0.2, 0.2, 0.2, 0.0);
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  paint(evals , scale, rot);
  

  glFlush();
   // glutSwapBuffers();//bpt
  // glColor3f(0.0, 0.0, 0.0);
  //  if (mySky.wantSky())
  //    {
  //      //mySky.Set( -18.0, -18.0, 0.0, 36.0f );
  //      //mySky.Set( -150.0, -150.0, 0.0, 300.0f );
  //      //mySky.Render( );
  //    }

  //  for(int r = 0; r < exp->getNbAgents(); r++ ){
  //    exp->getAgent(r)->render( );
  //  }
   
  //  for(int ob = 0; ob < exp->getNbObjects(); ob++) 
  //   exp->getObject(ob)->render();


  if( recording )
    {
      // int nWidth = width();
      // int nHeight = height();
      // pRGB = new unsigned char [4 * (nWidth) * (nHeight)];
    
      // glReadBuffer( GL_FRONT );
      // glReadPixels(0, 0, nWidth, nHeight, GL_RGBA, GL_UNSIGNED_BYTE, pRGB);
    
      //video->AddFrame(pRGB);

      video_append_frame( );

      //delete pRGB;
    }
//cout<<"end Viewer::draw"<<endl;

}


void Viewer::keyPressEvent(QKeyEvent *e)
{
#if QT_VERSION < 0x040000
  if (e->state() == Qt::NoButton)
#else
  if (e->modifiers() == Qt::NoModifier)
#endif
    switch (e->key())
      {
      case Qt::Key_S:         //switch sky
	mySky.switchSky();
	updateGL();
	break;
      default: QGLViewer::keyPressEvent(e);           //handler de la classe superieure
      }
  else
    QGLViewer::keyPressEvent(e);
}

void Viewer::glDrawUnfilledCircle(float cx, float cy, float r, int num_segments){//float x, float y, float r){
  float theta = 2 * 3.1415926 / float(num_segments); 
  float tangetial_factor = tanf(theta);//calculate the tangential factor 
  
  float radial_factor = cosf(theta);//calculate the radial factor 
  
  float x = r;//we start at angle = 0 
  
  float y = 0; 
  
  glBegin(GL_LINE_LOOP); 
  for(int ii = 0; ii < num_segments; ii++) 
    { 
      glVertex2f(x + cx, y + cy);//output vertex 
      
      //calculate the tangential vector 
      //remember, the radial vector is (x, y) 
      //to get the tangential vector we flip those coordinates and negate one of them 
      
      float tx = -y; 
      float ty = x; 
      
      //add the tangential vector 
      
      x += tx * tangetial_factor; 
      y += ty * tangetial_factor; 
      
      //correct using the radial factor 
      
      x *= radial_factor; 
      y *= radial_factor; 
    } 
  glEnd(); 
  
  // static const double inc = M_PI / 5;
  // static const double max = 2 * M_PI;
  // glBegin(GL_LINE_LOOP);
  // for (int d = 0; d < max; d+= inc){
  //   glVertex2f(cos(d) * r + x, sin(d) * r + y);
  // }
  // glEnd();
}

void Viewer::glDrawCircle(double x1, double y1, double radius) {
  
  double x2,y2,angle;
  
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(x1,y1);
  
  for (angle=1.0f;angle<361.0f;angle+=0.2)
    {
      x2 = x1+sin(angle)*radius;
      y2 = y1+cos(angle)*radius;
      glVertex2f(x2,y2);
    }
  
  glEnd();
}


void Viewer::video_open( void ){ //const char *filename, enum CodecID codec_id) {
  
  codec = NULL;
  codec_context = NULL;
  img_convert_codec_context = NULL;

  char filename[500];
  sprintf(filename, "sim.mp4");
  
  glGetIntegerv(GL_VIEWPORT, screen);
  oX = screen[0];
  oY = screen[1];
  eX = screen[2];
  eY = screen[3];
  pixsize = eX * eY;
  stride = 3 * eX;
  if (eX % 2 || eY % 2) {
    cout << "Fatal error: video dimensions % 2 non equal" << endl;
    exit(EXIT_FAILURE);
  }  


  if (!(video_buff.RGB = (uint8_t*) malloc(stride * eY)) || !(video_buff.ROW = (uint8_t*) malloc(stride))
      || !(video_buff.YUV = (uint8_t*) malloc(3 * (pixsize / 2)))) {
    cout << "Fatal error: cannot allocate video bufer memory" << endl;
    exit(EXIT_FAILURE);
  }
  
  avcodec_register_all();
  
  //DEBUG("Preparing codec/codec context for video file " << filename << endl);
  
  codec = avcodec_find_encoder( CODEC_ID_MPEG2VIDEO /*codec_id */);
  if (!codec) {
    cout << "Fatal error: codec not found" << endl;
    exit(EXIT_FAILURE);
  }

  codec_context = avcodec_alloc_context3(codec);
  if (!codec_context) {
    cout << "Fatal error: codec context not allocated" << endl;
    exit(EXIT_FAILURE);
  }

  codec_context->bit_rate = 40000000;
  codec_context->bit_rate_tolerance = 4000000;
  codec_context->width = eX;
  codec_context->height = eY;
  codec_context->time_base.num = 1;
  codec_context->time_base.den = 15;
  codec_context->gop_size = 20;
  codec_context->max_b_frames = 2;
  codec_context->pix_fmt = PIX_FMT_YUV420P;
  codec_context->codec_type = AVMEDIA_TYPE_VIDEO;
  codec_context->flags |= CODEC_FLAG_GLOBAL_HEADER;
  codec_context->max_qdiff = 1;
  codec_context->qmin = 1;
  codec_context->qmax = 30;
  codec_context->qcompress = 0.6;
  codec_context->keyint_min = 120;
  codec_context->flags |= CODEC_FLAG_PSNR;
  
  if (avcodec_open2(codec_context, codec, NULL) < 0) {
    cout << "Fatal error: cannot open codec" << endl;
    exit(EXIT_FAILURE);
  }

  VIDEOHandler = fopen(filename, "wb");
  if (!VIDEOHandler) {
    cout << ERR_VIDEOFILE << endl;
    exit(EXIT_FAILURE);
  }

  // YUV_frame = avcodec_alloc_frame();
  // if (!YUV_frame) {
  //   cout << "Fatal error: cannot allocate video frame" << endl;
  //   exit(EXIT_FAILURE);
  // }
}

/* -------------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------- */

void Viewer::video_close(void) {
  if (VIDEOHandler) {
    free_buffers(&video_buff);
    avcodec_free_frame(&RGB_frame);
    avcodec_free_frame(&YUV_frame);
    
    int ret, got_output;
    
    for (got_output = 1; got_output;) {
      fflush(stdout);
      AVPacket pkt;
      av_init_packet(&pkt);
      pkt.data = NULL;
      pkt.size = 0;
      pkt.pts = ++fcnt;
      
      fflush(stdout);
      ret = avcodec_encode_video2(codec_context, &pkt, NULL, &got_output);
      if (ret < 0) {
	cout << "Fatal error: cannot encode frame" << endl;
	exit(EXIT_FAILURE);
      }
      if (got_output) {
	fwrite(pkt.data, 1, pkt.size, VIDEOHandler);
	av_free_packet(&pkt);
      }
    }
    
    uint8_t endcode[] = { 0, 0, 1, 0xb7 };
    fwrite(endcode, 1, sizeof(endcode), VIDEOHandler);
    fclose(VIDEOHandler);
    avcodec_close(codec_context);
    av_free(codec_context);
    fflush( stdout);
    //DEBUG("Closing video file" << endl);
  }
}

void Viewer::video_append_frame( void ) {
  int ret, got_output;
  
  YUV_frame = avcodec_alloc_frame();
  YUV_frame->data[0] = video_buff.YUV;
  YUV_frame->data[1] = video_buff.YUV + pixsize;
  YUV_frame->data[2] = video_buff.YUV + pixsize + pixsize / 4;
  YUV_frame->linesize[0] = eX;
  YUV_frame->linesize[1] = eX / 2;
  YUV_frame->linesize[2] = eX / 2;
  
  RGB_frame = avcodec_alloc_frame();
  RGB_frame->data[0] = video_buff.RGB;
  RGB_frame->data[1] = video_buff.RGB;
  RGB_frame->data[2] = video_buff.RGB;
  RGB_frame->linesize[0] = stride;
  RGB_frame->linesize[1] = stride;
  RGB_frame->linesize[2] = stride;
  
  glReadBuffer(GL_FRONT);
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glReadPixels(oX, oY, eX, eY, GL_RGB, GL_UNSIGNED_BYTE, video_buff.RGB);
  
  for (int y = 0; y < eY / 2; y++) {
    uint8_t *r1 = video_buff.RGB + stride * y;
    uint8_t *r2 = video_buff.RGB + stride * (eY - 1 - y);
    memcpy(video_buff.ROW, r1, stride);
    memcpy(r1, r2, stride);
    memcpy(r2, video_buff.ROW, stride);
  }

  if (img_convert_codec_context == NULL)
    img_convert_codec_context = sws_getContext(eX, eY, PIX_FMT_RGB24, eX,
					       eY, PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
  if (img_convert_codec_context == NULL) {
    cout << "Fatal error: cannot convert video frame" << endl;
    exit(EXIT_FAILURE);
  }
  
  for (int i = 0; i < 3; i++)
    cout << " " << RGB_frame->data[i] << endl;  


  sws_scale(img_convert_codec_context, RGB_frame->data, RGB_frame->linesize,
	    0, eY, YUV_frame->data, YUV_frame->linesize);
  
  AVPacket pkt;
  av_init_packet(&pkt);
  YUV_frame->pts = AV_NOPTS_VALUE;
  pkt.data = NULL;
  pkt.size = 0;
  pkt.pts = AV_NOPTS_VALUE; // should be calculated based on frame counter + framerate (kHz ?)
  pkt.dts = AV_NOPTS_VALUE;
  
  fflush(stdout);

  ret = avcodec_encode_video2(codec_context, &pkt, YUV_frame, &got_output);
  if (ret < 0) {
    cout << "Fatal error: cannot encode frame" << endl;
    exit(EXIT_FAILURE);
  }

  
  if (got_output) {
    //BUG("Writing frame of size " << pkt.size << endl);
    fwrite(pkt.data, 1, pkt.size, VIDEOHandler);
    av_free_packet(&pkt);
  }
}
#endif
