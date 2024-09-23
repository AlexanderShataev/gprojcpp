#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

// #include <QFile>
// #include <QTextStream>
// #include <QRegularExpression>

// #include <set>

// #include "country.h"


// void initCountriesAndCities(std::set<Country>& con, const QVector<ParamsCity>& data) {
//     for (auto d : data) {
//         auto itCountry = con.emplace(Country(d.second));
//         itCountry.first._M_const_cast()->addCity(d.first);
//     }
// }


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    //auto dataset = parsingCSV("/home/andrey/projects/gprojcommon/gprojcpp/lesson_1/dataset/worldcities.csv");
    // std::set<Country> content;
    // initCountriesAndCities(content, dataset);
    // auto f = content.find(Country("Russia"));
    // qDebug() << f->name();
    //return 0;
}

