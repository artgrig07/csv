#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QDir>
#include <QFileDialog>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QStandardItemModel>
#include <QString>
#include <QStringList>
#include <QTableView>
#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void handleButtonOpenClick();
    void handleSelectViewSelect(const QString &tableName);
    void handleButtonExportClick();
    void handleButtonImportClick();
};

#endif // MAINWINDOW_H
