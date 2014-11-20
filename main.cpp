#include <QApplication>
#include "mainwindow.h"
//#include "scene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*OpenGLScene w;
    w.setWindowTitle("OpenGl");
    w.show();*/
    MainWindow mainwindow1; // создаётся главное окно
    mainwindow1.show(); // показать главное окно максимально развёрнутым
    return a.exec();
}
