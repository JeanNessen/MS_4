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

    QPen lines(Qt::black);
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
        for (int j = 0;j < pixleHeigth; j++){
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

void MainWindow::mousePressEvent(QMouseEvent *event){ //wenn man auf das widget clicked werden die koordinaten dem vector hinzugefügt und update() wird aufgerufen.
//    QPoint testPoint;
//    testPoint = event->pos();
//    QPoint pixelCoord = calcField(testPoint);
//    pixelValues[pixelCoord.x()][pixelCoord.y()] = 1;
//    if (pixelValues[pixelCoord.x()][pixelCoord.y()-1] < 1){
//        pixelValues[pixelCoord.x()][pixelCoord.y()-1] = pixelValues[pixelCoord.x()][pixelCoord.y()-1] + 0.25;
//    }
//    if (pixelValues[pixelCoord.x()][pixelCoord.y()+1] < 1){
//        pixelValues[pixelCoord.x()][pixelCoord.y()+1] = pixelValues[pixelCoord.x()][pixelCoord.y()+1] + 0.25;
//    }
//    if (pixelValues[pixelCoord.x()-1][pixelCoord.y()] < 1){
//        pixelValues[pixelCoord.x()-1][pixelCoord.y()] = pixelValues[pixelCoord.x()-1][pixelCoord.y()] + 0.25;
//    }
//    if (pixelValues[pixelCoord.x()+1][pixelCoord.y()] < 1){
//        pixelValues[pixelCoord.x()+1][pixelCoord.y()] = pixelValues[pixelCoord.x()+1][pixelCoord.y()] + 0.25;
//    }
//    pixelValues[pixelCoord.x()][pixelCoord.y()] = 1;

//    full.push_back(pixelCoord);

//    update(); //Alles wird erneuert um die neu gesetzte Stadt anzuzeigen.

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

    update(); //Alles wird erneuert um die neu gesetzte Stadt anzuzeigen.
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
    ui->pixelSizeLabel->setText(QString::number(ui->pixelSlider->value()));

}



void MainWindow::on_pushButton_2_clicked()
{
    width = standartWidth;
    height = standartHeight;
    pixelSize = ui->pixelSlider->value();
    pixelWidth = width/pixelSize;
    pixleHeigth = height/pixelSize;
    width = (width / pixelSize) * pixelSize;
    height = (height / pixelSize) * pixelSize;
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
        for (int j = 0;j < pixleHeigth; j++){
            pixelValues[i][j] = 0.0;
        }
    }
}
