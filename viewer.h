#ifdef _GRAPHICS_
#ifndef VIEWER_H
#define VIEWER_H

#include <Qt>
//#include <glut.h> // use this on my mac
//#include <OpenGL/glu.h> // use this on my mac
#include <GL/glut.h> // use this on rooster
#include <GL/glu.h> // use this on rooster
#include <QApplication>
#include <QGLViewer/qglviewer.h>
#if QT_VERSION >= 0x040000
# include <QKeyEvent>
#endif

#include "render.h"

#include "../MISC/general.h"
//#include "../EXP/experiment.h"
#include "../../ROB_SENSORS_OBJS/icub.h"
#include "../../ROB_SENSORS_OBJS/simple_objects.h"

#include "sky.h"


/* ------------------------------------------------------------------ */
/* ------------------------------------------------------------------ */

#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <cmath>
#include "viewer.h"

#define VIDEO_DEFAULT	"OUT/video3D_%d.mpg"
#define ERR_VIDEOFILE	"No VIDEO file found or permission problem"

#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif
class Viewer;

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libavutil/mem.h>
//#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
#include <libswscale/swscale.h>
}

using namespace std;

typedef struct buffer_s {
	uint8_t *YUV;
	uint8_t *RGB;
	uint8_t *ROW;
} buffer_t;


class Viewer : public QGLViewer, Render
{
  Q_OBJECT;
 public:
  Viewer(QWidget *parent,int eval, double scale, double rot, std::vector< MyIcub* > m_agents, std::vector< SIMPLE_Objects* > m_objects, int argc, char** argv /*, Video *_video */ );
  //Viewer(QWidget *parent, EXP_Class *_exp, int argc, char** argv/*, Video *_video*/ );
  ~Viewer();
  void keyPressEvent(QKeyEvent *e);
  void glDrawCircle(double x1, double y1, double radius);
  void glDrawUnfilledCircle(float cx, float cy, float r, int num_segments);//(float x, float y, float r);

  //Experiment *exp;
  //EXP_Class *exp;
  SKY mySky;
  //Video *video;


  void video_open( void );//const char*, enum CodecID);
  void video_append_frame( void );
  void video_close(void);
  bool isRecording( void ){return recording;}
  inline void free_buffers(buffer_t *buff) {
    free(buff->YUV);
    free(buff->RGB);
    free(buff->ROW);
  }
  inline void set_recording( bool flag ){ recording = flag; }
  virtual void draw(int , double, double);
int evals;
double scales;
double  rotation;
 protected:
  virtual void init();

    
 private:
  unsigned char *pRGB;
 
  bool recording;
  buffer_t video_buff;
  int w;

  //They have to be initialised
  //int oX, oY, eX, eY, pixsize, stride;
  int screen[4];
  int oX, oY, eX, eY, pixsize, stride;
  FILE *VIDEOHandler;
  AVFrame *YUV_frame;
  AVFrame *RGB_frame;
  int fcnt;

  AVCodec *codec;
  AVCodecContext *codec_context;
  struct SwsContext *img_convert_codec_context;



};

#endif
#endif
