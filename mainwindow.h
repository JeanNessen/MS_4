#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    int width = slider_width;
    int height = slider_height;
    int pixelSize = 50;
    int pixelWidth = width/pixelSize;
    int pixelHeigth = height/pixelSize;

    std::vector<QPoint> full;
    float pixelValues[100][100];



private:
    QColor lGray = QColor(193,193,193);
    QColor mGray = QColor(117,117,117);
    QColor dGray = QColor(69,69,69);

    int slider_width = 500;
    int slider_height = 500;

    void clear();
    Ui::MainWindow *ui;
    QPoint calcField(QPoint point);
protected:
    void paintEvent(QPaintEvent *e);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
private slots:


    void on_pixelSlider_valueChanged(int value);
    void on_pushButton_2_clicked();
    void on_clearButton_clicked();
    void on_Width_slider_valueChanged(int value);
    void on_height_slider_valueChanged(int value);
    void on_apply_width_heigthbutton_clicked();
    void on_defaultButton_clicked();
};

#endif // MAINWINDOW_H
