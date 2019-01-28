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
    //load = new LoadBinaries();
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

    painter.setPen(lines); //Hier wird das Gitter auf die Zeichenfläche gemalt.
    for (int i = 0; i <= height; i += pixelSize ){
        painter.drawLine(0, i, width, i);
    }
    for (int i = 0; i <= width; i += pixelSize){
        painter.drawLine(i, 0, i, height);
    }

    //Es wird für jeden Eintrag im Array überprüft ob es 0.25,0.50.75 oder 1 ist.
    //Wird in einem Eintrag ein solcher Wert gefunden, wird hier der entsprechende Pixel auf der Zeichenfläche in der richtigen Farbe eingefärbt.
    //Die Indizies multipliziert mit der Größe der Pixel ergibt die linke obere Ecke des Pixels auf der Zeichenfläche. Dann kann wird mit painter.fillRect
    //das entsprechende Quadrat ausgefüllt. Die Linien zwischen den Pixeln sollen nicht ausgefüllt werden, deswegen +1 und -1.
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
    pixelValues[pixelCoord.x()][pixelCoord.y()] = 1; //Der Pixel auf dem man klickt wird im Array mit 1 belegt.
    //Für jeden anliegenden Pixel (Neumann Nachbarschaft) wird dann überprüft ob dieser bereits 1 ist, in diesem fall passiert nichts.
    //Ist er kleiner als 1 wird 0.25 auf den ursprünglichen Wert addiert.
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
    update();
}

QPoint MainWindow::calcField(QPoint point){
    //Diese Funktion berechnet aus einer Koordinate das entsprechende Feld in dem Zweidimensionalen Array.
    //Die x und y Werte der Koordinate werden mit der Größe der Pixel dividiert, somit wird das große Zeichenfeld auf eis reduziert welches
    //dem Array entspricht.
    int xpoint = point.x();
    int ypoint = point.y();
    xpoint = xpoint/pixelSize;
    ypoint = ypoint/pixelSize;
    QPoint coord(xpoint,ypoint);

    return coord;

}





void MainWindow::on_pixelSlider_valueChanged(int value)
//Diese Funktion dient lediglich dazu, dass das Label neben dem Slider für die Pixelgröße den aktuellen Wert des Sliders anzeigt.
{
    ui->pixelSizeLabel->setText(QString::number(value));

}



void MainWindow::on_pushButton_2_clicked()//apply Button für den Pixelgröße Slider
//width und height werden gleich den derzeitigen Slider Values gesetzt.
//dann wird der aktuelle Wert des Sliders ausgelesen, und die PixelSize gleich diesem gesetzt.
//dann wird um die Höhe und Breite der Zeichenfläche in "Pixeln" zu berechnen die normale Höhe und Breite durch die pixelSize dividiert.
//danach werden Höhe und Breite der Zeichenfläche so angepasst, dass sie den nächst kleineren Wert erhalten in dem nur volle "Pixel" angezeigt werden,
//damit keine halben "Pixel an den Rändern übrig bleiben.
//schließlich werden die Labels mit den neuen Höhe und Breite werden versorgt, die Zeichenfläche wird geleert und PaintEvent wird geupdatet.
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
    clear();
    update();
}

void MainWindow::on_clearButton_clicked()
//Dieser Button leert die Zeichenfläche und das Array welches diese repräsentiert.
{
    clear();
    update();
}

void MainWindow::clear(){
//Um die Zeichenfläche zu leeren wird in jeden Eintrag des Arrays eine 0 geschrieben, danach wird PaintEvent neu Aufgerufen und das leere Array ersetzt
//das alte.
    for(int i = 0; i < pixelWidth; i++){
        for (int j = 0;j < pixelHeigth; j++){
            pixelValues[i][j] = 0.0;
        }
    }
}

void MainWindow::on_Width_slider_valueChanged(int value)
//Hier wird das Label neben dem width slider dem entsprechenden Wert des Slider angepasst.
//Außerdem wird die Variable slider_width immer aktuell gehalten wenn der Wert des Sliders gändert wird.
{
    ui->width_value_label->setText(QString::number(value));
    slider_width = value;
}

void MainWindow::on_height_slider_valueChanged(int value)
//Diese Funktion funktioniert analog zum width slider.
{
    ui->height_value_label->setText(QString::number(value));
    slider_height = value;
}

void MainWindow::on_apply_width_heigthbutton_clicked()
//Hier wird wie beim PixelSize Button die entsprechende Höhe und Breite berechnet, nur dass anstatt die Größe der Pixel zu ändern die Höhe und Breite
//der Zeichenfläche geändert wird.
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
//Um ein 28x28
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
