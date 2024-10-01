#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <set>

class Country;
class QStandardItemModel;
class ParamsFile;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool tryParsing();
    void initTreeView();

    void initCountriesAndCities(const QVector<ParamsFile>& data);

private:
    Ui::MainWindow *ui;
    std::set<Country> con;
    QStandardItemModel* model;
    QString currentFilePath;
};
#endif // MAINWINDOW_H
