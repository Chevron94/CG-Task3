#include "scene.h"
#include "vectornormal.h"
#include <gl\glaux.h>
#include <iostream>

CVector3 vTriangle[3] = { {-1,  0,   0},    {1,    0,   0},  {0,   1,   0} };
CVector3 vNormal = {0,0,0};
GLuint texture[1];
GLfloat Ambient[4] = {0.0,0.0,0.0,1.0};
OpenGLScene::OpenGLScene(QColor _clr, GLfloat _length, GLfloat _width, GLfloat _height, GLfloat _pyr1, GLfloat _pyr2,
                         GLfloat light_x, GLfloat light_y, GLfloat light_z,  QWidget *parent):QGLWidget(parent)
{
    xRot=-90;
    yRot=0;
    zRot=0;
    nSca=1;
    l = _length/2;
    w = _width/2;
    h = _height/2;
    h1 = _pyr1;
    h2 = _pyr2;
    clr = _clr;
    light_pos[0] =light_x;
    light_pos[1] =light_y;
    light_pos[2] =light_z;
    light_pos[3] = 1.0;
    textured = false;
    setWindowFlags(Qt::Window
         | Qt::WindowMinimizeButtonHint
         | Qt::WindowMaximizeButtonHint
         | Qt::CustomizeWindowHint);
}

OpenGLScene::~OpenGLScene()
{
}
void OpenGLScene::initializeGL()
{
    qglClearColor(Qt::white);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable (GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);      // Разрешение сглаженного закрашивания
    glEnable(GL_NORMALIZE);
    glEnable (GL_LIGHTING); // разрешаем работу с освещенностью
}

void OpenGLScene::load_texture(QString path)
{
    QImage img;
    img.load(path);
    img=QGLWidget::convertToGLFormat(img);
    glGenTextures(1,texture);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)img.width(), (GLsizei)img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
}

void OpenGLScene::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth;
    if (nWidth>=nHeight)
          glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 1.0);
    else
          glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 1.0);
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}
void OpenGLScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(textured)
        load_texture(path);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f); // поворот вокруг оси X
    glRotatef(yRot, 0.0f, 1.0f, 0.0f); // поворот вокруг оси Y
    glRotatef(zRot, 0.0f, 0.0f, 1.0f); // поворот вокруг оси Z
    glScalef(nSca, nSca, nSca);          // масштабирование по осям
    drawFigure();
}
void OpenGLScene::set_texture(QString _path, bool enable)
{
    textured = enable;
    path = _path;
    updateGL();
}

void OpenGLScene::set_color(QColor color)
{
    clr = color;
    updateGL();
}

void OpenGLScene::set_lenght(GLfloat _length)
{
    l = _length/2;
    updateGL();
}

void OpenGLScene::set_width(GLfloat _width)
{
    w = _width/2;
    updateGL();
}

void OpenGLScene::set_height(GLfloat _height)
{
    h = _height/2;
    updateGL();
}

void OpenGLScene::set_pyr1(GLfloat _pyr1)
{
    h1 = _pyr1;
    updateGL();
}

void OpenGLScene::set_pyr2(GLfloat _pyr2)
{
    h2 = _pyr2;
    updateGL();
}


void OpenGLScene::set_light_x(GLfloat _light_x)
{
    light_pos[0] =_light_x;
    updateGL();
}

void OpenGLScene::set_light_y(GLfloat _light_y)
{
    light_pos[1] =_light_y;
    updateGL();
}

void OpenGLScene::set_light_z(GLfloat _light_z)
{
    light_pos[2] =_light_z;
    updateGL();
}


void OpenGLScene::mousePressEvent(QMouseEvent* pe)
{
   ptrMousePosition = pe->pos();
}

void OpenGLScene::mouseMoveEvent(QMouseEvent* pe)
{
   // вычисление углов поворота
   xRot += 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
   zRot += 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width();
   ptrMousePosition = pe->pos();
   updateGL();
}

