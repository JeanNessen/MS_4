#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    for(int i = 0; i < w.pixelWidth; i++){
        for (int j = 0;j < w.pixleHeigth; j++){
            w.pixelValues[i][j] = 0.0;
        }
    }
    w.show();

    return a.exec();
}
