#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "treeanalyzer/csvregionparser.h"
#include "treeanalyzer/regions.h"

#include <QMessageBox>
#include <QStandardItemModel>
#include <QFileDialog>


class RegionVisualItem: public QStandardItem {
public:
    RegionVisualItem(const TRA::RegionNodePtr<TRA::BaseRegions>& regPtr): regPtr_(regPtr) {
        auto&& childs = regPtr->getChilds();
        for (const auto& child : childs) {
            appendRow(new RegionVisualItem(std::static_pointer_cast<TRA::TreeNodeRegion<TRA::BaseRegions>>(child)));
        }
    }
    QVariant data(int role = Qt::UserRole + 1) const override {
        if (Qt::DisplayRole == role) {
            return QString::fromStdString(regPtr_->getObject().getName());
        }
        return QStandardItem::data(role);
    }

private:
     TRA::RegionNodePtr<TRA::BaseRegions> regPtr_;
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateRegions(const QString &path)
{
    CSVRegionParser parser;
    auto data = parser.parseFromFile(path.toStdString());
    TRA::RegionNodePtr<TRA::BaseRegions> ptr = std::make_shared<TRA::TreeNodeRegion<TRA::BaseRegions >>(TRA::BaseRegions("All states", TRA::BaseRegions::RegionType::Undefined));
    for (const auto state : data) {
        ptr->addChild(state);
    }

    mainModel->clear();
    mainModel->appendRow(new RegionVisualItem(ptr));
}

void MainWindow::init()
{
    mainModel = new QStandardItemModel(this);
    ui->treeVieeRegions->setModel(mainModel);
    ui->treeVieeRegions->header()->hide();
    connect(ui->pushButtonSelectCSV, &QPushButton::clicked, [=](){
        QFileInfo path(QFileDialog::getOpenFileName(this, "Выберите CSVFile"));
        if (!path.exists()) {
            QMessageBox::warning(this, "Внимание", "Данного файла не существует");
            return;
        }
        updateRegions(path.absoluteFilePath());
    });
}