void OpenGLScene::wheelEvent(QWheelEvent* pe)
{
   if ((pe->delta())>0)
       scale_plus();
   else
       if ((pe->delta())<0)
           scale_minus();

   updateGL();
}

void OpenGLScene::keyPressEvent(QKeyEvent* pe)
{
   switch (pe->key())
   {
      case Qt::Key_Plus:
         scale_plus();
      break;

      case Qt::Key_Equal:
         scale_plus();
      break;

      case Qt::Key_Minus:
         scale_minus();
      break;

      case Qt::Key_Up:
         rotate_up();
      break;

      case Qt::Key_Down:
         rotate_down();
      break;

      case Qt::Key_Left:
        rotate_left();
      break;

      case Qt::Key_Right:
         rotate_right();
      break;

      case Qt::Key_Space:
         defaultScene();
      break;
   }
   updateGL();
}
void OpenGLScene::scale_plus()
{
   nSca = nSca*1.1;
}

void OpenGLScene::scale_minus()
{
   nSca = nSca/1.1;
}

void OpenGLScene::rotate_up()
{
   xRot += 1.0;
}

void OpenGLScene::rotate_down()
{
   xRot -= 1.0;
}

void OpenGLScene::rotate_left()
{
   zRot += 1.0;
}

void OpenGLScene::rotate_right()
{
   zRot -= 1.0;
}

void OpenGLScene::defaultScene()
{
    xRot=-90;
    yRot=0;
    zRot=0;
    nSca=1;
}

