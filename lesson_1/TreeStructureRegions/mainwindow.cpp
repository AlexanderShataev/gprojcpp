#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTreeWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMessageBox>

#include "country.h"
#include "parserdata.h"

const QString DEFAULT_DATASET_PATH = QString("./../../../gprojcommon/gprojcpp/lesson_1/dataset/worldcities.csv");
//const QString DEFAULT_DATASET_PATH = QString("/home/andrey/projects/gprojcommon/gprojcpp/lesson_1/dataset/worldcities.csv");

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

void MainWindow::initCountriesAndCities(const QVector<ParamsFile>& data) {
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

    connect(ui->pushButtonSave, &QPushButton::clicked, [&](){
        currentFilePath = ui->lineEditPath->text();
        if (currentFilePath == QString()) {
            //QMessageBox::warning(this, "Ошибочное поведение", "Указан несуществующий путь к выборке!\n"
            //                                                  "Проверьте путь и запустите заново..");
            currentFilePath = DEFAULT_DATASET_PATH;
        }
        tryParsing();
    });
    //tryParsing();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::tryParsing()
{
    ParserData parser;
    parser.setFilePath(currentFilePath);
    QVector<ParamsFile> params = parser.parsingCSV();

    initCountriesAndCities(params);
    initTreeView();
    return true;
}

void MainWindow::initTreeView()
{
    model = new QStandardItemModel();
    for (auto& country : con) {
        auto item = new ListStandardItem(country);
        model->appendRow(item);
    }

    model->setHeaderData(0, Qt::Horizontal, "Наименование");
    ui->treeViewCountry->setModel(model);


    return;
}
