#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTreeWidget>

#include "country.h"
#include "parserdata.h"

const QString TEST_DATASET_PATH = QString("/home/andrey/projects/gprojcommon/gprojcpp/lesson_1/dataset/worldcities.csv");


void initCountriesAndCities(std::set<Country>& con, const QVector<Params>& data) {
    for (auto d : data) {
        auto itCountry = con.emplace(Country(d.second));
        itCountry.first._M_const_cast()->addCity(d.first);
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tryParsing();
    initTreeView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::tryParsing()
{
    ParserData parser;
    parser.setFilePath(TEST_DATASET_PATH);
    QVector<Params> params = parser.parsingCSV();

    initCountriesAndCities(con, params);
    return true;
}

void MainWindow::initTreeView()
{
    ui->countryTree->setColumnCount(1);


    return;
}
