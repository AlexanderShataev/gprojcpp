#ifndef FILESDIALOG_H
#define FILESDIALOG_H

#include <QDialog>
#include <QString>

class QFileSystemModel;

namespace Ui {
class FilesDialog;
}

class FilesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilesDialog(QWidget *parent = nullptr);
    ~FilesDialog();

    void createFileSystemModel();
    QString getPath() const;

private:
    Ui::FilesDialog *ui;

    QString path;
    QFileSystemModel* model;

    void initConnection();
};

#endif // FILESDIALOG_H
