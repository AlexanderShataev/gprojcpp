#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTreeWidget>
#include <QStandardItem>
#include <QStandardItemModel>

#include "country.h"
#include "parserdata.h"

const QString TEST_DATASET_PATH = QString("/home/andrey/projects/gprojcommon/gprojcpp/lesson_1/dataset/worldcities.csv");

class ListStandardItem : public QStandardItem {
public:
    ListStandardItem(const Country& country) : QStandardItem() {
        this->setText(country.name());
        auto cities = country.getAllCities();
        for (auto i = 0; i < cities.size(); ++i) {
            QStandardItem* item = new QStandardItem();
            item->setText(cities[i]->name());
            this->appendRow(item);
        }
    }
};

// class ListStandardItem : public QStandardItem {
// public:
//     ListStandardItem(const std::shared_ptr<Country>& country) : QStandardItem() {
//         this->setText(country->name());
//         auto cities = country->getAllCities();
//         for (auto i = 0; i < cities.size(); ++i) {
//             QStandardItem* item = new QStandardItem();
//             item->setText(cities[i]->name());
//             this->appendRow(item);
//         }
//     }
// };


void initCountriesAndCities(std::set<Country>& con, const QVector<ParamsFile>& data) {
    for (auto d : data) {
        auto itCountry = con.emplace(d.nameCountry_, d.iso2_, d.iso3_);
        itCountry.first._M_const_cast()->addCity(d.nameCity_, d.population_, d.latitude_, d.longitude_);
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
    QVector<ParamsFile> params = parser.parsingCSV();

    initCountriesAndCities(con, params);
    return true;
}

void MainWindow::initTreeView()
{
    // ui->treeViewCountry->setColumnCount(1);
    model = new QStandardItemModel();
    for (auto& country : con) {
        auto item = new ListStandardItem(country);
        model->appendRow(item);
    }

    ui->treeViewCountry->setModel(model);


    return;
}
