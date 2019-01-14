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

    int standartWidth = 500;
    int standartHeight = 500;
    int width = standartWidth;
    int height = standartHeight;
    int pixelSize = 50;
    int pixelWidth = width/pixelSize;
    int pixleHeigth = height/pixelSize;

    std::vector<QPoint> full;
    float pixelValues[100][100];



private:
    QColor lGray = QColor(193,193,193);
    QColor mGray = QColor(117,117,117);
    QColor dGray = QColor(69,69,69);

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
};

#endif // MAINWINDOW_H
