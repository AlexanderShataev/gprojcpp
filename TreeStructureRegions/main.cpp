#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

//#include "country.h"

using ParamsCity = QPair<QString, QString>;

// Парсинг файла
QVector<ParamsCity> parsingCSV(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return {};

    QVector<ParamsCity> result;
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        auto temp = ParamsCity{line.section(",", 0, 0).remove(QRegularExpression("\"")),
                               line.section("\",\"", 4, 4).remove(QRegularExpression("\""))};
        result.push_back(temp);
    }
    return result;
}

// void initCountryAndCity(const ParamsCity& data) {

// }


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    //return a.exec();

    auto dataset = parsingCSV("/home/andrey/projects/gprojcommon/gprojcpp/lesson_1/dataset/worldcities.csv");

    qDebug() << dataset;

    return 0;
}

