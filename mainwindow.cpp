#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "scene.h"
#include <QtOpenGL>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    color = Qt::red;
    w = new OpenGLScene(color,(GLfloat)ui->l->value(),(GLfloat)ui->w->value(),(GLfloat)ui->h->value(),
                                     (GLfloat)ui->pyr1->value(),(GLfloat)ui->pyr2->value(),
                                     (GLfloat)ui->X_LIGHT->value(),(GLfloat)ui->Y_LIGHT->value(),(GLfloat)ui->Z_LIGHT->value());
    w->setWindowTitle("OpenGL");
    w->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SetColor_clicked()
{
    color = QColorDialog::getColor(color);
    if (!color.isValid() )
    {
    // Cancel
    } else w->set_color(color);
}

void MainWindow::on_l_valueChanged(double arg1)
{
    w->set_lenght((GLfloat)arg1);
}

void MainWindow::on_w_valueChanged(double arg1)
{
    w->set_width((GLfloat)arg1);
}

void MainWindow::on_h_valueChanged(double arg1)
{
    w->set_height((GLfloat)arg1);
}

void MainWindow::on_pyr1_valueChanged(double arg1)
{
    w->set_pyr1((GLfloat)arg1);
}

void MainWindow::on_pyr2_valueChanged(double arg1)
{
    w->set_pyr2((GLfloat)arg1);
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    w->close();
    event->accept();
}

void MainWindow::on_X_LIGHT_valueChanged(double arg1)
{
    w->set_light_x((GLfloat)arg1);
}

void MainWindow::on_Y_LIGHT_valueChanged(double arg1)
{
    w->set_light_y((GLfloat)arg1);
}

void MainWindow::on_Z_LIGHT_valueChanged(double arg1)
{
    w->set_light_z((GLfloat)arg1);
}

void MainWindow::on_Set_Texture_clicked()
{
    QString tmp = "";
    tmp = QFileDialog::getOpenFileName(0, "Open Dialog", "", tr("PNG(*.png);;JPG(*.jpg);;BMP(*.bmp)"));
    if (tmp == "")
    {
        QMessageBox::critical(this,"Ошибка","Не выбран файл текстуры");
        ui->Enable_Texture->setChecked(false);
        return;
    }
    else
    {
        w->set_texture(tmp,true);
    }
}


void MainWindow::on_Enable_Texture_clicked(bool checked)
{
    if (checked)
    {
        ui->Set_Texture->setEnabled(true);
        ui->SetColor->setEnabled(false);
        ui->Set_Texture->click();
    }else
    {
        ui->Set_Texture->setEnabled(false);
        ui->SetColor->setEnabled(true);
        w->set_texture("",false);
    }
}
