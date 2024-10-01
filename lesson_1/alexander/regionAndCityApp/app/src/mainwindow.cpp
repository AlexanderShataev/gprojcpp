#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "treeanalyzer/csvregionparser.h"
#include "treeanalyzer/regions.h"

#include <QMessageBox>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>

#include "waitingspinnerwidget.h"

class RegionVisualItem: public QStandardItem {
public:
    RegionVisualItem(const TRA::RegionNodePtr<TRA::BaseRegions>& regPtr): regPtr_(regPtr) {
        setEditable(false);
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
    ui->lineEditCSVSourcePath->setText(path);
    mainModel->clear();

    using WatcherRegRoot = QFutureWatcher<TRA::RegionNodePtr<TRA::BaseRegions> >;
    auto rootWatcherPtr = new WatcherRegRoot(this);
    rootWatcherPtr->connect(rootWatcherPtr, &WatcherRegRoot::finished, [=]{
        mainModel->clear();
        mainModel->appendRow(new RegionVisualItem(rootWatcherPtr->result()));
        spinner_->stop();
    });

    spinner_->start();
    QFuture<TRA::RegionNodePtr<TRA::BaseRegions>> future = QtConcurrent::run([path](){
        CSVRegionParser parser;
        auto data = parser.parseFromFile(path.toStdString());
        TRA::RegionNodePtr<TRA::BaseRegions> ptr = std::make_shared<TRA::TreeNodeRegion<TRA::BaseRegions >>(TRA::BaseRegions("All states", TRA::BaseRegions::RegionType::Undefined));
        for (const auto state : data) {
            ptr->addChild(state);
        }
        return ptr;
    });

    rootWatcherPtr->setFuture(future);
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

    spinner_ = new WaitingSpinnerWidget(ui->treeVieeRegions);
    spinner_->setRoundness(70.0);
    spinner_->setMinimumTrailOpacity(15.0);
    spinner_->setTrailFadePercentage(70.0);
    spinner_->setNumberOfLines(12);
    spinner_->setLineLength(10);
    spinner_->setLineWidth(5);
    spinner_->setInnerRadius(10);
    spinner_->setRevolutionsPerSecond(1);
    spinner_->setColor(QColor(100, 100, 100));
}
