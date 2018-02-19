#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->buttonOpen, &QPushButton::released,
            this, &MainWindow::handleButtonOpenClick);

    connect(ui->selectView, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::handleSelectViewSelect);

    connect(ui->buttonExport, &QPushButton::released,
            this, &MainWindow::handleButtonExportClick);

    connect(ui->buttonImport, &QPushButton::released,
            this, &MainWindow::handleButtonImportClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleButtonOpenClick()
{

}

void MainWindow::handleSelectViewSelect(const QString &name)
{

}

void MainWindow::handleButtonExportClick()
{

}

void MainWindow::handleButtonImportClick()
{

}
