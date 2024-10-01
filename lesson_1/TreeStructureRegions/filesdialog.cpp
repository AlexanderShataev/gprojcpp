#include "filesdialog.h"
#include "ui_filesdialog.h"

#include <QFileSystemModel>
#include <QDir>
#include <QDebug>

FilesDialog::FilesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FilesDialog)
{
    ui->setupUi(this);

    createFileSystemModel();
    //setBaseSize(1200, 1700);

    initConnection();
}

FilesDialog::~FilesDialog()
{
    delete ui;
}

void FilesDialog::createFileSystemModel()
{
    model = new QFileSystemModel(this);
    model->setRootPath(QDir::rootPath());

    ui->treeViewFiles->setModel(model);
    ui->treeViewFiles->setRootIndex(model->index(QDir::rootPath()));

    ui->treeViewFiles->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->treeViewFiles->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->treeViewFiles->header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->treeViewFiles->header()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
}

QString FilesDialog::getPath() const
{
    return path;
}

void FilesDialog::initConnection()
{
    connect(ui->treeViewFiles, &QTreeView::clicked, [&](const QModelIndex& idx){
        //qDebug() << model->filePath(idx);
        if (model->isDir(idx)) {
            ui->lineEditCurrentPath->clear();
            path.clear();
        }
        else {
            ui->lineEditCurrentPath->setText(model->filePath(idx));
            path = model->filePath(idx);
        }
    });
}
