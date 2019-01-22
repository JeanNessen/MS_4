#include <vector>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMainWindow>
#include <QDebug>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e){
    QPainter painter(this);

    QPen lines(Qt::gray);
    lines.setWidth(1);
    QPen all(Qt::white);
    all.setWidth(1);
    QPen linepen(Qt::red);
    linepen.setWidth(2);
    QPen centerpen(Qt::green);
    centerpen.setWidth(6);
    QPen elasticnodespen(Qt::red);
    elasticnodespen.setWidth(4);
    QPen elasticlinespen(Qt::black);
    elasticlinespen.setWidth(1);



    painter.setPen(all);
    painter.fillRect(0,0,width, height, QBrush(Qt::white));

    painter.setPen(lines); //Hier wird das Grid auf die Zeichenfläche gemalt.
    for (int i = 0; i <= height; i += pixelSize ){
        painter.drawLine(0, i, width, i);
    }
    for (int i = 0; i <= width; i += pixelSize){
        painter.drawLine(i, 0, i, height);
    }

    for(int i = 0; i < pixelWidth; i++){
        for (int j = 0;j < pixelHeigth; j++){
            if (pixelValues[i][j] == 0.25){
                painter.fillRect(i*pixelSize+1,j*pixelSize+1, pixelSize-1, pixelSize-1, QBrush(lGray));
            }
            if (pixelValues[i][j] == 0.5){
                painter.fillRect(i*pixelSize+1,j*pixelSize+1, pixelSize-1, pixelSize-1, QBrush(mGray));
            }
            if (pixelValues[i][j] == 0.75){
                painter.fillRect(i*pixelSize+1,j*pixelSize+1, pixelSize-1, pixelSize-1, QBrush(dGray));
            }
            if (pixelValues[i][j] == 1){
                painter.fillRect(i*pixelSize+1,j*pixelSize+1, pixelSize-1, pixelSize-1, QBrush(Qt::black));
            }

        }
    }




}

void MainWindow::mousePressEvent(QMouseEvent *event){
    QPoint testPoint;
    testPoint = event->pos();
    QPoint pixelCoord = calcField(testPoint);
    pixelValues[pixelCoord.x()][pixelCoord.y()] = 1;
    if (pixelValues[pixelCoord.x()][pixelCoord.y()-1] < 1){
        pixelValues[pixelCoord.x()][pixelCoord.y()-1] = pixelValues[pixelCoord.x()][pixelCoord.y()-1] + 0.25;
    }
    if (pixelValues[pixelCoord.x()][pixelCoord.y()+1] < 1){
        pixelValues[pixelCoord.x()][pixelCoord.y()+1] = pixelValues[pixelCoord.x()][pixelCoord.y()+1] + 0.25;
    }
    if (pixelValues[pixelCoord.x()-1][pixelCoord.y()] < 1){
        pixelValues[pixelCoord.x()-1][pixelCoord.y()] = pixelValues[pixelCoord.x()-1][pixelCoord.y()] + 0.25;
    }
    if (pixelValues[pixelCoord.x()+1][pixelCoord.y()] < 1){
        pixelValues[pixelCoord.x()+1][pixelCoord.y()] = pixelValues[pixelCoord.x()+1][pixelCoord.y()] + 0.25;
    }
    else {
        update();
    }
    pixelValues[pixelCoord.x()][pixelCoord.y()] = 1;

    full.push_back(pixelCoord);

    update();

}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    QPoint testPoint;
    testPoint = event->pos();
    QPoint pixelCoord = calcField(testPoint);
    pixelValues[pixelCoord.x()][pixelCoord.y()] = 1;
    if (pixelValues[pixelCoord.x()][pixelCoord.y()-1] < 1){
        pixelValues[pixelCoord.x()][pixelCoord.y()-1] = pixelValues[pixelCoord.x()][pixelCoord.y()-1] + 0.25;
    }
    if (pixelValues[pixelCoord.x()][pixelCoord.y()+1] < 1){
        pixelValues[pixelCoord.x()][pixelCoord.y()+1] = pixelValues[pixelCoord.x()][pixelCoord.y()+1] + 0.25;
    }
    if (pixelValues[pixelCoord.x()-1][pixelCoord.y()] < 1){
        pixelValues[pixelCoord.x()-1][pixelCoord.y()] = pixelValues[pixelCoord.x()-1][pixelCoord.y()] + 0.25;
    }
    if (pixelValues[pixelCoord.x()+1][pixelCoord.y()] < 1){
        pixelValues[pixelCoord.x()+1][pixelCoord.y()] = pixelValues[pixelCoord.x()+1][pixelCoord.y()] + 0.25;
    }
    pixelValues[pixelCoord.x()][pixelCoord.y()] = 1;

    full.push_back(pixelCoord);

    update();
}

QPoint MainWindow::calcField(QPoint point){
    int xpoint = point.x();
    int ypoint = point.y();
    xpoint = xpoint/pixelSize;
    ypoint = ypoint/pixelSize;
    QPoint coord(xpoint,ypoint);

    return coord;

}





void MainWindow::on_pixelSlider_valueChanged(int value)
{
    ui->pixelSizeLabel->setText(QString::number(value));

}



void MainWindow::on_pushButton_2_clicked()
{
    width = slider_width;
    height = slider_height;
    pixelSize = ui->pixelSlider->value();
    pixelWidth = width/pixelSize;
    pixelHeigth = height/pixelSize;
    width = (width / pixelSize) * pixelSize;
    height = (height / pixelSize) * pixelSize;
    ui->height_value_label->setText(QString::number(height));
    ui->width_value_label->setText(QString::number(width));
    qDebug() << width;
    clear();
    update();
}

void MainWindow::on_clearButton_clicked()
{
    clear();
    update();
}

void MainWindow::clear(){
    for(int i = 0; i < pixelWidth; i++){
        for (int j = 0;j < pixelHeigth; j++){
            pixelValues[i][j] = 0.0;
        }
    }
}

void MainWindow::on_Width_slider_valueChanged(int value)
{
    ui->width_value_label->setText(QString::number(value));
    slider_width = value;
}

void MainWindow::on_height_slider_valueChanged(int value)
{
    ui->height_value_label->setText(QString::number(value));
    slider_height = value;
}

void MainWindow::on_apply_width_heigthbutton_clicked()
{
    width = slider_width;
    height = slider_height;
    pixelWidth = width/pixelSize;
    pixelHeigth = height/pixelSize;
    width = (width / pixelSize) * pixelSize;
    height = (height / pixelSize) * pixelSize;
    ui->height_value_label->setText(QString::number(height));
    ui->width_value_label->setText(QString::number(width));
    clear();
    update();
}

void MainWindow::on_defaultButton_clicked()
{
    slider_width = 750;
    slider_height = 750;
    pixelSize = slider_height/28;
    width = slider_width;
    height = slider_height;
    pixelWidth = width/pixelSize;
    pixelHeigth = height/pixelSize;
    width = (width / pixelSize) * pixelSize;
    height = (height / pixelSize) * pixelSize;
    ui->height_value_label->setText(QString::number(height));
    ui->width_value_label->setText(QString::number(width));
    clear();
    update();
}