void OpenGLScene::drawFigure()
{
    qreal r=0,g=0,b=0;
    clr.getRgbF(&r,&g,&b);
    glEnable(GL_LIGHT0);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    if (textured)
    {
        glColor3f(1.0f,1.0f,1.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
    }
    else glColor3f((GLfloat)r,(GLfloat)g,(GLfloat)b);

    vTriangle[0] = {-h1-l,0,0};
    glBegin(GL_TRIANGLES);

        vTriangle[2] = {-l,-w,-h};
        vTriangle[1] = {-l,-w,h};
        vNormal = Normal(vTriangle);

        glNormal3d((GLfloat)vNormal.x,(GLfloat)vNormal.y,(GLfloat)vNormal.z);
        glTexCoord2f(0,0.5f);   glVertex3d(-h1-l,0,0);
        glTexCoord2f(1,0);      glVertex3d(-l,-w,-h);
        glTexCoord2f(1,1);      glVertex3d(-l,-w,h);

        vTriangle[2] = {-l,-w,h};
        vTriangle[1] = {-l,w,h};
        vNormal = Normal(vTriangle);

        glNormal3d((GLfloat)vNormal.x,(GLfloat)vNormal.y,(GLfloat)vNormal.z);

        glTexCoord2f(0,0.5f);   glVertex3d(-h1-l,0,0);
        glTexCoord2f(1,0);      glVertex3d(-l,-w,h);
        glTexCoord2f(1,1);      glVertex3d(-l,w,h);

        vTriangle[2] = {-l,w,h};
        vTriangle[1] = {-l,w,-h};
        vNormal = Normal(vTriangle);

        glNormal3d((GLfloat)vNormal.x,(GLfloat)vNormal.y,(GLfloat)vNormal.z);

        glTexCoord2f(0,0.5f);   glVertex3d(-h1-l,0,0);
        glTexCoord2f(1,0);      glVertex3d(-l,w,h);
        glTexCoord2f(1,1);      glVertex3d(-l,w,-h);

        vTriangle[2] = {-l,w,-h};
        vTriangle[1] = {-l,-w,-h};
        vNormal = Normal(vTriangle);

        glNormal3d((GLfloat)vNormal.x,(GLfloat)vNormal.y,(GLfloat)vNormal.z);

        glTexCoord2f(0,0.5f);   glVertex3d(-h1-l,0,0);
        glTexCoord2f(1,0);      glVertex3d(-l,w,-h);
        glTexCoord2f(1,1);      glVertex3d(-l,-w,-h);
    glEnd();

    vTriangle[0] = {l+h2,0,0};
    glBegin(GL_TRIANGLES);
        vTriangle[2] = {l,w,h};
        vTriangle[1] = {l,-w,h};
        vNormal = Normal(vTriangle);

        glNormal3d((GLfloat)vNormal.x,(GLfloat)vNormal.y,(GLfloat)vNormal.z);

        glTexCoord2f(1,0.5f);  glVertex3d(l+h2,0,0);
        glTexCoord2f(0,1);  glVertex3d(l,w,h);
        glTexCoord2f(0,0);  glVertex3d(l,-w,h);

        vTriangle[2] = {l,-w,h};
        vTriangle[1] = {l,-w,-h};
        vNormal = Normal(vTriangle);

        glNormal3d((GLfloat)vNormal.x,(GLfloat)vNormal.y,(GLfloat)vNormal.z);

        glTexCoord2f(1,0.5f);   glVertex3d(l+h2,0,0);
        glTexCoord2f(0,1);   glVertex3d(l,-w,h);
        glTexCoord2f(0,0);   glVertex3d(l,-w,-h);

        vTriangle[2] = {l,-w,-h};
        vTriangle[1] = {l,w,-h};
        vNormal = Normal(vTriangle);

        glNormal3d((GLfloat)vNormal.x,(GLfloat)vNormal.y,(GLfloat)vNormal.z);

        glTexCoord2f(1,0.5f);   glVertex3d(l+h2,0,0);
        glTexCoord2f(0,1);   glVertex3d(l,-w,-h);
        glTexCoord2f(0,0);   glVertex3d(l,w,-h);

        vTriangle[2] = {l,w,-h};
        vTriangle[1] = {l,w,h};
        vNormal = Normal(vTriangle);

        glNormal3d((GLfloat)vNormal.x,(GLfloat)vNormal.y,(GLfloat)vNormal.z);

        glTexCoord2f(1,0.5f);   glVertex3d(l+h2,0,0);
        glTexCoord2f(0,1);   glVertex3d(l,w,-h);
        glTexCoord2f(0,0);   glVertex3d(l,w,h);
    glEnd();

    glBegin(GL_QUADS);
        glNormal3d(0.0f,0.0f,-1.0f);
        glTexCoord2f(0,1);  glVertex3d(-l,-w,-h);
        glTexCoord2f(0,0);  glVertex3d(-l,w,-h);
        glTexCoord2f(1,0);  glVertex3d(l,w,-h);
        glTexCoord2f(1,1);  glVertex3d(l,-w,-h);

        glNormal3d(0.0f,0.0f,1.0f);
        glTexCoord2f(0,0);  glVertex3d(-l,-w,h);
        glTexCoord2f(1,0);  glVertex3d(l,-w,h);
        glTexCoord2f(1,1);  glVertex3d(l,w,h);
        glTexCoord2f(0,1);  glVertex3d(-l,w,h);

        glNormal3d(0.0f,-1.0f,0.0f);
        glTexCoord2f(0,0);  glVertex3d(-l,-w,-h);
        glTexCoord2f(1,0);  glVertex3d(l,-w,-h);
        glTexCoord2f(1,1);  glVertex3d(l,-w,h);
        glTexCoord2f(0,1);  glVertex3d(-l,-w,h);

        glNormal3d(0.0f,1.0f,0.0f);
        glTexCoord2f(1,1);  glVertex3d(l,w,-h);
        glTexCoord2f(0,1);  glVertex3d(-l,w,-h);
        glTexCoord2f(0,0);  glVertex3d(-l,w,h);
        glTexCoord2f(1,0);  glVertex3d(l,w,h);
    glEnd();

    if (textured)
    {
        glDisable(GL_TEXTURE_2D);
    }
}
