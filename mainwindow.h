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
    int width = 500;
    int height = 500;
    int pixelWidth = width/50;
    int pixleHeigth = height/50;
    int pixelSize = 50;
    std::vector<QPoint> full;
    float pixelValues[10][10];



private:
    Ui::MainWindow *ui;
    QPoint calcField(QPoint point);
protected:
    void paintEvent(QPaintEvent *e);
    virtual void mousePressEvent(QMouseEvent *);
};

#endif // MAINWINDOW_H
