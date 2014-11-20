#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    virtual void closeEvent(QCloseEvent *event);
private slots:
    void on_SetColor_clicked();

    void on_l_valueChanged(double arg1);

    void on_w_valueChanged(double arg1);

    void on_h_valueChanged(double arg1);

    void on_pyr1_valueChanged(double arg1);

    void on_pyr2_valueChanged(double arg1);

    void on_X_LIGHT_valueChanged(double arg1);

    void on_Y_LIGHT_valueChanged(double arg1);

    void on_Z_LIGHT_valueChanged(double arg1);

    void on_Set_Texture_clicked();

    void on_Enable_Texture_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    QColor color;
    OpenGLScene *w;
};

#endif // MAINWINDOW_H
