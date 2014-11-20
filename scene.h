//#ifndef MAINWINDOW_H
//#define MAINWINDOW_H

#include <QGLWidget> // подключаем класс QGLWidget
#include <QtOpenGL>

class OpenGLScene : public QGLWidget
{
    Q_OBJECT
    protected:
        // метод для проведения инициализаций, связанных с OpenGL
        void initializeGL();
        // метод вызывается при изменении размеров окна
        void resizeGL(int nWidth, int nHeight);
        // метод, чтобы заново перерисовать содержимое виджета
        void paintGL();
        // метод обработки события мыши при нажатии клавиши мыши
        void mousePressEvent(QMouseEvent* pe);
          // метод обработки события мыши при перемещении мыши
        void mouseMoveEvent(QMouseEvent* pe);
              // метод обработки событий колесика мыши
        void wheelEvent(QWheelEvent* pe);
              // методы обработки события при нажатии определенной клавиши
        void keyPressEvent(QKeyEvent* pe);
    public:
        OpenGLScene(QColor _clr, GLfloat _length=0.75f, GLfloat _width=0.75f, GLfloat _heigt=0.75f,
                    GLfloat _pyr1=0.75f, GLfloat _pyr2 = 0.75f,
                    GLfloat _light_x = 0,GLfloat _light_y = 0,GLfloat _light_z = 0, QWidget *parent = 0);
        ~OpenGLScene();
        void set_color(QColor color);
        void set_lenght(GLfloat _length);
        void set_width(GLfloat _width);
        void set_height(GLfloat _height);
        void set_pyr1(GLfloat _pyr1);
        void set_pyr2(GLfloat _pyr2);
        void set_light_x(GLfloat _light_x);
        void set_light_y(GLfloat _light_y);
        void set_light_z(GLfloat _light_z);
        void set_texture(QString path,bool enable);
    private:
        GLfloat xRot;
        GLfloat yRot;
        GLfloat zRot;
        GLfloat nSca;
        GLfloat l,w,h,h1,h2;
        QColor clr;
        bool textured;
        QString path;
        GLfloat light_pos[4];
        QPoint ptrMousePosition; // координата указателя мыши
        void scale_plus();     // приблизить сцену
        void scale_minus();    // удалиться от сцены
        void rotate_up();      // повернуть сцену вверх
        void rotate_down();    // повернуть сцену вниз
        void rotate_left();    // повернуть сцену влево
        void rotate_right();   // повернуть сцену вправо
        void defaultScene();   // наблюдение сцены по умолчанию
        void drawFigure();     // построить фигуру
        void load_texture(QString path);
};

//#endif // MAINWINDOW_H
