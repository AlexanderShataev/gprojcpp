#include <QApplication>

#include "mainwindow.h"

int main(int argv, char* argc[])
{
    QApplication a(argv, argc);
    MainWindow w;
    w.show();
    return a.exec();
}
