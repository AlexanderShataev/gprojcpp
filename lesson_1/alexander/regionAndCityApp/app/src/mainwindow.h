#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QStandardItemModel;
class WaitingSpinnerWidget;

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
    WaitingSpinnerWidget* spinner_{nullptr};

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
