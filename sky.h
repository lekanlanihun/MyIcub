/****************************************************************************

 Copyright (C) 2002-2008 Gilles Debunne. All rights reserved.

 This file is part of the QGLViewer library version 2.3.4.

 http://www.libqglviewer.com - contact@libqglviewer.com

 This file may be used under the terms of the GNU General Public License 
 versions 2.0 or 3.0 as published by the Free Software Foundation and
 appearing in the LICENSE file included in the packaging of this file.
 In addition, as a special exception, Gilles Debunne gives you certain 
 additional rights, described in the file GPL_EXCEPTION in this package.

 libQGLViewer uses dual licensing. Commercial/proprietary software must
 purchase a libQGLViewer Commercial License.

 This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

*****************************************************************************/

// TP OpenGL: Joerg Liebelt, Serigne Sow
//on ajoute du ciel!
#ifndef __SKYBOX_H__
#define __SKYBOX_H__
#include <GL/glut.h>
#include <GL/glu.h>
#include <qimage.h>

#define SKY_SIDES 6

#define SKY_FRONT  0
#define SKY_BACK   1
#define SKY_RIGHT  2
#define SKY_LEFT   3
#define SKY_TOP    4
#define SKY_BOTTOM 5


class SKY
{
private:
  QImage textures[SKY_SIDES]; //les cotes du ciel
  GLuint texIDs[SKY_SIDES];         //les IDs opengl pour chaque texture
  float vecMin[3], vecMax[3], vecCenter[3];
  bool iwantsky;

public:
  SKY() { iwantsky = true; }

  bool LoadTexture( int side, const QString& filename );

  void Render();

  //parametres du ciel
  void Set( float X, float Y, float Z, float size )
  {
    vecCenter[0] = X;
    vecCenter[0] = Y;
    vecCenter[0] = Z;
    vecMin[0] = 0;
    vecMin[0] = 0;
    vecMin[0] = 0;
    vecMax[0] = size;
    vecMax[0] = size;
    vecMax[0] = size;
  }

  void switchSky() { iwantsky = !iwantsky; }
  bool wantSky() { return iwantsky; }
};


#endif
