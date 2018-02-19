#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Нажатие "Открыть БД"
    connect(ui->buttonOpen, &QPushButton::released,
            this, &MainWindow::handleButtonOpenClick);

    // Выбор таблицы в "Просмотр"
    connect(ui->selectView, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::handleSelectViewSelect);

    // Нажатие "Сохранить" в "Экспорт"
    connect(ui->buttonExport, &QPushButton::released,
            this, &MainWindow::handleButtonExportClick);

    // Нажатие "Открыть" в "Импорт"
    connect(ui->buttonImport, &QPushButton::released,
            this, &MainWindow::handleButtonImportClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// Нажатие "Открыть БД"
void MainWindow::handleButtonOpenClick()
{
    // Открываем диалог выбора БД

    // Открываем БД

    // Читаем список таблиц

    // Добавляем таблицы в selectView

    // Добавляем таблицы в selectExport

    // Открываем "Просмотр"
}

// Выбор таблицы в "Просмотр"
void MainWindow::handleSelectViewSelect(const QString &name)
{
    // Очищаем tableView

    // Читаем таблицу из БД

    // Заполнякем tableView
}

// Нажатие "Сохранить" в "Экспорт"
void MainWindow::handleButtonExportClick()
{
    // Проверяем selectExport на непустоту

    // Открываем диалог сохранения CSV

    // Читаем таблицу из БД

    // Сохраняем CSV
}

// Нажатие "Открыть" в "Импорт"
void MainWindow::handleButtonImportClick()
{
    // Проверяем inputImport на непустоту

    // Открываем диалог выбора CSV

    // Читаем CSV

    // Сохраняем в таблицу

    // Добавляем таблицу в selectView

    // Добавляем таблицу в selectExport
}
