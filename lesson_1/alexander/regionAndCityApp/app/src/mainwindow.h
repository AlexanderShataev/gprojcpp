#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QStandardItemModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateRegions(const QString& path);

private:
    void init();

    QStandardItemModel* mainModel{nullptr};
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
