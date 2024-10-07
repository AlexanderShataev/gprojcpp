#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTreeWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMessageBox>

#include "filesdialog.h"
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
        auto [it, ok] = con.insert({d.nameCountry_, Country(d.nameCountry_, d.iso2_, d.iso3_)});
        it->second.addCity(d.nameCity_, d.population_, d.latitude_, d.longitude_);
    }
}

void MainWindow::createFilesDialog()
{
    auto dialog = new FilesDialog(this);
    connect(dialog, &QDialog::accepted, [&](){
        auto path = dialog->getPath();
        currentFilePath = path;
        ui->lineEditPath->setText(path);
    });
    dialog->exec();
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connection
    connect(ui->pushButtonSave, &QPushButton::clicked, [&](){
        currentFilePath = ui->lineEditPath->text();
        if (currentFilePath == QString()) {
            currentFilePath = DEFAULT_DATASET_PATH;
        }
        tryParsing();
    });
    connect(ui->pushButtonOpen, &QPushButton::clicked, this, &MainWindow::createFilesDialog);
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
    if (!params.size()) {
        QMessageBox::warning(this, "Ошибочное поведение", "Указан несуществующий путь к выборке!\n"
                                                         "Проверьте путь и запустите заново..");
        return false;
    }

    initCountriesAndCities(params);
    initTreeView();
    return true;
}

void MainWindow::initTreeView()
{
    model = new QStandardItemModel();
    for (auto& [first, country] : con) {
        auto item = new ListStandardItem(country);
        model->appendRow(item);
    }

    model->setHeaderData(0, Qt::Horizontal, "Наименование");
    ui->treeViewCountry->setModel(model);


    return;
}
