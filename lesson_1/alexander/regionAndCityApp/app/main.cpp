#include <iostream>

#include <QMainWindow>
#include <QApplication>

int main(int argv, char* argc[])
{
    QApplication a(argv, argc);
    QMainWindow w;
    w.show();
    return a.exec();
}
