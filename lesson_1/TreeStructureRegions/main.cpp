#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include <QDir>
#include <QDebug>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qDebug() << QCoreApplication::applicationDirPath();

    return a.exec();
}

